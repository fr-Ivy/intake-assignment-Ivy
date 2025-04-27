#pragma once
#include "template.h"
#include "surface.h"

class Item
{
public:
	Item() = default;
	Item(float x, float y);
	~Item() = default;
	void setPosition(float x, float y);
	void move();
	void draw(Tmpl8::Surface* surface);
	float getX() const {return x;}
	float getY() const {return y;}

private:
	float x = 0.0f;
	float y = 0.0f;
};