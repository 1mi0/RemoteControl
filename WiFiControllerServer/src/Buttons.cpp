#include "pch.h"
#include "Buttons.h"

struct newString
{
	std::string str;

	newString()
	{
		std::cout << "Constructing!!" << std::endl;
	}
	~newString()
	{
		std::cout << "Destructing!!" << std::endl;
	}
};

Buttons::Buttons()
{
	m_Buttons = std::unique_ptr<std::vector<Button>>(new std::vector<Button>);

	m_Buttons->push_back({ VK_RIGHT,	0x0 });
	m_Buttons->push_back({ VK_LEFT,		0x1 });
	m_Buttons->push_back({ VK_UP,		0x2 });
	m_Buttons->push_back({ VK_DOWN,		0x3 });
	m_Buttons->push_back({ VK_SPACE,	0x4 });
	m_Buttons->push_back({ VK_RETURN,	0x5 });
}

Button* Buttons::findButton(byte button)
{
	DWORD VK = -1;
	for (int i = 0; i < m_Buttons->size(); i++)
	{
		if ((*m_Buttons)[i].id == button)
		{
			return &((*m_Buttons)[i]);
		}
	}

	return nullptr;
}

std::string* Buttons::stringifyButton(byte button)
{
	Button* bButton = findButton(button);
	if (bButton == nullptr)
	{
		return new std::string("");
	}

	return stringifyButton(*bButton);
}

std::string* Buttons::stringifyButton(Button& button)
{
	switch (button.id)
	{
	case 0x0:
		return new std::string("Right");
		break;
	case 0x1:
		return new std::string("Left");
		break;
	case 0x2:
		return new std::string("Up");
		break;
	case 0x3:
		return new std::string("Down");
		break;
	case 0x4:
		return new std::string("Space");
		break;
	case 0x5:
		return new std::string("Return");
		break;
	}

	return new std::string("");
}

bool Buttons::ExecuteButton(byte button)
{
	Button* bButton = findButton(button);
	if (bButton == nullptr)
	{
		return false;
	}
	std::cout << "Executing button" << std::endl;

	m_Input.type = INPUT_KEYBOARD;
	m_Input.ki.wVk = bButton->vk;
	SendInput(1, &m_Input, sizeof(m_Input));
	ZeroMemory(&m_Input, sizeof(m_Input));
	m_Input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &m_Input, sizeof(m_Input));
	ZeroMemory(&m_Input, sizeof(m_Input));

	return true;
}