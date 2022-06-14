#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Entity.h"
#include "Bots.h"
#include "Enemy.h"
#include "MineObj.h"
#include "Structure.h"
#include "Storage.h"
#include "Bullet.h"
#include "Camera.h"
#include "Leviathan.h"
#include "Menu.h"

using namespace sf;

class Game
{
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(int X = 1600, int Y = 900);
	void run(int minimum_frame_per_seconds = 30);

private:
	void generator();

	int wSize = 5000;
	int amountStone = 10;
	int amountIron = 10;
	int amountBoss = 1;

private:
	void processEvents();//< Process events
	void update(Time deltaTime); //< do some updates
	void render();//< draw all the stuff

	void deads();

	RenderWindow _window;
	Menu menu;

	Time   _nextSaucer;
	Text   _txt;

	Font font;

	std::list<Bots*> bots;
	std::list<Enemy*> enemys;
	std::list<Leviathan*> leviathans;
	std::list<MineObj*> mineobj;
	std::list<Structure*> structure;
	std::list<Bullet*> bullets;

	bool IsKeyPressed = false;
	bool IsKeyPress = false;

	Storage storage;
	Camera camera;

	Vector2i pixelPos;
	Vector2f mousePos;

	Event event;

	Vector2f normal;
	float dis = 0;

	bool stop = false;
};
#endif GAME_H
