#pragma once 
#include "Global.h"

class TCPSocketManager
{
    std::list<sf::TcpSocket*> sockets;
    sf::TcpListener listener;
    sf::SocketSelector selector;

    bool* gameStart;

public:
    enum MessageTypes
    {
        LOGIN,
        MESSAGE,
        DISCONNECT,
        COUNT
    };

    TCPSocketManager(bool* gameStart);

    sf::Socket::Status Listen(unsigned short port, sf::IpAddress ip);
    void ServerSend(std::string mssg, sf::TcpSocket& senderSocket);
    void ServerSendAll(std::string message);
    void ClientSend(sf::Packet infoPack);
    void ServerReceive(sf::Packet receivedPacket, sf::TcpSocket& senderSocket);
    void ClientReceive(std::string* mssg);
    sf::Socket::Status Connect(unsigned short port, sf::IpAddress ip);
    void ClientDisconected(sf::TcpSocket& clientSocket);
    void Disconnect();
    void AddListener(unsigned short port);
    sf::TcpSocket* GetSocket();
};
