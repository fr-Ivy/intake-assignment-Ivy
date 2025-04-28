#pragma once
#include "template.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) 
	{ 
		if (button == 1) // Left mouse button
		{
			clicked = false;
		}
	}

	void MouseDown( int button ) 
	{ 
		if (button == 1)
		{
			clicked = true;
		}
	}

	void MouseMove(int x, int y) { mouseX += x; mouseY += y; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { theKey = key; }
	static bool CheckPos(float x, float y);

private:
	Surface* screen;
	int theKey = 0;
	int lives = 3;
	int collected = 0;

	bool show_game = false;
	bool show_startscreen = true;
	bool show_gameover = false;
	bool show_controls = false;
	bool exit = false;

	int mouseX = 0;
	int mouseY = 0;

	bool clicked = false;
};

}; // namespace Tmpl8