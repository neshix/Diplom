#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Entity.h"
#include "Bots.h"
#include "Enemy.h"
#include "Console.h"
#include "MineObj.h"
#include "Structure.h"
#include "Storage.h"
#include "Bullet.h"

using namespace sf;

class Game
{
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(int X = 1600, int Y = 900);
	void run(int minimum_frame_per_seconds = 30);

private:
	void processEvents();//< Process events
	void update(Time deltaTime); //< do some updates
	void render();//< draw all the stuff

	void deads();

	RenderWindow _window;

	Time   _nextSaucer;
	Text   _txt;

	Font font;

	std::list<Bots*> bots;
	std::list<Enemy*> enemys;
	std::list<MineObj*> mineobj;
	std::list<Structure*> structure;
	std::list<Bullet*> bullets;

	bool IsKeyPressed = false;

	Console console;
	Storage storage;

	Vector2i pixelPos;
	Vector2f mousePos;
};
#endif GAME_H
