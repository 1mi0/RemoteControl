#pragma once

#include "pch.h"

#define PORT 12433

class Server
{
public:
	static int setupWinSock();
	
	Server();
	~Server();
	int bindHint(SOCKADDR_IN* hint);
	inline int bindDefault() { return bindHint(&m_Hint); }

	bool sendPacket(char* packet, SOCKADDR_IN* hint);
	inline bool respond(char* packet) { return sendPacket(packet, &m_ClientInfo); }
	std::vector<byte>* receivePacket();

	inline SOCKADDR_IN* getClientHint() { return &m_ClientInfo; }

private:
	SOCKET m_Socket;
	SOCKET m_ReceiveSocket;
	SOCKADDR_IN m_Hint;
	SOCKADDR_IN m_ClientInfo;
	char m_Buffer[1024];
};

