#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "livingEntity.h"
#include "Entity.h"
#include "Enemy.h"

class Bullet : public livingEntity
{

public:
	Bullet(Vector2f spos, Vector2f fpos) : livingEntity("data/img/bullet.png")
	{
		speed = 300;
		target = fpos;
		setPosition(spos);
	};

	void update(Time deltaTime, std::list<Enemy*>& enemy);
};
#endif BULLET_H