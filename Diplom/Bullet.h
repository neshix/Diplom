#pragma once

#include "SFML/Graphics.hpp"
#include "livingEntity.h"

class Bullet : public livingEntity
{

public:
	Bullet(Vector2f spos, Vector2f fpos) : livingEntity("data/img/bullet.png")
	{
		speed = 200;
		target = fpos;
		setPosition(spos);
	};

	void update(Time deltaTime)
	{
		time = deltaTime.asSeconds();

		normal = target - _sprite.getPosition();
		float v = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
		moveToPoint = (normal / v) * speed * time;
		distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

		if (distanse >= 5)
		{
			_sprite.move(moveToPoint);
		}
		else
		{
			life = false;
		}
	}
};