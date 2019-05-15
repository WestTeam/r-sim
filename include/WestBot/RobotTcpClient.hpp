// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_ROBOTTCPCLIENT_HPP_
#define WESTBOT_ROBOTTCPCLIENT_HPP_

#include <QObject>
#include <QTcpSocket>

class QByteArray;
class QString;

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

class RobotTcpClient : public QObject
{
    Q_OBJECT

public:
    RobotTcpClient( QObject* parent = nullptr );
    ~RobotTcpClient() override = default;

    bool connectTo( const QString& ip, quint16 port );
    void disconnectFrom();

    void send( const QByteArray& message );

    bool isConnected() const;

    void readTcpData();

signals:
    void connected();
    void disconnected();

    void updateRobotPos( uint8_t id, uint8_t color, int x, int y, int theta );
    void updatePuckPos( uint8_t id, uint8_t color, int x, int y, bool onTable = true );

private:
    void handleStateChange( QAbstractSocket::SocketState state );

    QTcpSocket _clientSocket;
    bool _isConnected;
    SimData _dataRcv;
};

}

#endif // WESTBOT_ROBOTTCPCLIENT_HPP_
