// AirConditionDetailsWindow.cpp
#include "AirConditionDetailsWindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTime>

AirConditionDetailsWindow::AirConditionDetailsWindow(int roomNumber, const QDateTime &checkInDate, const QDateTime &checkOutDate, QWidget *parent)
        : QDialog(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableView = new QTableView(this);
    model = new QSqlQueryModel(this);

    QString queryString = QString("SELECT * FROM ServiceRecords WHERE extension_number = %1 AND service_start_time BETWEEN '%2' AND '%3'")
            .arg(roomNumber)
            .arg(checkInDate.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(checkOutDate.toString("yyyy-MM-dd HH:mm:ss"));

    model->setQuery(queryString);

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "数据库错误", model->lastError().text());
        return;
    }

    setHeaders();

    tableView->setModel(model);
    layout->addWidget(tableView);
    setLayout(layout);
    setWindowTitle("空调使用详单");
    resize(800, 600);
}

void AirConditionDetailsWindow::setHeaders() {
    model->setHeaderData(0, Qt::Horizontal, "房间号");
    model->setHeaderData(1, Qt::Horizontal, "服务开始时间");
    model->setHeaderData(2, Qt::Horizontal, "详单生成时间");
    model->setHeaderData(3, Qt::Horizontal, "服务时长（分钟）");
    model->setHeaderData(4, Qt::Horizontal, "目标温度（摄氏度）");
    model->setHeaderData(5, Qt::Horizontal, "风速");
    model->setHeaderData(6, Qt::Horizontal, "费用");
    model->setHeaderData(7, Qt::Horizontal, "模式");
}