#include "airconditioneroptthread.h"
#include <QThread>

AirConditionerOptThread::AirConditionerOptThread(QObject *parent)
    :QObject(parent)
{

}

void AirConditionerOptThread::turnOff()
{
    // TODO: 执行关闭空调的逻辑
    
}

void AirConditionerOptThread::turnOn()
{
    // TODO: 执行关闭空调的逻辑,目前设计假数据2S后发送成功信号
    QThread::sleep(2);
    emit signalOptResult(true);

}
