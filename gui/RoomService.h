#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include <QApplication>
#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class RoomService : public QMainWindow {
    Q_OBJECT

public:
    RoomService(QWidget* parent = nullptr);
    ~RoomService();

private slots:
    void on_checkInButton_clicked();
    void on_checkOutButton_clicked();
    void on_billButton_clicked();
    void on_detailsButton_clicked();

private:
    QSqlDatabase db;
    void setupDatabase();
    void setupUI();
    void updateRoomStatus(int roomNumber, const QString& status);

    QLineEdit* roomNumberInput;
    QLineEdit* guestIDInput;
    QPushButton* checkInButton;
    QPushButton* checkOutButton;
    QPushButton* billButton;
    QPushButton* detailsButton;
    QLabel* statusLabel;
};

#endif // ROOMSERVICE_H
