#pragma once
//#include "game.h"
#include "surface.h"
#include "Item.h"
#include "Bullets.h"

namespace Tmpl8 { class Game; }

class Tank
{
public:
	Tank() = default;
	Tank(float const posX, float const posY, int const frame, Tmpl8::Sprite* sprite, int const behaviour);
	~Tank() = default;
	void setPosition(float const posX, float const posY);
	void setFrame(int const frame);
	void Draw(Tmpl8::Surface& surface) const;
	void move(float const deltaTime);
	void Box(const Tmpl8::Surface& surface, Tmpl8::Pixel const color = 0) const;
	bool collision(const Tank& other) const;
	bool itemCollision(const Item& item) const;
	bool bulletCollision(const Bullets& bullets) const;

	bool isActive = false;
	void setActive(bool active) { isActive = active; }
	bool getActive() const { return isActive; }

private:
	float posX = 0.0f;
	float posY = 0.0f;
	int frame = 0.0f;
	Tmpl8::Sprite* sprite = nullptr;
	int behaviour = 0.0f;
	float beginX = 0.0f;
	float beginY = 0.0f;
	float seconds = 0.0f;
	float deltaTime1 = 0.0f;
	float deltaTime2 = 0.0f;
};


