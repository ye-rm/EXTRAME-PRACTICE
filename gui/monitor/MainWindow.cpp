// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // 初始化表格小部件
    tableWidget = new QTableWidget(this);
    setupTableWidget();

    // 创建一个布局并将表格添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableWidget);

    // 创建一个中心部件并将布局设置为中心部件的布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // 初始化定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateServiceList);
    timer->start(5); // 每5秒触发一次

    // 首次显示服务数据
    displayServiceData();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupTableWidget()
{
    tableWidget->setColumnCount(7);
    QStringList headers;
    headers << "房间" << "当前温度" << "目标温度"
            << "风速" << "模式" << "服务过"
            << "状态" ;
    tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::displayServiceData()
{
    tableWidget->setRowCount(display_services.size());
    tableWidget->clearContents();
    for (size_t i = 0; i < display_services.size(); ++i) {
        const service &svc = display_services[i];
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(svc.get_sub_id())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(svc.get_cur_temp())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(svc.get_target_temp())));
        switch (svc.get_cur_wind_speed()) {
            case LOW_SPEED:
                tableWidget->setItem(i, 3, new QTableWidgetItem("Low"));
                break;
            case MEDIUM_SPEED:
                tableWidget->setItem(i, 3, new QTableWidgetItem("Mid"));
                break;
            case HIGH_SPEED:
                tableWidget->setItem(i, 3, new QTableWidgetItem("High"));
                break;
            default:
                tableWidget->setItem(i, 3, new QTableWidgetItem("Unknown"));
                break;
        }
        switch (svc.get_working_mood()){
            case COOLING_MODE:
                tableWidget->setItem(i, 4, new QTableWidgetItem("Cooling"));
                break;
            case HEATING_MODE:
                tableWidget->setItem(i, 4, new QTableWidgetItem("Heating"));
                break;
            default:
                tableWidget->setItem(i, 4, new QTableWidgetItem("Unknown"));
                break;
        }
        tableWidget->setItem(i, 5, new QTableWidgetItem(svc.ever_serviced() ? "Yes" : "No"));
        switch (svc.get_status()) {
            case WORKING:
                tableWidget->setItem(i, 6, new QTableWidgetItem("Working"));
                break;
            case WAITING:
                tableWidget->setItem(i, 6, new QTableWidgetItem("Waiting"));
                break;
            default:
                tableWidget->setItem(i, 6, new QTableWidgetItem("Unknown"));
                break;

        }
    }
}

void MainWindow::updateServiceList()
{
    display_services = e_scheduler->copy_service();
    displayServiceData();
}

void MainWindow::linkScheduler(Scheduler *scheduler) {
    e_scheduler = scheduler;
}

