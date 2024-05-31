// AirConditionDetailsWindow.cpp
#include "AirConditionDetailsWindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
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

    QString fileName = QString("空调账单_%1_%2_%3.csv")
            .arg(roomNumber)
            .arg(checkInDate.toString("yyyyMMddHHmmss"))
            .arg(checkOutDate.toString("yyyyMMddHHmmss"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "文件错误", "无法创建文件: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << "房间号,服务开始时间,详单生成时间,服务时长（分钟）,目标温度（摄氏度）,风速,费用,模式\n";

    // 遍历查询结果并写入文件
    for (int row = 0; row < model->rowCount(); ++row) {
        out << model->record(row).value("extension_number").toString() << ","
            << model->record(row).value("service_start_time").toDateTime().toString("yyyy-MM-dd HH:mm:ss") << ","
            << model->record(row).value("detail_creation_time").toDateTime().toString("yyyy-MM-dd HH:mm:ss") << ","
            << model->record(row).value("service_duration").toInt() << ","
            << model->record(row).value("target_temperature").toDouble() << ","
            << model->record(row).value("wind_speed").toInt() << ","
            << model->record(row).value("fee").toDouble() << ","
            << model->record(row).value("mode").toString() << "\n";
    }

    file.close();

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