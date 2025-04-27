#include "startscreen.h"

startscreen::startscreen(Tmpl8::Surface* surface, std::vector<buttons> button) : surface(surface), button(button)
{
}

void startscreen::drawButton()
{
	for (int i = 0; i < button.size(); i++)
	{
		surface->Box(button[i].x, button[i].y, button[i].x + 200, button[i].y + 60, 0xffffff);
	}
}