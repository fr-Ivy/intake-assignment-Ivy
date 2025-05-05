#include "Item.h"
#include "game.h"

using namespace Tmpl8;

Item::Item(float const x, float const y)
{
	this->x = x;
	this->y = y;

}

void Item::setPosition(float const x, float const y)
{
	this->x = x;
	this->y = y;
}

void Item::move()
{
    float nx = x;
    float ny = y;

    do
    {
        nx = IRand(ScreenWidth);
        ny = IRand(ScreenHeight);

    } while (!Game::CheckPos(nx, ny) ||
        !Game::CheckPos(nx + 15.0f, ny + 15.0f) ||
        !Game::CheckPos(nx + 15.0f, ny) ||
        !Game::CheckPos(nx, ny + 15.0f));

    x = nx;
    y = ny;

    /*
    do
    {
         nx = IRand(SW);
         ny = IRand(SH):
    } while(a && b);
    // Reverse logic
    do
    {
          nx = IRand(SW);
         ny = IRand(SH):
    } while(!a || !b);
*/
}


void Item::draw(Tmpl8::Surface& surface)
{
	surface.Box(x, y, x + 15, y + 15, 0x204299);
}