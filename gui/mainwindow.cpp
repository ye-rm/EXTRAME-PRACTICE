#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextCodec>

#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new Client(1);
	m_client->start_client_working();
    this->setWindowTitle("Controller");
    m_bIsTurnOn = false;
    m_pOptThread = new QThread;
    m_pAirConditionerOpt = new AirConditionerOptThread;
    m_pAirConditionerOpt->moveToThread(m_pOptThread);
    m_pOptThread->start();
	updateTempThread = std::thread(&MainWindow::updateTemp, this);
 //   m_pGetTempThread = new GetTemperatureThread(m_client);
//    m_pThreadGetTemp = new QThread;
 //   m_pGetTempThread->moveToThread(m_pThreadGetTemp);
//    m_pThreadGetTemp->start();

    initWindow();
    connectionFunc();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_pOptThread->quit();
    m_pOptThread->wait();
    m_pOptThread->deleteLater();
    if(m_pAirConditionerOpt)
    {
        delete m_pAirConditionerOpt;
        m_pAirConditionerOpt = nullptr;
    }

//    m_pThreadGetTemp->quit();
  //  m_pThreadGetTemp->wait();
  //  m_pThreadGetTemp->deleteLater();
 //   if(m_pGetTempThread)
 //   {
 //       delete m_pGetTempThread;
//        m_pGetTempThread = nullptr;
//    }
}

void MainWindow::initWindow()
{
    QFile qssFile(":/path/qss/mainwindow.qss");
    if(qssFile.open(QFile::ReadOnly))
    {
        this->setStyleSheet(qssFile.readAll());
    }
    qssFile.close();

    QRegExp regExp("^([1][6-9]|[2][0-9]|3[0-2])$");
    QRegExpValidator *validator = new QRegExpValidator(regExp, ui->lineEdit_temperature);
    ui->lineEdit_temperature->setValidator(validator);

    ui->label_currCostData->setText(QString::fromUtf8("5￥"));
    ui->label_allinCostData->setText(QString::fromUtf8("10￥"));
    ui->label_errorTip->hide();
    initData();
}

void MainWindow::connectionFunc()
{
    connect(ui->pushButton_ok, &QPushButton::clicked, this, &MainWindow::slotSetDesTemperature);
    connect(ui->pushButton_turnOff, &QPushButton::clicked, this, &MainWindow::slotOnClickedTurnOff);
    connect(ui->pushButton_turnOn, &QPushButton::clicked, this, &MainWindow::slotOnClickedTurnOn);
    connect(ui->pushButton_hot, &QPushButton::clicked, this, &MainWindow::slotOnClickedHot);
    connect(ui->pushButton_cold, &QPushButton::clicked, this, &MainWindow::slotOnClickedCold);
    connect(ui->pushButton_low, &QPushButton::clicked, this, &MainWindow::slotOnClickedLowFan);
    connect(ui->pushButton_middle, &QPushButton::clicked, this, &MainWindow::slotOnClickedMiddleFan);
    connect(ui->pushButton_high, &QPushButton::clicked, this, &MainWindow::slotOnClickedHighFan);
    connect(m_pAirConditionerOpt, &AirConditionerOptThread::signalOptResult, this, &MainWindow::slotSetWorkStatus);
    connect(this, &MainWindow::signalToTurnOn, m_pAirConditionerOpt, &AirConditionerOptThread::turnOn);
    connect(this, &MainWindow::signalToTurnOff, m_pAirConditionerOpt, &AirConditionerOptThread::turnOff);
//    connect(this, &MainWindow::signalStartGetTemp, m_pGetTempThread, &GetTemperatureThread::startThread);
//    connect(m_pGetTempThread, &GetTemperatureThread::setTemperature, this, &MainWindow::slotSetCurrTemp);
}

void MainWindow::setWorkModel(int nWorkModel)
{
    switch (nWorkModel)
    {
    case WORKMODELENUM::HOT:
        // TODO: 设置制热,如果操作耗时建议放到AirConditionerOptThread线程
		m_client->change_working_mode(HEATING_MODE);
        ui->label_workMode_hot->show();
        ui->label_workMode_cold->hide();
        break;
    case WORKMODELENUM::COLD:
        // TODO: 设置制冷，如果操作耗时建议放到AirConditionerOptThread线程
		m_client->change_working_mode(COOLING_MODE);
        ui->label_workMode_hot->hide();
        ui->label_workMode_cold->show();
        break;
    }
}

