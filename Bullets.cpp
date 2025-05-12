#include "Bullets.h"
#include "game.h"
#include "template.h"

using namespace Tmpl8;

Bullets::Bullets(float x, float y, float r, float speed, float beginX, float beginY, int direction) //get properties
{
	this->x = x;
	this->y = y;
    this->r = r;
    this->beginX = beginX;
    this->beginY = beginY;
    this->speed = speed;
    this->direction = direction;
}


void Bullets::move(float deltaTime)
{
    deltaTime /= 1000.0f;
    
    if (direction == 1)
    {
        y -= speed * deltaTime;
    }

    if (direction == 2)
    {
        y += speed * deltaTime;
    }

    if (direction == 3)
    {
        x += speed * deltaTime;
    }

    if (direction == 4)
    {
        x -= speed * deltaTime;
    }

    if (direction == 5)
    {
        x += speed * deltaTime;
        y -= speed * deltaTime;
    }

    if (direction == 6)
    {
        x -= speed * deltaTime;
        y -= speed * deltaTime;
    }

    if (direction == 7)
    {
        x += speed * deltaTime;
        y += speed * deltaTime;
    }

    if (direction == 8)
    {
        x -= speed * deltaTime;
        y += speed * deltaTime;
    }

    if (!Game::CheckPos(x - r, y - r) ||
        !Game::CheckPos(x + r, y + r) ||
        !Game::CheckPos(x - r, y + r) ||
        !Game::CheckPos(x + r, y - r)) //checks if the circle doesn't collide with the walls
    {
        x = beginX;
        y = beginY;
    }
}

void Bullets::draw(const Surface& surface) const
{
    for (int i = 0; i < 64; i++) //draw a dot 64 times
    {
        float r1 = static_cast<float>(i) * PI / 32, r2 = static_cast<float>(i + 1) * PI / 32; //gets the angle
        surface.Line(x - r * sinf(r1), y - r * cosf(r1), //draw the circle at the right radius
            x - r * sinf(r2), y - r * cosf(r2), 0xff0000);

        surface.Line(x - (r + 1) * sinf(r1), y - (r + 1) * cosf(r1),
            x - (r + 1) * sinf(r2), y - (r + 1) * cosf(r2), 0x0000000);
    }
}