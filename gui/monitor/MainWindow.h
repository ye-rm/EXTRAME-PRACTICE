// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <vector>
#include <mutex>
#include "../../src/server/service.h"  // 确保包含 service 类的头文件
#include "../../src/common/common.h"
#include "../../src/server/scheduler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void linkScheduler(Scheduler *scheduler);

private slots:
    void updateServiceList();

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    Scheduler *e_scheduler;
    std::vector<service> display_services;
    QTimer *timer;

    void setupTableWidget();
    void displayServiceData();
};

#endif // MAINWINDOW_H
