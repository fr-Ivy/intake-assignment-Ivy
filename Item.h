#pragma once
#include "surface.h"

class Item
{
public:
	Item() = default;
	Item(float x, float y, Tmpl8::Sprite* sprite);
	~Item() = default;
	void setPosition(float x, float y);
	void move();
	void Box(const Tmpl8::Surface& surface, Tmpl8::Pixel color) const;
	void draw(Tmpl8::Surface& surface) const;
	float getX() const {return x;}
	float getY() const {return y;}
private:
	float x = 0.0f;
	float y = 0.0f;
	Tmpl8::Sprite* sprite = nullptr;
};