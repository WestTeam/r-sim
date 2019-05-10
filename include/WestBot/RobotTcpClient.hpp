// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_ROBOTTCPCLIENT_HPP_
#define WESTBOT_ROBOTTCPCLIENT_HPP_

#include <QObject>
#include <QTcpSocket>

class QByteArray;
class QString;

namespace WestBot {

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

private:
    void handleStateChange( QAbstractSocket::SocketState state );

    QTcpSocket _clientSocket;
    bool _isConnected;
};

}

#endif // WESTBOT_ROBOTTCPCLIENT_HPP_
