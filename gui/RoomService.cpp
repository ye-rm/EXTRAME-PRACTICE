#include "roomservice.h"

RoomService::RoomService(QWidget* parent)
    : QMainWindow(parent) {
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
    db.setDatabaseName("hotel_management.db");
    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
    }
    else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS ServiceRecords ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "roomNumber INTEGER, "
            "guestID TEXT, "
            "status TEXT, "
            "startTime DATETIME, "
            "endTime DATETIME)");
    }
}

void RoomService::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    roomNumberInput = new QLineEdit(this);
    guestIDInput = new QLineEdit(this);
    checkInButton = new QPushButton("入住", this);
    checkOutButton = new QPushButton("退房", this);
    billButton = new QPushButton("账单", this);
    detailsButton = new QPushButton("详单", this);
    statusLabel = new QLabel("状态: 等待操作", this);

    layout->addWidget(new QLabel("房间号:", this));
    layout->addWidget(roomNumberInput);
    layout->addWidget(new QLabel("顾客ID:", this));
    layout->addWidget(guestIDInput);
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
    if (guestID.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a guest ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ServiceRecords (roomNumber, guestID, status, startTime) VALUES (?, ?, 'Checked In', ?)");
    query.addBindValue(roomNumber);
    query.addBindValue(guestID);
    query.addBindValue(QDateTime::currentDateTime());

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "Check In", "Guest checked in successfully.");
        updateRoomStatus(roomNumber, "Checked In");
    }
}

void RoomService::on_checkOutButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();

    QSqlQuery query;
    query.prepare("UPDATE ServiceRecords SET status = 'Checked Out', endTime = ? WHERE roomNumber = ? AND status = 'Checked In'");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "Check Out", "Guest checked out successfully.");
        updateRoomStatus(roomNumber, "Checked Out");
    }
}

void RoomService::on_billButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ServiceRecords WHERE roomNumber = ?");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QString bill = "Room Number: " + QString::number(roomNumber) + "\n";
        while (query.next()) {
            bill += "Guest ID: " + query.value("guestID").toString() + "\n";
            bill += "Status: " + query.value("status").toString() + "\n";
            bill += "Start Time: " + query.value("startTime").toString() + "\n";
            bill += "End Time: " + query.value("endTime").toString() + "\n\n";
        }
        QMessageBox::information(this, "Bill", bill);
    }
}

void RoomService::on_detailsButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ServiceRecords WHERE roomNumber = ?");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QString details = "Room Number: " + QString::number(roomNumber) + "\n";
        while (query.next()) {
            details += "Guest ID: " + query.value("guestID").toString() + "\n";
            details += "Status: " + query.value("status").toString() + "\n";
            details += "Start Time: " + query.value("startTime").toString() + "\n";
            details += "End Time: " + query.value("endTime").toString() + "\n\n";
        }
        QMessageBox::information(this, "Details", details);
    }
}

void RoomService::updateRoomStatus(int roomNumber, const QString& status) {
    if (status == "Checked In") {
        checkInButton->setText("退房");
    }
    else {
        checkInButton->setText("入住");
    }
    statusLabel->setText("房间 " + QString::number(roomNumber) + " 状态: " + status);
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    RoomService window;
    window.show();
    return app.exec();
}
