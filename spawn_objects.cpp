#include "spawn_objects.h"

void spawn_objects::spawnObjects(Tmpl8::Game& objects, const int& collected, Tmpl8::Surface& surface)
{
   // std::cout << "Collected: " << collected << std::endl;

    Tank* tanks = objects.getTanks();
    Bullets* bullets = objects.getBullets();

    if (collected >= 0)
    {
        tanks[1].setActive(true);
    }
    else
    {
        tanks[1].setActive(false);
    }


    if (collected >= 1)
    {
        bullets[2].setActive(true);
    }
    else
    {
        bullets[2].setActive(false);
    }


    if (collected >= 2)
    {
        bullets[4].setActive(true);
    }
    else
    {
        bullets[4].setActive(false);
    }


    if (collected >= 3)
    {
        bullets[0].setActive(true);
        bullets[1].setActive(true);
    }
    else
    {
        bullets[0].setActive(false);
        bullets[1].setActive(false);
    }


    if (collected >= 4)
    {
        tanks[3].setActive(true);
    }
    else
    {
        tanks[3].setActive(false);
    }


    if (collected >= 5)
    {
        tanks[4].setActive(true);
    }
    else
    {
        tanks[4].setActive(false);
    }


    if (collected >= 6)
    {
        bullets[3].setActive(true);
    }
    else
    {
        bullets[3].setActive(false);
    }


    if (collected >= 7)
    {
        tanks[2].setActive(true);
    }
    else
    {
        tanks[2].setActive(false);
    }


    if (collected >= 8)
    {
        bullets[5].setActive(true);
    }
    else
    {
        bullets[5].setActive(false);
    }


    // bullets - 5

    // 1 - 4 tanks
    // 0 - 5 bullets
}