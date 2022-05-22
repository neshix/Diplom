#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Entity.h"

class Enemy : public livingEntity
{
public:
	Enemy() :livingEntity("data/img/enemy.png")
	{
		setPosition(800, 800);
	};
};
#endif ENEMY_H