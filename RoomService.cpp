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
        QMessageBox::critical(this, "Database Error", db.lastError().text());
    }

    // Ensure the table has required columns (run once to create or modify table)
    // QSqlQuery query(db);
    // query.exec("ALTER TABLE ServiceRecords ADD COLUMN customer_name TEXT");
    // query.exec("ALTER TABLE ServiceRecords ADD COLUMN customer_phone TEXT");
}

void RoomService::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    roomNumberInput = new QLineEdit(this);
    guestIDInput = new QLineEdit(this); // Assuming you want to keep guest ID
    nameInput = new QLineEdit(this);
    phoneInput = new QLineEdit(this);
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
    layout->addWidget(new QLabel("电话:", this));
    layout->addWidget(phoneInput);
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
    QString guestID = guestIDInput->text(); // Assuming you want to keep guest ID
    QString name = nameInput->text();
    QString phone = phoneInput->text();

    QSqlQuery query;
    query.prepare("INSERT INTO ServiceRecords (extension_number, service_start_time, customer_name, customer_phone) VALUES (?, ?, ?, ?)");
    query.addBindValue(roomNumber);
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(name);
    query.addBindValue(phone);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "Check In", "Guest checked in successfully.");
    }
}

void RoomService::on_checkOutButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();

    QSqlQuery query;
    query.prepare("UPDATE ServiceRecords SET generation_time = ?, mode = 'Checked Out' WHERE extension_number = ? AND mode IS NULL");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QMessageBox::information(this, "Check Out", "Check-out successful.");
    }
}

void RoomService::on_billButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ServiceRecords WHERE extension_number = ? AND mode = 'Checked Out'");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QString bill;
        while (query.next()) {
            bill += "Room: " + query.value("extension_number").toString() + "\n";
            bill += "Fee: " + query.value("fee").toString() + "\n\n";
        }
        QMessageBox::information(this, "Bill", bill);
    }
}

void RoomService::on_detailsButton_clicked() {
    int roomNumber = roomNumberInput->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ServiceRecords WHERE extension_number = ?");
    query.addBindValue(roomNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else {
        QString details;
        while (query.next()) {
            details += "Room: " + query.value("extension_number").toString() + "\n";
            details += "Start Time: " + query.value("service_start_time").toString() + "\n";
            details += "End Time: " + query.value("generation_time").toString() + "\n";
            details += "Duration: " + query.value("service_duration").toString() + "\n";
            details += "Temperature: " + query.value("target_temperature").toString() + "\n";
            details += "Fan Speed: " + query.value("fan_speed").toString() + "\n";
            details += "Fee: " + query.value("fee").toString() + "\n";
            details += "Mode: " + query.value("mode").toString() + "\n\n";
        }
        QMessageBox::information(this, "Details", details);
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    RoomService window;
    window.show();
    return app.exec();
}
