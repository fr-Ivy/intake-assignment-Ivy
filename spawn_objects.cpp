#include "spawn_objects.h"

void spawn_objects::spawnObjects(Tmpl8::Game& objects, const int& collected, Tmpl8::Surface& surface)
{
   // std::cout << "Collected: " << collected << std::endl;

    Tank* tanks = objects.getTanks();
    Bullets* bullets = objects.getBullets();

    //tanks
    tanks[1].setActive(collected >= 0);
    tanks[3].setActive(collected >= 4);
    tanks[4].setActive(collected >= 5);
    tanks[2].setActive(collected >= 7);

    //bullets
    bullets[2].setActive(collected >= 1);
    bullets[4].setActive(collected >= 2);
    bullets[0].setActive(collected >= 3);
    bullets[1].setActive(collected >= 3);
    bullets[3].setActive(collected >= 6);
    bullets[5].setActive(collected >= 8);

    // 1 - 4 tanks
    // 0 - 5 bullets
}