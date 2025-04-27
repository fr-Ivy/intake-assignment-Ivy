#pragma once
#include "surface.h"
class Bullets
{
public:
	Bullets() = default;
	Bullets(int x, int y, float r, float speed, int beginY, int beginX);
	~Bullets() = default;
	void move();
	void draw(Tmpl8::Surface* surface);

	int getX() const { return x; }

	int getY() const { return y; }

	int get_r() const { return r; }


private:
	int x = 0;
	int y = 0;
	float r = 0;
	int beginY = 0;
	int beginX = 0;
	float speed = 0.0f;
};

