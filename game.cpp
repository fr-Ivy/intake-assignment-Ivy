#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "Tank.h"
#include "Item.h"
#include "Gun.h"
#include "Bullets.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //controls
#include "startscreen.h"
#include <vector>


namespace Tmpl8
{
	static char map[16][76] =
	{
		"aaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXdaX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb baXneXbaXbaXbaXbbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb cbXfb aaXcdXcdXcdXcdXcdXdaXfb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb cbXfb cbXfb fb fb fb fb cbXfb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb ieXcdXdcXfb fb fb fb fb cbXfb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbXfb ff cbX",
		"acXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXddX"
	};

	Surface tiles("assets/nc2tiles.png");
	Sprite tank(new Surface ("assets/ctankbase.tga"), 16);
	Sprite badTank(new Surface("assets/ctankbase.tga"), 16);
	Sprite gun(new Surface("assets/minigun.tga"), 32);
	Sprite bullet(new Surface("assets/phaser.tga"), 16);


	float TankX = 23.0f * 32.0f, TankY = 14.0f * 32.0f;
	float Enemy1X = 20.0f * 32.0f, Enemy1Y = 10.0f * 32.0f;
	int framePlayer = 8;
	int frameEnemy = 8;
	float PlayerBehaviour = 1.0f;
	float enemy1Behaviour = 2.0f;
	Tank tanks[2];
	Item item[1];
	int itemX = 45;
	int itemY = 45;
	float cooldown1 = 1000.0f;
	float cooldown2 = 1000.0f;
	float cooldown3 = 500.0f;
	float time = 0;

	//Gun guns[1];
//	Gun bullets[10];
	int gunX1 = 400;
	int gunY1 = 200;
	int bulletFrame = 1;
	float Seconds = 0.0f;
	int amount = 0;
	Bullets bullets[5];
	startscreen start_screen;

	void Game::Init()
	{
		std::vector<buttons> button
			{
				{50, 375, 1},
				{300, 375, 2},
				{550, 375, 3}
			};

		start_screen = startscreen(screen, button);
		tanks[0] = Tank(TankX, TankY, framePlayer, &tank, PlayerBehaviour);
		tanks[1] = Tank(Enemy1X, Enemy1Y, frameEnemy, &badTank, enemy1Behaviour);

		for (Tank& tank : tanks)
		{
			tanks[0].setPosition(TankX, TankY);
			tanks[1].setPosition(Enemy1X, Enemy1Y);
			tanks[0].setFrame(framePlayer);
			tanks[1].setFrame(frameEnemy);
		}

		item[0] = Item(itemX, itemY);

		for (Item& item : item)
		{
			item.setPosition(itemX, itemY);
		}

		//guns[0] = Gun(gunX1, gunY1, 1, &gun, 1);

		//bullets directions:
		//up = 1
		//down = 2
		//right = 3
		//left = 4
		//combination up and right = 5
		//combination up and left = 6
		//combination down and right = 7
		//combination down and left = 8

		bullets[0] = Bullets(214, 450, 5, 1.0f, 450, 214);
		bullets[1] = Bullets(214, 225, 5, 1.0f, 450, 214);

	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}



	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
		Pixel* dst = screen->GetBuffer() + x + y * 800;

		for (int i = 0; i < 32; i++, src += 595, dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}
	
	bool Game::CheckPos(float x, float y)
	{
		float tx = x / (32.0f), ty = y / (32.0f);
		return map[(int)ty][(int)tx * 3 + 2] != 'X';
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		if (show_startscreen)
		{
			start_screen.drawButton();
		}
		if (show_Game)
		{
			//other stuff
			cooldown1 -= deltaTime;
			cooldown2 -= deltaTime;
			cooldown3 -= deltaTime;

			for (Tank& tank : tanks)
			{
				tank.move(deltaTime);
			}

			for (Bullets& bullet : bullets)
			{
				bullet.move();
			}


			//collisions
			if (tanks[0].collision(tanks[1]))
			{
				if (cooldown1 <= 0.0f)
				{
					lives--;
					cooldown1 = 1000.0f;
				}
			}

			if (tanks[0].itemCollision(item[0]))
			{
				for (Item& item : item)
				{
					item.move();
					if (cooldown2 <= 0.0f)
					{
						collected++;
						cooldown2 = 1000.0f;
					}
				}
			}

			for (Bullets& bullet : bullets)
			{
				if (tanks[0].bulletCollision(bullet))
				{
					if (cooldown3 <= 0.0f)
					{
						lives--;
						cooldown3 = 250.0f;
					}
				}
			}

			//draw map
			screen->Clear(0);
			for (int y = 0; y < 16; y++)
				for (int x = 0; x < 25; x++)
				{
					int tx = map[y][x * 3] - 'a', ty = map[y][x * 3 + 1] - 'a';
					DrawTile(tx, ty, screen, x * 32, y * 32);
				}

			//numbers printed
			char msg1[256];
			snprintf(msg1, 256, "Lives: %i", lives);
			screen->Print(msg1, 35, 12, 0xffffff);

			char msg2[256];
			snprintf(msg2, 256, "Items collected: %i", collected);
			screen->Print(msg2, 35, 22, 0xffffff);

			//draw stuff on screen
			for (Tank& tank : tanks)
			{
				tank.Draw(screen);
			}

			tanks[0].Box(screen, 0xff00ff);
			tanks[1].Box(screen, 0xff0000);

			for (Item& item : item)
			{
				item.draw(screen);
			}

			int amount = 0;
			Seconds += deltaTime;
			for (Bullets& bullet : bullets)
			{
				bullet.draw(screen);
			}

			gun.Draw(screen, 200, 460);
		}
	}

};