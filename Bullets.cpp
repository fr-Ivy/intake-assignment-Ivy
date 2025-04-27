#include "Bullets.h"
#include "game.h"
using namespace Tmpl8;

Bullets::Bullets(int x, int y, float r, float speed, int beginY, int beginX)
{
	this->x = x;
	this->y = y;
    this->r = r;
    this->beginY = beginY;
    this->beginX = beginX;
    this->speed = speed;
}


void Bullets::move()
{
    if (y)
    {
        y -= speed;
    }
    if (!Game::CheckPos(x - r, y - r) ||
        !Game::CheckPos(x + r, y + r) ||
        !Game::CheckPos(x - r, y + r) ||
        !Game::CheckPos(x + r, y - r))
    {
        y = beginY;
    }
}

void Bullets::draw(Surface* surface)
{
    for (int i = 0; i < 64; i++)
    {
        float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
        surface->Line(x - r * sinf(r1), y - r * cosf(r1),
            x - r * sinf(r2), y - r * cosf(r2), 0xff0000);

        surface->Line(x - (r + 1) * sinf(r1), y - (r + 1) * cosf(r1),
            x - (r + 1) * sinf(r2), y - (r + 1) * cosf(r2), 0x0000000);
    }
}