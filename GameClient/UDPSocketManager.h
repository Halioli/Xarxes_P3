#pragma once 
#include <SFML\Network.hpp>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>

class UDPSocketManager
{
    std::list<sf::UdpSocket*> sockets;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::vector<std::string> usernames;

public:
    enum MessageTypes
    {
        LOGIN,
        MESSAGE,
        DISCONNECT,
        COUNT
    };

    sf::Socket::Status Listen(unsigned short port, sf::IpAddress ip);
    void ServerSend(std::string mssg, sf::UdpSocket& senderSocket);
    void ServerSendAll(std::string message);
    void ClientSend(sf::Packet infoPack);
    void ServerReceive(sf::Packet receivedPacket, sf::UdpSocket& senderSocket);
    void ClientReceive(std::string* mssg);
    sf::Socket::Status Connect(unsigned short port, sf::IpAddress ip);
    void ClientDisconected(std::string username, sf::UdpSocket& clientSocket);
    void Disconnect();
    void AddListener(unsigned short port);
    sf::UdpSocket* GetSocket();
};
