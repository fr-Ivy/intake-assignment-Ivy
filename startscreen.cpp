#include "startscreen.h"
#include <iostream>

startscreen::startscreen(Tmpl8::Surface* surface, std::vector<buttons> button) : surface(surface), button(button), case_number(-1), button_detected(-1)
{
}

void startscreen::drawButton_startscreen() const
{
	for (int i = 0; i < 3; i++)
	{
		surface->Box(button[i].x, button[i].y, button[i].x + button[i].x2, button[i].y + button[i].y2, 0xffffff);
	}
}

void startscreen::drawButton_controls() const //not active
{
	for (int i = 3; i < 4; i++)
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

void startscreen::detectButton(int const start, int const end) //which buttons should it detect
{
	for (int i = start; i < end; i++)
	{
		if (mouse_x <= button[i].x + button[i].x2 && 
			mouse_x >= button[i].x &&
			mouse_y <= button[i].y + button[i].y2 && 
			mouse_y >= button[i].y)
		{
			std::cout << "detected" << std::endl;
			button_detected = i;
			break;
		}
		else
		{
			button_detected = -1;
		}
	}

}

void startscreen::mouseClick(bool clicked)
{
	if (button_detected >= 0 && clicked && button_detected < button.size())
	{
		case_number = button_detected;
		//std::cout << case_number << std::endl;
	}
}

void startscreen::buttonCase(bool& show_startscreen, bool& show_game, bool& show_controls) const
{
	//std::cout << "Case number: " << case_number << std::endl;
	switch (case_number)
	{
	case 0: // controls
		show_startscreen = false;
		show_controls = true;
		//std::cout << "Controls button pressed" << std::endl;
		break;
	case 1: // play
		show_game = true;
		show_startscreen = false;
		//std::cout << "Play button pressed" << std::endl;
		break;
	case 2: // exit
		exit(0);
		//std::cout << "Exit button pressed" << std::endl;
		break;
	case 3:
		//std::cout << "Back button pressed" << std::endl;
		show_startscreen = true;
		show_controls = false;
		break;
	}
}
