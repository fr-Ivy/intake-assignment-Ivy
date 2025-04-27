#pragma once
#include "game.h"
#include "surface.h"
#include "Item.h"
#include "Bullets.h"

class Tank
{
public:
	Tank() = default;
	Tank(float posX, float posY, int frame, Tmpl8::Sprite* sprite, float behaviour);
	~Tank() = default;
	void setPosition(float posX, float posY);
	void setFrame(int frame);
	void Draw(Tmpl8::Surface* surface);
	void move(float deltaTime);
	void Box(Tmpl8::Surface* surface, Tmpl8::Pixel color) const;
	bool collision(const Tank& other) const;
	bool itemCollision(const Item& item) const;
	bool bulletCollision(const Bullets& bullets) const;
	bool circleRect(float circle_x, float circle_y, float circle_r, float square_x1, float square_y1, float square_x2, float square_y2);



private:
	float posX = 0.0f;
	float posY = 0.0f;
	int frame = 0.0f;
	Tmpl8::Sprite* sprite = nullptr;
	float behaviour = 0.0f;
	float beginY = 0.0f;
	float seconds = 0.0f;
};


