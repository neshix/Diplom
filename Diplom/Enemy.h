#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy() :Entity()
	{
		_shape.setFillColor(Color::Red);
		setPosition(800, 800);
	};
};
#endif ENEMY_H