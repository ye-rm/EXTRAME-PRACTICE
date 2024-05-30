// AirConditionDetailsWindow.h
#ifndef AIRCONDITIONDETAILSWINDOW_H
#define AIRCONDITIONDETAILSWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>
#include <QVBoxLayout>

class AirConditionDetailsWindow : public QDialog {
Q_OBJECT

public:
    AirConditionDetailsWindow(int roomNumber, const QDateTime &checkInDate, const QDateTime &checkOutDate, QWidget *parent = nullptr);

private:
    QTableView *tableView;
    QSqlQueryModel *model;
    void setHeaders();
};

#endif // AIRCONDITIONDETAILSWINDOW_H
