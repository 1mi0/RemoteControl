#pragma once

#include "pch.h"

struct Button
{
	WORD vk;
	byte id;
};

class Buttons
{
public:
	Buttons();
	Button* findButton(byte button);
	std::string* stringifyButton(byte button);
	std::string* stringifyButton(Button& button);
	bool ExecuteButton(byte button);

private:
	INPUT m_Input = { 0 };
	std::unique_ptr<std::vector<Button>> m_Buttons;
};

