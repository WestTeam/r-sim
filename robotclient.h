// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef ROBOTCLIENT_H
#define ROBOTCLIENT_H

#include <QObject>
#include <QTcpSocket>

class QByteArray;
class QString;

class RobotClient : public QObject
{
    Q_OBJECT

public:
    RobotClient( QObject* parent = nullptr );
    ~RobotClient() override = default;

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

#endif // ROBOTCLIENT_HPP_
