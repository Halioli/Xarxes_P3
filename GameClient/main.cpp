#pragma once
#include "Global.h"
#include "TCPSocketManager.h"
#include "ChessBoard.h"

using namespace sf;

const unsigned short PORT = 5555;
const sf::IpAddress IP = "127.0.0.1";
bool applicationRunning = true;
bool gameStart = false;

enum Mode
{
	SERVER,
	CLIENT,
	COUNT
};

// Function to read from console (adapted for threads)
void GetLineFromCin(std::string* mssg)
{
	while (applicationRunning)
	{
		std::string line;
		std::getline(std::cin, line);
		mssg->assign(line);
	}
}

void OpenReceiveThread(TCPSocketManager* _tcpSocketManager, std::string* _mssg)
{
	while (applicationRunning)
	{
		_tcpSocketManager->ClientReceive(_mssg);
	}
}

void OpenListener(TCPSocketManager* _tcpSocketManager)
{
	_tcpSocketManager->AddListener(PORT);

	while (applicationRunning)
	{
		_tcpSocketManager->Listen(PORT, IP);
	}
}

bool SendLogic(TCPSocketManager* tcpSocketManager, Mode mode, sf::Packet mssgInfo, std::string* message)
{
	if (message->size() > 0)
	{
		if (*message == "exit")
		{
			// Desconection
			switch (mode)
			{
			case SERVER:
				tcpSocketManager->ServerSendAll("DISCONNECT");
				break;
			case CLIENT:
				std::cout << "CLIENT DISCONECT" << std::endl;
				mssgInfo << tcpSocketManager->DISCONNECT << *message;
				tcpSocketManager->ClientSend(mssgInfo);
				break;
			default:
				break;
			}

			applicationRunning = false;
			message->clear();
			return false;
		}
		else
		{
			switch (mode)
			{
			case SERVER:
				tcpSocketManager->ServerSendAll(*message);
				break;
			case CLIENT:
				mssgInfo << tcpSocketManager->MESSAGE << *message;
				tcpSocketManager->ClientSend(mssgInfo);
				break;
			default:
				break;
			}
			message->clear();
		}
	}

	return true;
}

void Server()
{
	std::cout << "Client 2 mode running" << std::endl;

	TCPSocketManager tcpSocketManager(&gameStart);

	sf::Packet infoPacket;
	std::string sendMessage, receiveMessage;

	// Logic for receiving
	std::thread tcpScoketListen(OpenListener, &tcpSocketManager);
	tcpScoketListen.detach();

	std::thread getLines(GetLineFromCin, &sendMessage);
	getLines.detach();

	while (applicationRunning)
	{
		// Logic for sending
		if (SendLogic(&tcpSocketManager, Mode::SERVER, infoPacket, &sendMessage) != true)
		{
			break;
		}
	}

	tcpSocketManager.Disconnect();
}

void Client()
{
	std::cout << "Client 1 mode running" << std::endl;

	TCPSocketManager tcpSocketManager(&gameStart);

	// client connect
	sf::Socket::Status status = tcpSocketManager.Connect(PORT, IP);

	sf::Packet infoPacket;
	std::string sendMessage, receiveMessage;

	// Logic for receiving
	std::thread tcpSocketReceive(OpenReceiveThread, &tcpSocketManager, &receiveMessage);
	tcpSocketReceive.detach();

	std::thread getLines(GetLineFromCin, &sendMessage);
	getLines.detach();

	while (applicationRunning)
	{
		if (status != sf::Socket::Done)
		{
			applicationRunning = false;
			break;
		}

		// Logic for sending
		if (SendLogic(&tcpSocketManager, Mode::CLIENT, infoPacket, &sendMessage) != true)
		{
			break;
		}
	}

	sendMessage = "exit";
	SendLogic(&tcpSocketManager, Mode::CLIENT, infoPacket, &sendMessage);
	tcpSocketManager.Disconnect();
}

void main()
{
	int server_mode;
	std::string mode_str;
	std::cout << "Select a mode: (1) client-1, (2) client-2" << std::endl;
	std::cin >> mode_str;
	server_mode = std::stoi(mode_str);
	bool facistPieces;

	if (server_mode == 1)
	{
		std::thread clientThread(Client);
		clientThread.detach();
		facistPieces = true;
	}
	else if (server_mode == 2)
	{
		std::thread serverThread(Server);
		serverThread.detach();
		facistPieces = false;
	}

	while (!gameStart)
	{
		Sleep(100);
	}
	ChessBoard graphics;
	graphics.run(facistPieces);
}