#include "Item.h"
#include "game.h"
#include "template.h"

using namespace Tmpl8;

Item::Item(float const x, float const y, Tmpl8::Sprite* sprite)
{
	this->x = x;
	this->y = y;
    this->sprite = sprite;
}

void Item::move()
{
    float nx = x;
    float ny = y;

    do
    {
        //chose random position
        nx = static_cast<float>(IRand(ScreenWidth)); 
        ny = static_cast<float>(IRand(ScreenHeight)); //get random positions

    } while (!Game::CheckPos(nx, ny) ||
        !Game::CheckPos(nx + size, ny + size) ||
        !Game::CheckPos(nx + size, ny) ||
        !Game::CheckPos(nx, ny + size)); //check if item isn't colliding with a wall

    x = nx;
    y = ny;
}

void Item::rotate(Tmpl8::Surface& surface, float deltaTime)
{
    frameSeconds -= deltaTime;
    if (frameSeconds <= 0.0f)
    {
        frame = (frame + 1) % sprite->Frames();
        sprite->SetFrame(frame);
        frameSeconds = 100.0f;
    }
}

void Item::draw(Tmpl8::Surface& surface) const
{
    if (sprite)
    {
        sprite->Draw(&surface, x, y);
    }
}

void Item::Box(const Tmpl8::Surface& surface, Tmpl8::Pixel color) const
{
    surface.Box(x, y, x + size, y + size, color);
}