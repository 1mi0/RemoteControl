#include "pch.h"
#include "SimplePacket.h"

SimplePacket::SimplePacket()
	: m_Params(nullptr)
	, m_Action(Action::ClickButton)
{
	m_Params = std::unique_ptr<std::vector<byte>>(new std::vector<byte>);
}

void SimplePacket::translatePacket(std::vector<byte>& packet)
{
	m_Params->clear();
	
	m_Action = (Action)(packet[0]);
	// Set the action
	// Add the params to the packet
	for (int i = 1; i < packet.size(); i++)
	{
		m_Params->push_back(packet[i]);
	}
}

void SimplePacket::constructPacket()
{
	m_Packet.push_back((byte)m_Action);
	std::for_each(m_Params.get()->begin(), m_Params.get()->end(), [&](byte& param) {
		m_Packet.push_back((byte)param);
		});
}

std::vector<byte> SimplePacket::getPacket()
{
	if (m_Packet.empty())
	{
		constructPacket();
	}

	return m_Packet;
}

byte SimplePacket::getParam(int index)
{
	return (*m_Params)[index];
}

void SimplePacket::addParam(byte param)
{
	m_Params->push_back(param);
}

void SimplePacket::addAction(Action action)
{
	m_Action = action;
}

Action SimplePacket::getAction()
{
	return m_Action;
}