// BillWindow.h
#ifndef BILLWINDOW_H
#define BILLWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include "AirConditionDetailsWindow.h"

class BillWindow : public QDialog {
Q_OBJECT
public:
    BillWindow(QWidget *parent = nullptr);

    void setBillDetails(const QString &customerID, int roomNumber, double roomFee, double airConditionFee, double totalFee, const QDateTime &checkInDate, const QDateTime &checkOutDate);

private slots:
    void on_detailsButton_clicked();

private:
    QLabel *customerIDLabel;
    QLabel *roomNumberLabel;
    QLabel *roomFeeLabel;
    QLabel *airConditionFeeLabel;
    QLabel *totalFeeLabel;
    QLabel *checkInDateLabel;
    QLabel *checkOutDateLabel;
    QPushButton *detailsButton;
    int currentRoomNumber;
    QDateTime currentCheckInDate;
    QDateTime currentCheckOutDate;
};

#endif // BILLWINDOW_H
