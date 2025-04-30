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
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb adXfb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb adXfb fb fb fb fb fb cbXfb fb fb fb fb cbX",
		"abXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXddXfb fb fb fb fb fb acXbaXneXbcXfb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb bdXcdXcdXcdXdaXfb aaXcdXcdXcdXcdXcdXdaXfb fb cbX",
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
	Tank tanks[6];
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
	Bullets bullets[10];
	startscreen start_screen;

	void Game::Init()
	{
		std::vector<buttons> button
			{
				{50, 375, 200, 60},
				{300, 375, 200, 60},
				{550, 375, 200, 60},
				{680, 20, 100, 60}
			};

		start_screen = startscreen(screen, button);

		tanks[0] = Tank(TankX, TankY, framePlayer, &tank, 1);
		tanks[1] = Tank(Enemy1X, Enemy1Y, frameEnemy, &badTank, 2);

		for (Tank& tank : tanks)
		{
			tanks[0].setPosition(TankX, TankY);
			tanks[1].setPosition(Enemy1X, Enemy1Y);
			tanks[0].setFrame(framePlayer);
			tanks[1].setFrame(frameEnemy);
		}

		item[0] = Item(itemX, itemY);

		for (Item& items : item)
		{
			items.setPosition(itemX, itemY);
		}

		//bullets directions:
		//up = 1
		//down = 2
		//right = 3
		//left = 4
		//combination up and right = 5
		//combination up and left = 6
		//combination down and right = 7
		//combination down and left = 8

		
		bullets[0] = Bullets(214, 450, 5, 240.0f, 214, 450, 1);
		bullets[1] = Bullets(214, 225, 5, 240.0f, 214, 450, 1);

		bullets[2] = Bullets(14 * 32 + 2 + 14, 12 * 32, 5, 240.0f, 14 * 32 + 2 + 14, 12 * 32, 1);
		bullets[3] = Bullets(14 * 32 + 2 + 14, 6 * 32, 5, 240.0f, 14 * 32 + 2 + 14, 12 * 32, 1);


	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}



	void DrawTile(int const tx, int const ty, Surface* screen, int const x, int const y)
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
			screen->Clear(0);
			start_screen.drawButton_startscreen();
			start_screen.detectMouse(mouseX, mouseY);
			start_screen.detectButton(0, 3);
			start_screen.buttonCase(show_startscreen, show_game, show_controls);
			start_screen.mouseClick(clicked);

			screen->PrintScaled("PLAY", 375, 400, 2, 2, 0XFFFFFF);
			screen->PrintScaled("CONTROLS", 100, 400, 2, 2, 0xffffff);
			screen->PrintScaled("EXIT", 625, 400, 2, 2, 0xffffff);
		}

		if (show_controls)
		{
			screen->Clear(0);
			start_screen.drawButton_controls();
			start_screen.detectMouse(mouseX, mouseY);
			start_screen.detectButton(3, 4);
			start_screen.buttonCase(show_startscreen, show_game, show_controls);
			start_screen.mouseClick(clicked);

			screen->PrintScaled("BACK", 700, 45, 3, 3, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY UP - UP", 50, 120, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY LEFT - LEFT", 50, 150, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY DOWN - DOWN", 50, 180, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY RIGHT - RIGHT", 50, 210, 2, 2, 0XFFFFFF);
		}

		if (show_game)
		{
			screen->Clear(0);
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
				bullet.move(deltaTime);
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
				for (Item& items : item)
				{
					items.move();
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
				tank.Draw(*screen);
			}

			tanks[0].Box(*screen, 0xff00ff);
			tanks[1].Box(*screen, 0xff0000);

			for (Item& items : item)
			{
				items.draw(screen);
			}

			int amount = 0;
			Seconds += deltaTime;
			for (Bullets& bullet : bullets)
			{
				bullet.draw(screen);
			}

			gun.Draw(screen, 200, 460);
			gun.Draw(screen, 14 * 32 + 2, 12 * 32 + 9);
		}
	}

};