#pragma once
#include "surface.h"

namespace Tmpl8 { class Game; }

class Bullets
{
public:
	Bullets() = default;
	Bullets(float const x, float const y, float const r, float const speed, float const beginX, float const beginY, int const direction);
	~Bullets() = default;
	void move(float deltaTime);
	void draw(Tmpl8::Surface* surface);

	int getX() const { return x; }
	int getY() const { return y; }
	int get_r() const { return r; }

	bool isActive = false;
	void setActive(bool active) { isActive = active; }
	bool getActive() const { return isActive; }



private:
	float x = 0;
	float y = 0;
	float r = 0;
	float beginX = 0;
	float beginY = 0;
	float speed = 0.0f;
	int direction = 1;
};

