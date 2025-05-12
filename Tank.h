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
	Tank(float posX, float posY, int frame, Tmpl8::Sprite* sprite, int behaviour);
	~Tank() = default;
	void setFrame(int frame);
	void Draw(Tmpl8::Surface& surface) const;
	void move(float deltaTime, bool& resetTankPos);
	void keyUp(int key);
	void keyDown(int key);
	void Box(const Tmpl8::Surface& surface, Tmpl8::Pixel color = 0) const;
	bool collision(const Tank& other) const;
	bool itemCollision(const Item& item) const;
	bool bulletCollision(const Bullets& bullets) const;

	bool isActive = false;
	void setActive(bool active) { isActive = active; }
	bool getActive() const { return isActive; }

	float getX() { return posX; }
	float getY() { return posY; }

private:
	float posX = 0.0f;
	float posY = 0.0f;
	int frame = 0;
	Tmpl8::Sprite* sprite = nullptr;
	int behaviour = 0;
	float beginX = 0.0f;
	float beginY = 0.0f;
};


