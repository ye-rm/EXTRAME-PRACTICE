#include "gettemperaturethread.h"

GetTemperatureThread::GetTemperatureThread(Client* client, QObject *parent)
    :QObject(parent)
{
	m_client = client;
    m_pTimer = nullptr;
}

GetTemperatureThread::~GetTemperatureThread()
{
    if(m_pTimer)
    {
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}

void GetTemperatureThread::startThread()
{
    m_pTimer = new QTimer;
    connect(m_pTimer, &QTimer::timeout, this, &GetTemperatureThread::slotGetTemp);
    m_pTimer->start(1000*60*3); // 3分钟查询一次室温
    slotGetTemp();
}

void GetTemperatureThread::slotGetTemp()
{
    // TODO: 执行查询室温逻辑，目前使用假数据 给主线程返回22度
    emit setTemperature(m_client->get_cur_temp());
}
