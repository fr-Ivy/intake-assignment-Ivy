#include "startscreen.h"
#include <iostream>

startscreen::startscreen(Tmpl8::Surface* surface, std::vector<buttons> button) : surface(surface), button(button)
{
}

void startscreen::drawButton()
{
	for (int i = 0; i < button.size(); i++)
	{
		surface->Box(button[i].x, button[i].y, button[i].x + button[i].x2, button[i].y + button[i].y2, 0xffffff);
	}
}

void startscreen::detectMouse(int mouse_x, int mouse_y)
{
	this->mouse_x = mouse_x;
	this->mouse_y = mouse_y;
	//std::cout << mouse_x << ", " << mouse_y << std::endl;
}

void startscreen::detectButton()
{
	for (int i = 0; i < button.size(); i++)
	{
		if (mouse_x <= button[i].x + button[i].x2 && 
			mouse_x >= button[i].x &&
			mouse_y <= button[i].y + button[i].y2 && 
			mouse_y >= button[i].y)
		{
			//std::cout << "detected" << std::endl;
			button_detected = i;
			break;
		}
		else
		{
			button_detected = 3;
		}
	}
}

void startscreen::mouseClick(bool clicked)
{
	for (int i = 0; i < button.size(); i++)
	{
		if (button_detected >= 0 && clicked)
		{
			case_number = button_detected;
			std::cout << case_number << std::endl;
			clicked = false;
			break;
		}
	}
}

void startscreen::buttonCase(bool& show_startscreen, bool& show_game)
{
	//std::cout << case_number << std::endl;
	switch (case_number)
	{
	case 0: //controls
		break;

	case 1: //play
		show_game = true;
		show_startscreen = false;
		break;
	case 2: //exit

		break;

	case 3: //might use it?
		break;
	}
}