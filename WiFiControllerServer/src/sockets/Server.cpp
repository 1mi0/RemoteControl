#include "pch.h"
#include "Server.h"

int Server::setupWinSock()
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int isWSOk = WSAStartup(version, &data);

	return isWSOk;
}

Server::Server()
	: m_Socket(socket(AF_INET, SOCK_DGRAM, NULL))
	, m_ReceiveSocket(socket(AF_INET, SOCK_DGRAM, NULL))
{
	m_Hint.sin_addr.S_un.S_addr = ADDR_ANY;
	m_Hint.sin_family = AF_INET;
	m_Hint.sin_port = htons(PORT);
	ZeroMemory(&m_ClientInfo, sizeof(m_ClientInfo));
}

Server::~Server()
{
	closesocket(m_Socket);
	WSACleanup();
}

int Server::bindHint(SOCKADDR_IN* hint)
{
	return bind(m_ReceiveSocket, (SOCKADDR*)hint, sizeof(*hint));
}

std::vector<byte>* Server::receivePacket()
{
	SOCKADDR_IN hint;
	int clientSize = sizeof(hint);
	ZeroMemory(&hint, clientSize);
	ZeroMemory(&m_Buffer, sizeof(m_Buffer));

	int errorState = recvfrom(m_ReceiveSocket, m_Buffer, sizeof(m_Buffer), NULL, (SOCKADDR*)&hint, &clientSize);
	if (errorState == SOCKET_ERROR)
	{
		return nullptr;
	}

	memcpy(&m_ClientInfo, &hint, sizeof(hint));

	std::vector<byte>* bytes = new std::vector<byte>;
	byte bChar;
	for (char& c : m_Buffer)
	{
		bChar = static_cast<byte>(c);
		if (bChar == 0xFF)
		{
			std::cout << "End found! Char count => " << &c - m_Buffer << std::endl;
			break;
		}
		bytes->push_back(bChar);
	}

	if (bytes->empty())
	{
		std::cout << "Encountered error!!! Empty packet?" << std::endl;
		return nullptr;
	}

	return bytes;
}

bool Server::sendPacket(char* packet, SOCKADDR_IN* hint)
{
	int errorCode = sendto(m_Socket, packet, strlen(packet), NULL, (SOCKADDR*)hint, sizeof(*hint));
	return errorCode != SOCKET_ERROR;
}