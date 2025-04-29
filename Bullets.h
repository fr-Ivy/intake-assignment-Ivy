#pragma once
#include "surface.h"
class Bullets
{
public:
	Bullets() = default;
	Bullets(float x, float y, float r, float speed, float beginX, float beginY);
	~Bullets() = default;
	void move(float deltaTime);
	void draw(Tmpl8::Surface* surface);

	int getX() const { return x; }

	int getY() const { return y; }

	int get_r() const { return r; }


private:
	float x = 0;
	float y = 0;
	float r = 0;
	float beginX = 0;
	float beginY = 0;
	float speed = 0.0f;
};

