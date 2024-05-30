#ifndef AIRCONDITIONEROPTTHREAD_H
#define AIRCONDITIONEROPTTHREAD_H

#include <QObject>

class AirConditionerOptThread : public QObject
{
    Q_OBJECT
public:
    AirConditionerOptThread(QObject *parent = nullptr);

signals:
    void signalOptResult(bool bSuccess);

public slots:
    void turnOn(); // 目前设计没有参数，如果需要参数可以再添加
    void turnOff();
};

#endif // AIRCONDITIONEROPTTHREAD_H
