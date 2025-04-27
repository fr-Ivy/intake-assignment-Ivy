/*#include "Gun.h"

Gun::Gun(float x, float y, int frame, Tmpl8::Sprite* sprite, int behaviour)
{
	this->x = x;
	this->y = y;
	this->frame = frame;
	this->sprite = sprite;
	this->behaviour = behaviour;
	this->beginY = y;
}

void Gun::getPosition(float x, float y)
{
	this->x = x;
	this->x = x;
}

void Gun::getFrame(int frame)
{
	this->frame = frame;
}

void Gun::moveBullets(float deltaTime)
{
	static int seconds = 0;
	seconds += deltaTime;
	if (seconds >= 5)
	{
		if (y > 32)
		{
			y--;
		}

		if (y <= 32)
		{
			y = beginY;
		}
		seconds = 0;
	}

}

void Gun::draw(Tmpl8::Surface* surface)
{
	if (sprite)
	{
			sprite->Draw(surface, x, y);
			sprite->SetFrame(frame);
	}
}
*/