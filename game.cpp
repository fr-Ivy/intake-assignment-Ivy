#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "Item.h"
#include "Gun.h"
#include "Bullets.h"
#include "spawn_objects.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //controls
#include "UI.h"
#include <vector>
#include <iostream>


namespace Tmpl8
{
	static char map[16][76] =
	{
		"aaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXcaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXda8",
		"cbXfb fb fb fb fb fb fb fb fb fb cbXfb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb cbXfb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb cbXfb fb fb fb fb fb adXfb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb cbXfb fb fb fb fb fb cbXfb fb fb fb fb cbX",
		"abXcdXcdXcdXcdXcdXbcXfb fb bdXcdXddXfb fb fb fb fb fb ac8baXbaXbcXfb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb adXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb cbXfb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbX",
		"cbXfb fb fb cbXfb fb fb fb bdXcdXcdXcdXdaXfb aaXcdXcdXcdXcdXcdXdaXfb fb cbX",
		"cbXfb fb fb cbXfb fb fb fb fb fb fb fb cbXfb1cbXfb fb fb fb fb cbXfb fb cbX",
		"cbXfb fb fb dbXfb fb fb fb fb fb fb fb ieXcdXdcXfb fb fb fb fb cbXfb fb cbX",
		"cbXfb fb fb fb fb fb1fb fb fb fb fb fb fb fb fb fb fb fb fb fb cbXfb ff cbX",
		"acXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXddX"
	};

	Surface tiles("assets/nc2tiles.png");
	Sprite tank(new Surface ("assets/ctankbase.tga"), 16);
	Sprite badTank1(new Surface("assets/enemyTank.png"), 16);
	Sprite badTank2(new Surface("assets/enemyTank.png"), 16);
	Sprite badTank3(new Surface("assets/enemyTank.png"), 16);
	Sprite gun1(new Surface("assets/minigun.tga"), 32);
	Sprite gun2(new Surface("assets/minigun.tga"), 32);
	Sprite gun3(new Surface("assets/minigun.tga"), 32);
	Sprite bullet(new Surface("assets/phaser.tga"), 16);
	Sprite mouse(new Surface("assets/target.tga"), 1);
	Sprite coin(new Surface("assets/coin4.png"), 1);


	float TankX = 23.0f * 32.0f, TankY = 14.0f * 32.0f;
	float Enemy1X = 20.0f * 32.0f, Enemy1Y = 10.0f * 32.0f;
	float Enemy2X = 12.0f * 32.0f, Enemy2Y = 1.0f * 32.0f;
	float Enemy3X = 11.0f * 32.0f, Enemy3Y = 10.0f * 32.0f;
	float Enemy4X = 1.0f * 32.0f, Enemy4Y = 4.0f * 32.0f;
	Item item[1];
	float itemX = 45.0f;
	float itemY = 45.0f;
	float cooldown1 = 1000.0f;
	float cooldown2 = 1000.0f;
	float cooldown3 = 500.0f;
	float Seconds = 0.0f;

	UI ui;
	spawn_objects spawn;

	void Game::Init()
	{
		std::vector<buttons> button
			{
				{50, 375, 200, 60},
				{300, 375, 200, 60},
				{550, 375, 200, 60},
				{680, 20, 100, 60},
				{150, 300, 200, 60},
				{450, 300, 200, 60},
				{150, 300, 200, 60},
				{450, 300, 200, 60}
			};

		ui = UI(screen, button);

		tanks[0] = Tank(TankX, TankY, 8, &tank, 0);
		tanks[1] = Tank(Enemy1X, Enemy1Y, 8, &badTank1, 1);
		tanks[2] = Tank(Enemy2X, Enemy2Y, 0, &badTank2, 3);
		tanks[3] = Tank(Enemy3X, Enemy3Y, 0, &badTank2, 1);
		tanks[4] = Tank(Enemy4X, Enemy4Y, 12, &badTank3, 2);



		item[0] = Item(itemX, itemY, &coin);

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

		
		bullets[0] = Bullets(6 * 32 + 14, 14 * 32 + 7, 5, 240.0f, 6 * 32 + 14, 14 * 32 + 7, 1);
		bullets[1] = Bullets(6 * 32 + 14, 13 * 32 + 7, 5, 240.0f, 6 * 32 + 14, 14 * 32 + 7, 1);
		bullets[2] = Bullets(14 * 32 + 14, 12 * 32 + 7, 5, 200.0f, 14 * 32 + 14, 12 * 32 + 7, 1);
		bullets[3] = Bullets(14 * 32 + 14, 6 * 32 + 7, 5, 200.0f, 14 * 32 + 14, 12 * 32 + 7, 1);

		bullets[4] = Bullets(23 * 32 + 25, 2 * 32 - 25, 5, 80.0f, 23 * 32 + 25, 2 * 32 - 25, 8);
		bullets[5] = Bullets(17 * 32 + 25, 7 * 32 - 25, 5, 80.0f, 17 * 32 + 25, 7 * 32 - 25, 8);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}


