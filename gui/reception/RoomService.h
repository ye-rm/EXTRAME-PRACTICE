// 入住退房服务界面
#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include <QMainWindow>
#include <QtMath>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QMap>
#include "../../src/common/common.h"
#include "../../lib/rapidcsv/rapidcsv.h"
#include "BillWindow.h"

enum status {
    IN_USE,
    FREE,
};

class RoomService : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomService(QWidget* parent = nullptr);
    ~RoomService();

private slots:
    void on_checkInButton_clicked();
    void on_checkOutButton_clicked();

private:
    void setupUI();
    void setupDatabase();
    void initRoomMsg();
    void updateRoomStatus(int roomNumber, status r_status);

    QSqlDatabase db;
    QLineEdit* roomNumberInput;
    QLineEdit* guestIDInput;
    QLineEdit* nameInput;
    QLineEdit* phoneInput;
    QPushButton* checkInButton;
    QPushButton* checkOutButton;
    QPushButton* billButton;
    QPushButton* detailsButton;
    int roomCount;
    QLabel* statusLabel;
    QMap<int, status> room_status;
    QMap<int, double> room_price;
};

#endif // ROOMSERVICE_H
