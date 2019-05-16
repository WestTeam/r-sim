#ifndef CLIENTSTUFF_H
#define CLIENTSTUFF_H

#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

namespace WestBot {

typedef struct
{
    double x; // mm
    double y; // mm
    double theta; // rad
} __attribute__( ( packed ) ) RobotPos;

typedef struct
{
    uint8_t objectId;
    uint8_t objectType;
    uint8_t objectColor;
    RobotPos objectPos; // robotpos = x,y,teta en double
    double objectSize; // utile uniquement pour definir la taille du bras
    uint8_t objectMode; // utile seulement pour les palets
} __attribute__( ( packed ) ) SimData;


class ClientStuff : public QObject
{
    Q_OBJECT

public:
    ClientStuff(const QString hostAddress, int portVal, QObject *parent = 0);

    QTcpSocket *tcpSocket;
    bool getStatus();

    void send( const QByteArray& message );

public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(SimData msg);
    void updateRobotPos( uint8_t id, uint8_t color, int x, int y, int theta );
    void updatePuckPos( uint8_t id, uint8_t color, int x, int y, bool onTable = true );

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;
};

}

#endif // CLIENTSTUFF_H
