#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airconditioneroptthread.h"
//#include "gettemperaturethread.h"
#include "../src/client/client.h"
#include "../src/common/common.h"
#include <thread>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum WORKMODELENUM
{
    HOT,
    COLD
};

enum WINDSPEEDENUM
{
    LOW = 1,
    MIDDLE,
    HIGH
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalToTurnOn();
    void signalToTurnOff();
    void signalStartGetTemp();

private:
	std::thread updateTempThread;
    Ui::MainWindow *ui;
    bool m_bIsTurnOn; // 记录当前空调状态
	Client *m_client;
    

    AirConditionerOptThread *m_pAirConditionerOpt;
    QThread *m_pOptThread;
//    GetTemperatureThread *m_pGetTempThread;
//    QThread *m_pThreadGetTemp;

protected:
    void initWindow();
    void connectionFunc();
    void setWorkModel(int nWorkModel);
    void setWindSpeed(int nSpeed);
    void initData();
	void updateTemp();

protected slots:
    void slotSetDesTemperature();
    void slotOnClickedTurnOff();
    void slotOnClickedTurnOn();
    void slotOnClickedHot();
    void slotOnClickedCold();
    void slotOnClickedLowFan();
    void slotOnClickedMiddleFan();
    void slotOnClickedHighFan();
    void slotSetWorkStatus(bool bSuccess);
    void slotSetCurrTemp(int nCurrTemp);
};
#endif // MAINWINDOW_H
