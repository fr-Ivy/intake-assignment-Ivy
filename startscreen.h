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
	void drawButton(int const start, int const end) const;
	void detectMouse(int mouse_x, int mouse_y);
	void detectButton(int const start, int const end);
	void mouseClick(bool clicked);
	void buttonCase(bool& show_startscreen, bool& show_game, bool& show_controls) const;

private:
	int x = 0;
	int y = 0;
	Tmpl8::Surface* surface;
	std::vector<buttons> button;
	int mouse_x = 0;
	int mouse_y = 0;
	int case_number = 0;
	int button_detected = 0;
};