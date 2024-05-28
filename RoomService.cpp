#include "RoomService.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

RoomService::RoomService(QWidget* parent) : QMainWindow(parent) {
    setupDatabase();
    setupUI();
}

RoomService::~RoomService() {
    if (db.isOpen()) {
        db.close();
    }
}

void RoomService::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/DELL/Source/Repos/ye-rm/EXTRAME-PRACTICE/sqlite/airconditioner.sqlite");
    if (!db.open()) {
        QMessageBox::critical(this, "数据库错误", db.lastError().text());
    }

}

void RoomService::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    roomNumberInput = new QLineEdit(this);
    guestIDInput = new QLineEdit(this);
    nameInput = new QLineEdit(this);
    checkInButton = new QPushButton("入住", this);
    checkOutButton = new QPushButton("退房", this);
    billButton = new QPushButton("账单", this);
    detailsButton = new QPushButton("详单", this);
    statusLabel = new QLabel("状态: 等待操作", this);

    layout->addWidget(new QLabel("房间号:", this));
    layout->addWidget(roomNumberInput);
    layout->addWidget(new QLabel("顾客ID:", this));
    layout->addWidget(guestIDInput);
    layout->addWidget(new QLabel("姓名:", this));
    layout->addWidget(nameInput);
    layout->addWidget(checkInButton);
    layout->addWidget(checkOutButton);
    layout->addWidget(billButton);
    layout->addWidget(detailsButton);
    layout->addWidget(statusLabel);

    connect(checkInButton, &QPushButton::clicked, this, &RoomService::on_checkInButton_clicked);
    connect(checkOutButton, &QPushButton::clicked, this, &RoomService::on_checkOutButton_clicked);
    connect(billButton, &QPushButton::clicked, this, &RoomService::on_billButton_clicked);
    connect(detailsButton, &QPushButton::clicked, this, &RoomService::on_detailsButton_clicked);

    setCentralWidget(centralWidget);
}

void RoomService::on_checkInButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QString guestID = guestIDInput->text();
    QString name = nameInput->text();

    QSqlQuery query;
    query.prepare("INSERT INTO RoomRecords (room_id, customer_id, customer_name, check_in_time) VALUES (?, ?, ?, ?)");
    query.addBindValue(roomNumber);
    query.addBindValue(guestID);
    query.addBindValue(name);
    query.addBindValue(QDateTime::currentDateTime());

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "入住", "客户成功入住。");
    }
}

void RoomService::on_checkOutButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();

    QSqlQuery query;
    query.prepare("UPDATE RoomRecords SET check_out_time = ? WHERE room_id = ? AND check_out_time IS NULL");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "退房", "退房成功。");
    }
}

void RoomService::on_billButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM RoomRecords WHERE room_id = ? AND check_out_time IS NOT NULL");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
    }
    else {
        QString bill;
        while (query.next()) {
            bill += "房间号: " + query.value("room_id").toString() + "\n";
            bill += "费用: " + calculateBill(query.value("check_in_time").toDateTime(), query.value("check_out_time").toDateTime()) + "\n\n";
        }
        QMessageBox::information(this, "账单", bill);
    }
}

void RoomService::on_detailsButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM RoomRecords WHERE room_id = ?");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", query.lastError().text());
    }
    else {
        QString details;
        while (query.next()) {
            details += "房间号: " + query.value("room_id").toString() + "\n";
            details += "开始时间: " + query.value("check_in_time").toString() + "\n";
            details += "结束时间: " + query.value("check_out_time").toString() + "\n";
            details += "客户姓名: " + query.value("customer_name").toString() + "\n\n";
        }
        QMessageBox::information(this, "详单", details);
    }
}

QString RoomService::calculateBill(const QDateTime& startTime, const QDateTime& endTime) {
    // 添加费用计算逻辑
    return "具体费用"; // 暂时返回固定字符串
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    RoomService window;
    window.show();
    return app.exec();
}
