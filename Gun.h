/*#pragma once
#include "game.h"
#include "surface.h"

class Gun
{
public:
	Gun() = default;
	Gun(float x, float y, int frame, Tmpl8::Sprite* sprite, int behaviour);
	~Gun() = default;
	void getPosition(float x, float y);
	void getFrame(int frame);
	void moveBullets(float deltaTime);
	void draw(Tmpl8::Surface* surface);

private:
	float x = 0.0f;
	float y = 0.0f;
	int frame = 0;
	Tmpl8::Sprite* sprite = nullptr;
	int behaviour = 0;
	int number = 0;
	float beginY = 0;
};
*/

