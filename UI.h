#pragma once
#include "surface.h"
#include <vector>

struct buttons
{
	float x, y, x2, y2;
};

class UI
{
public:
	UI() = default;
	UI(Tmpl8::Surface* surface, std::vector<buttons> button);
	~UI() = default;
	void drawButton(int start, int end) const;
	void detectMouse(float mouse_x, float mouse_y);
	void detectButton(int start, int end);
	void mouseClick(bool clicked);
	void buttonCase(bool& show_startscreen, bool& show_game, bool& show_controls, bool& show_gameover, bool& show_win, 
		int& lives, int& collected, bool& resetTankPos, bool clicked, bool enabled) const;


private:
	Tmpl8::Surface* surface;
	std::vector<buttons> button;
	float mouse_x = 0.0f;
	float mouse_y = 0.0f;
	int case_number = 0;
	int button_detected = 0;
};