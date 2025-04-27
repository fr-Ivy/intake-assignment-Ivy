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
	//std::cout << mouse_x << ", " << mouse_y << std::endl;
}

void startscreen::detectButton()
{

}

void startscreen::buttonCase()
{

}