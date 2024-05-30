// mainwindow.cpp
#include "mainwindow.h"
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          startDateEdit(new QDateEdit(this)),
          endDateEdit(new QDateEdit(this)),
          roomReportButton(new QPushButton("Generate Room Report", this)),
          serviceReportButton(new QPushButton("Generate Service Report", this)),
          statusLabel(new QLabel(this)) {

    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Start Date:"));
    layout->addWidget(startDateEdit);
    layout->addWidget(new QLabel("End Date:"));
    layout->addWidget(endDateEdit);
    layout->addWidget(roomReportButton);
    layout->addWidget(serviceReportButton);
    layout->addWidget(statusLabel);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(roomReportButton, &QPushButton::clicked, this, &MainWindow::generateRoomReport);
    connect(serviceReportButton, &QPushButton::clicked, this, &MainWindow::generateServiceReport);
}

MainWindow::~MainWindow() {
}

void MainWindow::generateRoomReport() {
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString query = QString("SELECT * FROM CustomerRecords WHERE check_in_date BETWEEN '%1' AND '%2'")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd"));
    QString filename = QString("%1_to_%2_RoomReport_%3.csv")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd"))
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    queryDatabaseAndExportToCSV(query, filename);
}

void MainWindow::generateServiceReport() {
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString query = QString("SELECT * FROM ServiceRecords WHERE service_start_time BETWEEN '%1' AND '%2'")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd"));
    QString filename = QString("%1_to_%2_ServiceReport_%3.csv")
            .arg(startDate.toString("yyyy-MM-dd"))
            .arg(endDate.toString("yyyy-MM-dd"))
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    queryDatabaseAndExportToCSV(query, filename);
}

int MainWindow::callback(void *data, int argc, char **argv, char **azColName){
    FILE *pFile = (FILE*)data;
    for(int i = 0; i < argc; i++){
        fprintf(pFile, "%s,", argv[i] ? argv[i] : "NULL");
    }
    fprintf(pFile, "\n");
    return 0;
}

void MainWindow::queryDatabaseAndExportToCSV(const QString &query, const QString &csvFilename) {
    sqlite3 *db;
    char *zErrMsg = 0;
    if (sqlite3_open(SQLITE_FILE, &db) != SQLITE_OK) {
        QMessageBox::critical(this, "Database Error", "Failed to open database.");
        return;
    }

    FILE *csvFile = fopen(csvFilename.toStdString().c_str(), "w");
    if (!csvFile) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        sqlite3_close(db);
        return;
    }

    int rc=sqlite3_exec(db, query.toStdString().c_str(),callback, csvFile, &zErrMsg);
    if(rc!=SQLITE_OK){
        QMessageBox::critical(this, "Query Error", zErrMsg);
        sqlite3_free(zErrMsg);
        fclose(csvFile);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
    fclose(csvFile);
    statusLabel->setText(QString("Report saved as %1").arg(csvFilename));
}
