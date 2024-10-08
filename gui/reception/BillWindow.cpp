// BillWindow.cpp
#include "BillWindow.h"

BillWindow::BillWindow(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    customerIDLabel = new QLabel(this);
    roomNumberLabel = new QLabel(this);
    roomFeeLabel = new QLabel(this);
    airConditionFeeLabel = new QLabel(this);
    totalFeeLabel = new QLabel(this);
    checkInDateLabel = new QLabel(this);
    checkOutDateLabel = new QLabel(this);

    detailsButton = new QPushButton("查看空调使用详单", this);
    connect(detailsButton, &QPushButton::clicked, this, &BillWindow::on_detailsButton_clicked);

    layout->addWidget(customerIDLabel);
    layout->addWidget(roomNumberLabel);
    layout->addWidget(roomFeeLabel);
    layout->addWidget(airConditionFeeLabel);
    layout->addWidget(totalFeeLabel);
    layout->addWidget(checkInDateLabel);
    layout->addWidget(checkOutDateLabel);
    layout->addWidget(detailsButton);

    setLayout(layout);
}

void BillWindow::setBillDetails(const QString &customerID, int roomNumber, double roomFee, double airConditionFee, double totalFee, const QDateTime &checkInDate, const QDateTime &checkOutDate) {
    customerIDLabel->setText("顾客ID: " + customerID);
    roomNumberLabel->setText("房间号: " + QString::number(roomNumber));
    roomFeeLabel->setText("房费: " + QString::number(roomFee) + " 元");
    airConditionFeeLabel->setText("空调使用费: " + QString::number(airConditionFee) + " 元");
    totalFeeLabel->setText("总费用: " + QString::number(totalFee) + " 元");
    checkInDateLabel->setText("入住时间: " + checkInDate.toString("yyyy-MM-dd HH:mm:ss"));
    checkOutDateLabel->setText("退房时间: " + checkOutDate.toString("yyyy-MM-dd HH:mm:ss"));

    currentRoomNumber = roomNumber;
    currentCheckInDate = checkInDate;
    currentCheckOutDate = checkOutDate;
    QString fileName = QString("住宿账单_%1_%2_%3.csv").arg(roomNumber).arg(checkInDate.toString("yyyyMMddHHmmss")).arg(checkOutDate.toString("yyyyMMddHHmmss"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "顾客ID: "<< customerID << "\n";
    out << "房间号: " << roomNumber << "\n";
    out << "房费: " << roomFee << " 元\n";
    out << "空调使用费: " << airConditionFee << " 元\n";
    out << "总费用: " << totalFee << " 元\n";
    out << "入住时间: " << checkInDate.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    out << "退房时间: " << checkOutDate.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    file.close();
}

void BillWindow::on_detailsButton_clicked() {
    AirConditionDetailsWindow *detailsWindow = new AirConditionDetailsWindow(currentRoomNumber, currentCheckInDate, currentCheckOutDate, this);
    detailsWindow->exec();
}
