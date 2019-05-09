// Copyright (c) 2019 All Rights Reserved WestBot

#include <QByteArray>
#include <QString>

#include "RobotClient.h"

RobotClient::RobotClient( QObject* parent )
    : QObject( parent )
    , _isConnected( false )
{
    connect(
        & _clientSocket,
        & QAbstractSocket::stateChanged,
        this,
        & RobotClient::handleStateChange );

    connect(
        & _clientSocket,
        & QAbstractSocket::readyRead,
        this,
        & RobotClient::readTcpData );

}

bool RobotClient::connectTo( const QString& ip, quint16 port )
{
    _clientSocket.connectToHost( ip, port );

    if( ! _clientSocket.waitForConnected( 3000 ) )
    {
        _isConnected = false;
        return _isConnected;
    }

    _isConnected = true;
    return _isConnected;
}

void RobotClient::disconnectFrom()
{
    _clientSocket.disconnectFromHost();
    _isConnected = false;
}

bool RobotClient::isConnected() const
{
    return _isConnected;
}

void RobotClient::send( const QByteArray& message )
{
    _clientSocket.write( message, message.length() );
    qDebug() << "Data" << message;
}

void RobotClient::readTcpData()
{
    QByteArray data = _clientSocket.readAll();
}

// Private methods
void RobotClient::handleStateChange( QAbstractSocket::SocketState state )
{
    if( state == QAbstractSocket::ConnectedState )
    {
        emit RobotClient::connected();
        _isConnected = true;
    }
    else
    {
        emit RobotClient::disconnected();
        _isConnected = false;
    }
}
