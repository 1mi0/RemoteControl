#pragma once
#include "pch.h"
#include "Buttons.h"

enum class Action
{
	Pulse = 0x0,
	ClickButton = 0x1
};

class SimplePacket
{
public:
	SimplePacket();

	void translatePacket(std::vector<byte>& packet);

	void constructPacket();
	std::vector<byte> getPacket();

	byte getParam(int index);
	void addParam(byte param);

	Action getAction();
	void addAction(Action action);
private:
	std::vector<byte> m_Packet;

	Action m_Action;
	std::unique_ptr<std::vector<byte>> m_Params;
};

