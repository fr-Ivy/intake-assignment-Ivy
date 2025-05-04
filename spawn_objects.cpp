#include "spawn_objects.h"
#include <iostream>

//spawn_objects::spawn_objects() {}

void spawn_objects::spawnObjects(Tmpl8::Game& objects, int& collected, Tmpl8::Surface* surface)
{
    std::cout << "Collected: " << collected << std::endl;

    Tank* tanks = objects.getTanks();
    Bullets* bullets = objects.getBullets();

    if (collected >= 0)
    {
        tanks[1].setActive(true);
    }

    if (collected >= 1)
    {
        bullets[2].setActive(true);
    }

    if (collected >= 2)
    {
        bullets[4].setActive(true);
    }

    if (collected >= 3)
    {
        bullets[0].setActive(true);
        bullets[1].setActive(true);
    }

    if (collected >= 4)
    {
        tanks[3].setActive(true);
    }

    if (collected >= 5)
    {
        tanks[4].setActive(true);
    }

    if (collected >= 6)
    {
        bullets[3].setActive(true);
    }

    if (collected >= 7)
    {
        tanks[2].setActive(true);
    }

    if (collected >= 7)
    {
        bullets[5].setActive(true);
    }

    // bullets - 5

    // 1 - 4 tanks
    // 0 - 5 bullets
}