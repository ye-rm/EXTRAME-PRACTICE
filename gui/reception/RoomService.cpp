#include "RoomService.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

RoomService::RoomService(QWidget *parent) : QMainWindow(parent) {
    setupDatabase();
    setupUI();
    initRoomMsg();
}

RoomService::~RoomService() {
    if (db.isOpen()) {
        db.close();
    }
}

void RoomService::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(SQLITE_FILE);
    if (!db.open()) {
        QMessageBox::critical(this, "数据库错误", db.lastError().text());
    }
}

void RoomService::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    roomNumberInput = new QLineEdit(this);
    guestIDInput = new QLineEdit(this);
    nameInput = new QLineEdit(this);
    checkInButton = new QPushButton("入住", this);
    checkOutButton = new QPushButton("退房", this);
    statusLabel = new QLabel("状态: 等待操作", this);

    layout->addWidget(new QLabel("房间号:", this));
    layout->addWidget(roomNumberInput);
    layout->addWidget(new QLabel("顾客ID:", this));
    layout->addWidget(guestIDInput);
    layout->addWidget(new QLabel("姓名:", this));
    layout->addWidget(nameInput);
    layout->addWidget(checkInButton);
    layout->addWidget(checkOutButton);
    layout->addWidget(statusLabel);

    connect(checkInButton, &QPushButton::clicked, this, &RoomService::on_checkInButton_clicked);
    connect(checkOutButton, &QPushButton::clicked, this, &RoomService::on_checkOutButton_clicked);

    setCentralWidget(centralWidget);
}

void RoomService::on_checkInButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QString guestID = guestIDInput->text();
    QString guestName = nameInput->text();

    if (room_status[roomNumber] == IN_USE) {
        QMessageBox::critical(this, "入住", "房间已被占用。");
        return;
    }

    QSqlQuery query;
    query.prepare(
            "INSERT INTO CustomerRecords (customer_id, room_id, check_in_date, customer_name) VALUES (?, ?, ?, ?)");
    query.addBindValue(guestID); // 先绑定 guestID
    query.addBindValue(roomNumber); // 然后绑定 roomNumber
    query.addBindValue(QDateTime::currentDateTime()); // 绑定当前时间
    query.addBindValue(guestName); // 最后绑定 guestName

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
    } else {
        updateRoomStatus(roomNumber, IN_USE);
        QMessageBox::information(this, "入住", "客户成功入住。");
    }
    // clear input
    roomNumberInput->clear();
    guestIDInput->clear();
    nameInput->clear();
}


void RoomService::on_checkOutButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();

    if (room_status[roomNumber] == FREE) {
        QMessageBox::critical(this, "退房", "房间未被占用。");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT customer_id, check_in_date FROM CustomerRecords WHERE room_id = ? AND check_out_date IS NULL");
    query.addBindValue(roomNumber);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
        return;
    }

    QString customerID = query.value("customer_id").toString();
    QDateTime checkInDate = query.value("check_in_date").toDateTime();
    QDateTime checkOutDate = QDateTime::currentDateTime();
    qint64 secondsStayed = checkInDate.secsTo(checkOutDate);
    int daysStayed = qCeil(static_cast<double>(secondsStayed) / (60 * 60 * 24));

    double roomFeePerDay = room_price[roomNumber];
    double totalRoomFee = daysStayed * roomFeePerDay;

    double totalAirConditionFee = 0;
    QString queryString = QString("SELECT SUM(fee) FROM ServiceRecords WHERE extension_number = %1 AND service_start_time BETWEEN '%2' AND '%3'")
            .arg(roomNumber)
            .arg(checkInDate.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(checkOutDate.toString("yyyy-MM-dd HH:mm:ss"));
    QSqlQuery airConditionQuery;
    if (!airConditionQuery.exec(queryString) || !airConditionQuery.next()) {
        QMessageBox::critical(this, "数据库错误", airConditionQuery.lastError().text());
        return;
    }
    totalAirConditionFee = airConditionQuery.value(0).toDouble();

    QSqlQuery updateQuery;
    updateQuery.prepare(
            "UPDATE CustomerRecords SET check_out_date = ?, room_fee = ?, air_condition_fee = ? WHERE room_id = ? AND check_out_date IS NULL");
    updateQuery.addBindValue(checkOutDate);
    updateQuery.addBindValue(totalRoomFee);
    updateQuery.addBindValue(totalAirConditionFee);
    updateQuery.addBindValue(roomNumber);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "数据库错误", updateQuery.lastError().text());
    } else {
        updateRoomStatus(roomNumber, FREE);

        double totalFee = totalRoomFee + totalAirConditionFee;
        BillWindow *billWindow = new BillWindow(this);
        billWindow->setBillDetails(customerID, roomNumber, totalRoomFee, totalAirConditionFee, totalFee, checkInDate, checkOutDate);
        billWindow->exec();
    }
    //clear input
    roomNumberInput->clear();
    guestIDInput->clear();
    nameInput->clear();
}


void RoomService::initRoomMsg() {
    rapidcsv::Document doc(SOCKET_CONFIG_FILE);
    roomCount = doc.GetRowCount();
    for (int i = 0; i < roomCount; i++) {
        int roomNumber = doc.GetCell<int>(0, i);
        auto price = doc.GetCell<double>(4, i);
        // query in database to get room status
        QSqlQuery query;
        query.prepare("SELECT check_out_date FROM CustomerRecords WHERE room_id = ? AND check_out_date IS NULL");
        query.addBindValue(roomNumber);
        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", query.lastError().text());
            return;
        }
        status r_status = query.next() ? IN_USE : FREE;
        room_status[roomNumber] = r_status;
        room_price[roomNumber] = price;
    }
}

void RoomService::updateRoomStatus(int roomNumber, status r_status) {
    room_status[roomNumber] = r_status;
    statusLabel->setText((r_status == IN_USE ? "已入住" : "空闲"));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RoomService window;
    window.show();
    return app.exec();
}
