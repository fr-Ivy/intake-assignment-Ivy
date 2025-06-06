#include "Tank.h"
#include "game.h"
#include "surface.h"
#include <iostream> // cout
#define WIN32_LEAN_AND_MEAN
#include <SDL.h>

using namespace Tmpl8;

//saving stuff
Tank::Tank(float posX, float posY, int frame, Tmpl8::Sprite* sprite, int behaviour)
{
    this->posX = posX;
    this->posY = posY;
    this->frame = frame;
    this->sprite = sprite;
    this->behaviour = behaviour;
    this->beginX = posX;
    this->beginY = posY;
}

void Tank::setFrame(int frame)
{
    this->frame = frame;
}

//draw sprite
void Tank::Draw(Tmpl8::Surface& surface) const
{
    if (sprite)
    {
    	sprite->SetFrame(frame);
    	sprite->Draw(&surface, posX - 10, posY - 7);
    }
}

//keys
float w = 0.0f;
float a = 0.0f;
float s = 0.0f;
float d = 0.0f;

void Tank::keyUp(int key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        w = 0.0f;
        break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        a = 0.0f;
        break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        s = 0.0f;
        break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        d = 0.0f;
        break;
    }
}

void Tank::keyDown(int key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        w = 1.0f;
        break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        a = 1.0f;
        break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        s = 1.0f;
        break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        d = 1.0f;
        break;
    }
}

void Tank::move(float deltaTime, bool& resetTankPos)
{
    deltaTime /= 1000.0f;
    if (behaviour == 0) //player
    {
        float moveSpeed = 200.0f;
        float nx = posX;
        float ny = posY;

        if (a == 1.0f) {
            nx -= moveSpeed * deltaTime;
            frame = 12;
        }
        if (d == 1.0f) {
            nx += moveSpeed * deltaTime;
            frame = 4;
        }
        if (w == 1.0f) {
            ny -= moveSpeed * deltaTime;
            frame = 8;
        }
        if (s == 1.0f) {
            ny += moveSpeed * deltaTime;
            frame = 0;
        }

        //check if the tank isn't colliding with a wall or gun
        if (Game::CheckPos(nx, ny) &&
            Game::CheckPos(nx + size, ny + size) &&
            Game::CheckPos(nx + size, ny) &&
            Game::CheckPos(nx, ny + size) && 
            Game::CheckGun(nx, ny) &&
            Game::CheckGun(nx + size, ny + size) &&
            Game::CheckGun(nx + size, ny) &&
            Game::CheckGun(nx, ny + size)) //check if the tank isn't colliding with a wall
        {
            posX = nx;
            posY = ny;
        }

        if (resetTankPos) //reset the tank position if resetTankPos is called
        {
            posX = beginX;
            posY = beginY;
            resetTankPos = false;
        }
    }

    //enemy tanks
    if (behaviour == 1)
    {
    	posY -= 100.0f * deltaTime;
    	frame = 8;
    }

    if (behaviour == 2)
    {
        posX += 100.0f * deltaTime;
        frame = 12;
    }

    if (behaviour == 3)
    {
        posY += 100.0f * deltaTime;
        frame = 0;
    }

    if (behaviour == 4)
    {
        posX -= 100.0f * deltaTime;
        frame = 4;
    }

    //check if the tank isn't colliding with a wall or gun
    if (!Game::CheckPos(posX, posY) ||
		!Game::CheckPos(posX + size, posY + size) ||
		!Game::CheckPos(posX + size, posY) ||
		!Game::CheckPos(posX, posY + size) && behaviour > 1) //check if the tank isn't colliding with a wall
    {
    	posY = beginY;
    	posX = beginX;
    }
}

void Tank::Box(const Tmpl8::Surface& surface, Tmpl8::Pixel color) const
{
    surface.Box(posX, posY, posX + size, posY + size, color);
}

//collisions
bool Tank::collision(const Tank& other) const
{
	if (posX <= other.posX + size && posY <= other.posY + size && posX + size >= other.posX && posY + size >= other.posY)
	{
		//std::cout << "Hit by a tank!" << std::endl;
		return true;
	}
	return false;
}

bool Tank::itemCollision(const Item& item) const
{

    if (posX <= item.getX() + item.getSize() && posY <= item.getY() + item.getSize() && posX + size >= item.getX() && posY + size >= item.getY())
    {
        //std::cout << "Item, YAYYYY!" << std::endl;
        return true;
    }
    return false;
}

bool Tank::bulletCollision(const Bullets& bullets) const
{

    if (posX - bullets.getR() <= bullets.getX() &&
        posY - bullets.getR() <= bullets.getY() &&
        posX + size + bullets.getR() >= bullets.getX() &&
        posY + size + bullets.getR() >= bullets.getY())
    {
        //std::cout << "a Bullet! ouch!" << std::endl;
        return true;
    }
    return false;
} 

