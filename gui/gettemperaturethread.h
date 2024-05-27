#ifndef GETTEMPERATURETHREAD_H
#define GETTEMPERATURETHREAD_H

#include <QObject>
#include <QTimer>
#include "../src/client/client.h"

class GetTemperatureThread : public QObject
{
    Q_OBJECT
public:
    GetTemperatureThread(Client * client, QObject *parent = nullptr);
    ~GetTemperatureThread();

signals:
    void setTemperature(int nTemperature);

public slots:
    void startThread();
    

private:
    QTimer *m_pTimer;
	Client* m_client;

protected slots:
    void slotGetTemp();
};

#endif // GETTEMPERATURETHREAD_H
