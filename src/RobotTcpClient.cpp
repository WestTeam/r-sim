// Copyright (c) 2019 All Rights Reserved WestBot

#include <QByteArray>
#include <QString>

#include "include/WestBot/RobotTcpClient.hpp"

using namespace WestBot;

RobotTcpClient::RobotTcpClient( QObject* parent )
    : QObject( parent )
    , _isConnected( false )
{
    connect(
        & _clientSocket,
        & QAbstractSocket::stateChanged,
        this,
        & RobotTcpClient::handleStateChange );

    connect(
        & _clientSocket,
        & QAbstractSocket::readyRead,
        this,
        & RobotTcpClient::readTcpData );
}

bool RobotTcpClient::connectTo( const QString& ip, quint16 port )
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

void RobotTcpClient::disconnectFrom()
{
    _clientSocket.disconnectFromHost();
    _isConnected = false;
}

bool RobotTcpClient::isConnected() const
{
    return _isConnected;
}

void RobotTcpClient::send( const QByteArray& message )
{
    _clientSocket.write( message, message.length() );
    qDebug() << "Data" << message;
}

void RobotTcpClient::readTcpData()
{
    _clientSocket.read( (char*) & _dataRcv.objectId, sizeof( SimData ) );

    qDebug() << ">>>>RCV DATA" << _dataRcv.objectPos.x;
}

// Private methods
void RobotTcpClient::handleStateChange( QAbstractSocket::SocketState state )
{
    if( state == QAbstractSocket::ConnectedState )
    {
        emit RobotTcpClient::connected();
        _isConnected = true;
    }
    else
    {
        emit RobotTcpClient::disconnected();
        _isConnected = false;
    }
}
