#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

class RoomService : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomService(QWidget* parent = nullptr);
    ~RoomService();

private slots:
    void on_checkInButton_clicked();
    void on_checkOutButton_clicked();
    void on_billButton_clicked();
    void on_detailsButton_clicked();

private:
    void setupUI();
    void setupDatabase();
    void updateRoomStatus(int roomNumber, const QString& status);

    QSqlDatabase db;
    QLineEdit* roomNumberInput;
    QLineEdit* guestIDInput;
    QLineEdit* nameInput;
    QLineEdit* phoneInput;
    QPushButton* checkInButton;
    QPushButton* checkOutButton;
    QPushButton* billButton;
    QPushButton* detailsButton;
    QLabel* statusLabel;
};

#endif // ROOMSERVICE_H