void MainWindow::setWindSpeed(int nSpeed)
{
    switch (nSpeed)
    {
    case WINDSPEEDENUM::LOW:
        // TODO:设置低档风速，如果操作耗时建议放到AirConditionerOptThread线程
		m_client->change_wind_speed(LOW_SPEED);
        ui->label_speed1->show();
        ui->label_speed2->hide();
        ui->label_speed3->hide();
        break;
    case WINDSPEEDENUM::MIDDLE:
        // TODO: 设置中档风速，如果操作耗时建议放到AirConditionerOptThread线程
		m_client->change_wind_speed(MEDIUM_SPEED);
        ui->label_speed1->show();
        ui->label_speed2->show();
        ui->label_speed3->hide();
        break;
    case WINDSPEEDENUM::HIGH:
        // TODO: 设置高档风速，如果操作耗时建议放到AirConditionerOptThread线程
		m_client->change_wind_speed(HIGH_SPEED);
        ui->label_speed1->show();
        ui->label_speed2->show();
        ui->label_speed3->show();
        break;
    }
}

void MainWindow::initData()
{
    ui->lineEdit_temperature->setText("");
    ui->label_currTempData->setText(QString("-"));
    ui->label_desTempData->setText(QString("25℃"));
    ui->label_workMode_hot->show();
    ui->label_workMode_cold->hide();
    ui->label_workStatus_waiting->hide();
    ui->label_workStatus_working->hide();
    ui->label_on->hide();
    ui->label_off->show();
    ui->label_speed3->hide();
    ui->label_speed1->show();
    ui->label_speed2->show();
}

void MainWindow::slotSetDesTemperature()
{
    if((ui->lineEdit_temperature->text() == "") || (ui->lineEdit_temperature->text().toInt() < 16))
    {
        ui->label_errorTip->show();
        return ;
    }
    ui->label_errorTip->hide();
    // TODO:设置目标温度并展示在数据区，设置目标温度操作如果耗时建议放到AirConditionerOptThread线程
    m_client->change_target_temp(ui->lineEdit_temperature->text().toInt());
    ui->label_desTempData->setText(QString("%1℃").arg(ui->lineEdit_temperature->text()));
    ui->lineEdit_temperature->setText("");
}

void MainWindow::slotOnClickedTurnOff()
{
    if(m_bIsTurnOn)
    {
        m_bIsTurnOn = false;
        initData();
		m_client->power_off();
        emit signalToTurnOff();
    }
}

void MainWindow::slotOnClickedTurnOn()
{
    if(!m_bIsTurnOn)
    {
        ui->label_on->show();
        ui->label_off->hide();
		m_client->power_on();
        ui->label_workStatus_waiting->show();
        ui->label_workStatus_working->hide();
        // 通知启动线程启动空调
        emit signalToTurnOn();
    }
}

void MainWindow::slotOnClickedHot()
{
    if(m_bIsTurnOn)
    {
        setWorkModel(WORKMODELENUM::HOT);
    }
}

void MainWindow::slotOnClickedCold()
{
    if(m_bIsTurnOn)
    {
        setWorkModel(WORKMODELENUM::COLD);
    }
}

void MainWindow::slotOnClickedLowFan()
{
    if(m_bIsTurnOn)
    {
        setWindSpeed(WINDSPEEDENUM::LOW);
    }
}

void MainWindow::slotOnClickedMiddleFan()
{
    if(m_bIsTurnOn)
    {
        setWindSpeed(WINDSPEEDENUM::MIDDLE);
    }
}

void MainWindow::slotOnClickedHighFan()
{
    if(m_bIsTurnOn)
    {
        setWindSpeed(WINDSPEEDENUM::HIGH);
    }
}

void MainWindow::slotSetWorkStatus(bool bSuccess)
{
    if(bSuccess)
    {
        m_bIsTurnOn = true;
        ui->label_workStatus_working->show();
        ui->label_workStatus_waiting->hide();
        // 通知获取室温线程定时获取室温
        emit signalStartGetTemp();
        return ;
    }
    initData();
}

void MainWindow::slotSetCurrTemp(int nCurrTemp)
{
    ui->label_currTempData->setText(QString("%1℃").arg(nCurrTemp));
}

void MainWindow::updateTemp()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
        slotSetCurrTemp((int)m_client->get_cur_temp());
	}
}