#include "Bullets.h"
#include "game.h"
using namespace Tmpl8;

Bullets::Bullets(float const x, float const y, float const r, float const speed, float const beginX, float const beginY, int const direction)
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
        !Game::CheckPos(x + r, y - r))
    {
        x = beginX;
        y = beginY;
    }
}

void Bullets::draw(Surface& surface) const
{
    for (int i = 0; i < 64; i++)
    {
        float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
        surface.Line(x - r * sinf(r1), y - r * cosf(r1),
            x - r * sinf(r2), y - r * cosf(r2), 0xff0000);

        surface.Line(x - (r + 1) * sinf(r1), y - (r + 1) * cosf(r1),
            x - (r + 1) * sinf(r2), y - (r + 1) * cosf(r2), 0x0000000);
    }
}