#pragma once
#include "surface.h"

namespace Tmpl8 { class Game; }

class Bullets
{
public:
	Bullets() = default;
	Bullets(float x, float y, float r, float speed, float beginX, float beginY, int direction);
	~Bullets() = default;
	void move(float deltaTime);
	void draw(const Tmpl8::Surface& surface) const;

	float getX() const { return x; }
	float getY() const { return y; }
	float getR() const { return r; }

	void setActive(bool active) { isActive = active; }
	bool getActive() const { return isActive; }



private:
	float x = 0.0f;
	float y = 0.0f;
	float r = 0.0f;
	float beginX = 0.0f;
	float beginY = 0.0f;
	float speed = 0.0f;
	int direction = 1;
	bool isActive = false;
};

