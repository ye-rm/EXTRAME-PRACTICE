// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include "../../sqlite/sqlite3.h"
#include "../../lib/rapidcsv/rapidcsv.h"
#include "../../src/common/common.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateRoomReport();
    void generateServiceReport();

private:
    void queryDatabaseAndExportToCSV(const QString &query, const QString &csvFilename);
    static int callback(void *data, int argc, char **argv, char **azColName);
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QPushButton *roomReportButton;
    QPushButton *serviceReportButton;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
