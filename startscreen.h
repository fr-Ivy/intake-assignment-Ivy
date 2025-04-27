#pragma once
#include "surface.h"
#include <vector>

struct buttons
{
	int x, y, x2, y2;
};

class startscreen
{
public:
	startscreen() = default;
	startscreen(Tmpl8::Surface* surface, std::vector<buttons> button);
	~startscreen() = default;
	void drawButton();
	void detectMouse(int mouse_x, int mouse_y);
	void button1();

private:
	int x = 0;
	int y = 0;
	Tmpl8::Surface* surface;
	std::vector<buttons> button;
	int button_id = 0;
	int mouse_x = 0;
	int mouse_y = 0;
};