	//map stuff
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
		return map[static_cast<int>(ty)][static_cast<int>(tx) * 3 + 2] != 'X';
	}

	bool Game::CheckGun(float x, float y)
	{
		float tx = (x) / (32.0f), ty = (y) / (32.0f);
		return map[static_cast<int>(ty)][static_cast<int>(tx) * 3 + 2] != '1' &&
			map[static_cast<int>(ty)][static_cast<int>(tx) * 3 + 2] != '8';
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		ui.buttonCase(show_startscreen, show_game, show_controls, show_gameover, show_win, 
			lives, collected, resetTankPos, clicked, enabled);

		if (show_startscreen)
		{
			screen->Clear(0);
			ui.drawButton(0, 3);
			ui.detectMouse(mouseX, mouseY);
			ui.detectButton(0, 3);
			enabled = true;
			ui.mouseClick(clicked);

			screen->PrintScaled("PLAY", 375, 400, 2, 2, 0XFFFFFF);
			screen->PrintScaled("CONTROLS", 100, 400, 2, 2, 0xffffff);
			screen->PrintScaled("EXIT", 625, 400, 2, 2, 0xffffff);
			screen->PrintScaled("welcome", 20, 20, 2, 2, 0xffffff);
			mouse.Draw(screen, mouseX - 12, mouseY - 12);
		}

		if (show_controls)
		{
			screen->Clear(0);
			ui.drawButton(3, 4);
			ui.detectMouse(mouseX, mouseY);
			ui.detectButton(3, 4);
			ui.mouseClick(clicked);

			screen->PrintScaled("BACK", 700, 45, 3, 3, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY UP/W - UP", 50, 120, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY LEFT/A - LEFT", 50, 150, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY DOWN/S - DOWN", 50, 180, 2, 2, 0XFFFFFF);
			screen->PrintScaled("ARROW KEY RIGHT/D - RIGHT", 50, 210, 2, 2, 0XFFFFFF);
			mouse.Draw(screen, mouseX - 12, mouseY - 12);
		} 

		if (show_game)
		{
			enabled = false;
			//other stuff
			cooldown1 -= deltaTime;
			cooldown2 -= deltaTime;
			cooldown3 -= deltaTime;

			for (Tank& tank : tanks)
			{
				tank.move(deltaTime, resetTankPos);
			}

			for (Bullets& bullet : bullets)
			{
				bullet.move(deltaTime);
			}
			

			//collisions
			for (int i = 1; i <= 5; i++)
			{
				if (tanks[0].collision(tanks[i]) && tanks[i].getActive())
				{
					if (cooldown1 <= 0.0f)
					{
						lives--;
						cooldown1 = 1000.0f;
					}
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

			for (int i = 0; i < 6; i++)
			{
				if (tanks[0].bulletCollision(bullets[i]) && bullets[i].getActive())
				{
					if (cooldown3 <= 0.0f)
					{
						lives--;
						cooldown3 = 500.0f;
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

			for (float y = 0; y < 16; y++)
				for (float x = 0; x < 25; x++)
				{
					if (map[static_cast<int>(y)][static_cast<int>(x) * 3 + 2] == '1')
					{
						gun1.Draw(screen, x * 32 + 2, y * 32 + 10);
						gun1.SetFrame(0);
#ifdef _DEBUG

						screen->Box(x * 32, y * 32, x * 32 + 32, y * 32 + 32, 0xff0000);
#endif
					}

					if (map[static_cast<int>(y)][static_cast<int>(x) * 3 + 2] == '8')
					{
						gun3.Draw(screen, x * 32, y * 32 + 6);
						gun3.SetFrame(20);
#ifdef _DEBUG
						screen->Box(x * 32, y * 32, x * 32 + 32, y * 32 + 32, 0xff0000);
#endif
					}
				}

			//numbers printed
			char msg1[256];
			snprintf(msg1, 256, "Lives: %i", lives);
			screen->PrintScaled(msg1, 35, 12, 2, 2, 0xffffff);

			char msg2[256];
			snprintf(msg2, 256, "Items collected: %i/9", collected);
			screen->PrintScaled(msg2, 525, 12, 2, 2, 0xffffff);

			//draw stuff on screen

			tanks[0].Draw(*screen);
#ifdef _DEBUG
			tanks[0].Box(*screen, 0xff00ff);
#endif

			for (int i = 1; i < 5; i++)
			{
				if (tanks[i].getActive())
				{
					tanks[i].Draw(*screen);
#ifdef _DEBUG
					tanks[i].Box(*screen, 0xff0000);
#endif
				}
			}

			for (Item& items : item)
			{
				items.draw(*screen);
#ifdef _DEBUG
				items.Box(*screen, 0xffffff);
#endif
			}

			Seconds += deltaTime;
			for (int i = 0; i < 6; i++)
			{
				if (bullets[i].getActive())
				{
					bullets[i].draw(*screen);
				}
			}

			spawn.spawnObjects(*this, collected, *screen);

			if (lives <= 0 && !show_win && !show_startscreen && !show_controls)
			{
				show_gameover = true;
			}

			if (collected >= 9 && !show_gameover && !show_startscreen && !show_controls)
			{
				show_win = true;
			}
		}

		if (show_win)
		{
			screen->Clear(0);
			ui.drawButton(6, 8);
			ui.detectMouse(mouseX, mouseY);
			ui.detectButton(6, 8);
			ui.mouseClick(clicked);
			enabled = true;
			mouse.Draw(screen, mouseX - 12, mouseY - 12);

			screen->PrintScaled("RETRY", 225, 325, 2, 2, 0XFFFFFF);
			screen->PrintScaled("MENU", 525, 325, 2, 2, 0XFFFFFF);
			screen->PrintScaled("YOU WON", 275, 200, 5, 5, 0XFFFFFF);
		}

		if (show_gameover)
		{
			screen->Clear(0);
			ui.drawButton(4, 6);
			ui.detectMouse(mouseX, mouseY);
			ui.detectButton(4, 6);
			ui.mouseClick(clicked);
			enabled = true;
			mouse.Draw(screen, mouseX - 12, mouseY - 12);

			screen->PrintScaled("RETRY", 225, 325, 2, 2, 0XFFFFFF);
			screen->PrintScaled("MENU", 525, 325, 2, 2, 0XFFFFFF);
			screen->PrintScaled("GAME OVER", 275, 200, 5, 5, 0XFFFFFF);
		}
	}

};