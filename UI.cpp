#include "UI.h"
#include <iostream>

UI::UI(Tmpl8::Surface* surface, std::vector<buttons> button) : //get the buttons
surface(surface), button(button), //call the correct screen or button
case_number(-1), button_detected(-1) //change it so it isn't 0 at the start
{
}

void UI::drawButton(int start, int end) const //draw the buttons that are called
{
	for (int i = start; i < end; i++)
	{
		surface->Box(button[i].x, button[i].y, button[i].x + button[i].x2, button[i].y + button[i].y2, 0xffffff);
	}
}

void UI::detectMouse(float mouse_x, float mouse_y) //get the position of the mouse
{
	this->mouse_x = mouse_x;
	this->mouse_y = mouse_y;
	//std::cout << mouse_x << ", " << mouse_y << std::endl;
}

void UI::detectButton(int start, int end) //which buttons should it detect
{
	for (int i = start; i < end; i++)
	{
		if (mouse_x <= button[i].x + button[i].x2 && 
			mouse_x >= button[i].x &&
			mouse_y <= button[i].y + button[i].y2 && 
			mouse_y >= button[i].y) //if the mouse is over the button
		{
			//std::cout << "detected" << std::endl;
			button_detected = i; //update the right button number
			break;
		}
		else
		{
			button_detected = -1;
		}
	}

}

void UI::mouseClick(bool clicked)
{
	if (clicked)
	{
		if (button_detected >= 0) //if clicked on a button
		{
			case_number = button_detected; //update another button number
			//std::cout << case_number << std::endl;
		}
	}
	else
	{
		case_number = -1;
	}
}

void UI::buttonCase(bool& show_startscreen, bool& show_game, bool& show_controls, bool& show_gameover, bool& show_win, 
	int& lives, int& collected, bool& resetTankPos, bool clicked, bool enabled) const
{
	//std::cout << "Case number: " << case_number << std::endl;
	switch (case_number) //look which button is called
	{
	case 0: //controls
		show_startscreen = false;
		show_controls = true;
		std::cout << "Controls button pressed" << std::endl;
		break;
	case 1: //play
		show_game = true;
		show_startscreen = false;
		show_gameover = false;
		std::cout << "Play button pressed" << std::endl;

		if (clicked && enabled)
		{
			resetTankPos = true;

			lives = 3;
			collected = 0;
		}

		break;
	case 2: //exit
		exit(0);
		break;
	case 3: //back in controls
		std::cout << "Back button pressed" << std::endl;
		show_startscreen = true;
		show_controls = false;
		break;
	case 4: //retry in game over screen
		show_game = true;
		show_gameover = false;
		std::cout << "retry button pressed" << std::endl;

		if (clicked && enabled)
		{
			resetTankPos = true;

			lives = 3;
			collected = 0;
		}
		break;
	case 5: //main menu in game over screen
		show_startscreen = true;
		show_gameover = false;
		show_game = false;
		std::cout << "menu button clicked" << std::endl;
		break;
	case 6: //retry in win screen
		show_game = true;
		show_win = false;
		std::cout << "retry button pressed" << std::endl;

		if (clicked && enabled)
		{
			resetTankPos = true;

			lives = 3;
			collected = 0;
		}
		break;
	case 7: //main menu in win screen
		show_startscreen = true;
		show_win = false;
		show_game = false;
		std::cout << "menu button clicked" << std::endl;
		break;
	case -1: //make sure that it doesn't immediately gets pressed
		break;
	}

}
	