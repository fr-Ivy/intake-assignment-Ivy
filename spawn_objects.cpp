#include "spawn_objects.h"
#include <iostream>

//spawn_objects::spawn_objects() {}

void spawn_objects::spawnObjects(Tmpl8::Game& objects, int& collected, Tmpl8::Surface* surface)
{
    std::cout << "Collected: " << collected << std::endl;

    Tank* tanks = objects.getTanks();
    Bullets* bullets = objects.getBullets();

    if (collected >= 1)
    {
        std::cout << "Activating bullet 0" << std::endl;
        bullets[0].setActive(true);
        std::cout << "Bullet 0 active state: " << bullets[0].getActive() << std::endl;
    }


    // 1 - 4 tanks
    // 0 - 5 bullets
}