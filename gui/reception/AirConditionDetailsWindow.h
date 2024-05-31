// 账单窗口中可选择查看空调使用详单的窗口
#ifndef AIRCONDITIONDETAILSWINDOW_H
#define AIRCONDITIONDETAILSWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QFile>

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
