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
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { theKey = key; }
	static bool CheckPos(float x, float y);
private:
	Surface* screen;
	int theKey = 0;
	int lives = 3;
	int collected = 0;


	bool show_Game = false;
	bool show_startscreen = true;

};

}; // namespace Tmpl8