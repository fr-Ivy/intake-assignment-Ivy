#include "Tank.h"
#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream> // cout
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //controls
#include <SDL.h>

using namespace Tmpl8;

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

void Tank::setPosition(float posX, float posY)
{
    this->posX = posX;
    this->posY = posY;
}

void Tank::setFrame(int frame)
{
    this->frame = frame;
}


void Tank::Draw(Tmpl8::Surface& surface) const
{
    if (sprite)
    {
    	sprite->SetFrame(frame);
    	sprite->Draw(&surface, posX - 10, posY - 7);
    }
}

float w = 0;
float a = 0;
float s = 0;
float d = 0;

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
    if (behaviour == 0)
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

        if (Game::CheckPos(nx, ny) &&
            Game::CheckPos(nx + 30.0f, ny + 30.0f) &&
            Game::CheckPos(nx + 30.0f, ny) &&
            Game::CheckPos(nx, ny + 30.0f) && 
            Game::CheckGun(nx, ny) &&
            Game::CheckGun(nx + 30.0f, ny + 30.0f) &&
            Game::CheckGun(nx + 30.0f, ny) &&
            Game::CheckGun(nx, ny + 30.0f))
        {
            posX = nx;
            posY = ny;
        }

        if (resetTankPos)
        {
            posX = beginX;
            posY = beginY;
            resetTankPos = false;
        }
    }

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

    if (!Game::CheckPos(posX, posY) ||
		!Game::CheckPos(posX + 30.0f, posY + 30.0f) ||
		!Game::CheckPos(posX + 30.0f, posY) ||
		!Game::CheckPos(posX, posY + 30.0f) && behaviour > 1)
    {
    	posY = beginY;
    	posX = beginX;
    }
}

void Tank::Box(const Tmpl8::Surface& surface, Tmpl8::Pixel color) const
{
    surface.Box(posX, posY, posX + 32, posY + 32, color);
}


bool Tank::collision(const Tank& other) const
{
	if (posX <= other.posX + 32 && posY <= other.posY + 32 && posX + 32 >= other.posX && posY + 32 >= other.posY)
	{
		//std::cout << "Hit by a tank!" << std::endl;
		return true;
	}
	return false;
}

bool Tank::itemCollision(const Item& item) const
{

    if (posX <= item.getX() + 15 && posY <= item.getY() + 15 && posX + 32 >= item.getX() && posY + 32 >= item.getY())
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
        posX + 32 + bullets.getR() >= bullets.getX() &&
        posY + 32 + bullets.getR() >= bullets.getY())
    {
        //std::cout << "a Bullet! ouch!" << std::endl;
        return true;
    }
    return false;
} 

