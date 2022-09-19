#pragma once
#include "pch.h"

template<typename T>
class LockQueue;

class Application
{
public:
	Application();

	void run();
	void receiveLoop(int id);
	void managePacket(std::vector<byte> packetReceived);

	template<typename TInputIter>
	std::string makeHexString(TInputIter first, TInputIter last);
private:

	std::unique_ptr<Server> m_Server;
	std::unique_ptr<Buttons> m_Buttons;
	std::unique_ptr<ctpl::thread_pool> m_Pool;
	std::unique_ptr<std::queue<std::vector<byte>>> m_PacketQueue;
	std::mutex m_Mutex;
};

