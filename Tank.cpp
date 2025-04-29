#include "Tank.h"
#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream> // cout
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //controls

using namespace Tmpl8;

Tank::Tank(float posX, float posY, int frame, Tmpl8::Sprite* sprite, float behaviour)
{
    this->posX = posX;
    this->posY = posY;
    this->frame = frame;
    this->sprite = sprite;
    this->behaviour = behaviour;
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


void Tank::Draw(Tmpl8::Surface& surface)
{
    if (sprite)
    {
            sprite->SetFrame(frame);
            sprite->Draw(&surface, posX - 10, posY - 7);
    }
}


void Tank::move(float deltaTime)
{
    if (behaviour == 1.0f)
    {
        float nx = posX;
        float ny = posY;



        if (GetAsyncKeyState(VK_LEFT)) {
            nx = posX - 1.0f;
            frame = 12;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            nx = posX + 1.0f;
            frame = 4;
        }
        if (GetAsyncKeyState(VK_UP)) {
            ny = posY - 1.0f;
            frame = 8;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            ny = posY + 1.0f;
            frame = 0;
        }


        if (Game::CheckPos(nx, ny) &&
            Game::CheckPos(nx + 30.0f, ny + 30.0f) &&
            Game::CheckPos(nx + 30.0f, ny) &&
            Game::CheckPos(nx, ny + 30.0f))
        {
            posX = nx;
            posY = ny;
        }
    }

   /* if (behaviour == 2.0f)
    {
        static float seconds = 0.0f;
        seconds += deltaTime;

        if (seconds >= 10.0f)
        {
            if (posY)
            {
                posY--;
            }
            if (posY == 6.0f * 32.0f)
            {
                posY = 10.0f * 32.0f;
            }

            seconds = 0.0f;
            frame = 8.0f;
        }
    }*/

    if (behaviour == 2.0f)
    {
        seconds += deltaTime;

        if (seconds >= 10.0f)
        {
            if (posY)
            {
                posY--;
            }
            if (!Game::CheckPos(posX, posY) ||
                !Game::CheckPos(posX + 30.0f, posY + 30.0f) ||
                !Game::CheckPos(posX + 30.0f, posY) ||
                !Game::CheckPos(posX, posY + 30.0f))
            {
                posY = beginY;
            }

            seconds = 0.0f;
            frame = 8.0f;
        }
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
                    std::cout << "Hit by a tank!" << std::endl;
                    return true;
                }
                return false;
}

bool Tank::itemCollision(const Item& item) const
{

    if (posX <= item.getX() + 15 && posY <= item.getY() + 15 && posX + 32 >= item.getX() && posY + 32 >= item.getY())
    {
        std::cout << "Item, YAYYYY!" << std::endl;
        return true;
    }
    return false;
}

bool Tank::bulletCollision(const Bullets& bullets) const
{

    if (posX - bullets.get_r() <= bullets.getX() &&
        posY - bullets.get_r() <= bullets.getY() &&
        posX + 32 + bullets.get_r() >= bullets.getX() &&
        posY + 32 + bullets.get_r() >= bullets.getY())
    {
        std::cout << "a Bullet! ouch!" << std::endl;
        return true;
    }
    return false;
} 

