﻿#ifndef AUTORECOGINZE_H
#define AUTORECOGINZE_H

#include <QObject>
#include <QMap>
#include <QHostAddress>
#include <QUdpSocket>

class AutoRecognize : public QObject
{
    Q_OBJECT
public:
    enum{
        NO_CONNECT,
        USB_CONNECTED=0x02,
        MOTOR_CONNECTED=0x04,
    };
    static AutoRecognize * getInstance();

    void startRecognize(bool bRetry = false);
    void addMototInfo(quint8 nDeviceId,quint32 nDeviceMac);
    QMap<quint8,quint32> getMotorsInfo()const{return m_motorsInfo;}
protected:
    explicit AutoRecognize(QObject *parent = 0);
    void findCommunicationUnits();
signals:

public slots:
    void openFailed();
    void waitTimeout();
private slots:
    void onIpBroadcast();
private:
    class GC{
    public:
        ~GC()
        {
            if(m_pAutoRecognize!=nullptr)
            {
                delete m_pAutoRecognize;
                m_pAutoRecognize = nullptr;
            }
        }
        static GC gc;
    };
private:
    static AutoRecognize * m_pAutoRecognize;
    bool m_bFindAvaliable;
    bool m_bTryNext;
    //QList <QSerialPortInfo> m_portList;
    QMap<quint8,quint32> m_motorsInfo;
    QUdpSocket * m_pSocket;
    QVector<QHostAddress> m_addrVector;
};

#endif // AUTORECOGINZE_H
