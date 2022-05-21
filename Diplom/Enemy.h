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
		_texture.loadFromFile("data/img/enemy.png");
		_sprite.setTexture(_texture);
		setPosition(800, 800);
	};
};
#endif ENEMY_H