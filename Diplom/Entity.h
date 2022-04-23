#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Entity : public Drawable
{
protected:
	friend class Bots;
	friend class Enemy;

public:
	CircleShape _shape;

public:
	float speed = 50;
	int health = 100;

private:
	Vector2f target;

	Vector2f normal;
	Vector2f moveToPoint;

	float distanse = 0;
	float time = 0;

	bool life = false;

public:

	Entity(float radius = 25);

	template<typename ... Args>
	void setPosition(Args&& ... args)
	{
		_shape.setPosition(std::forward<Args>(args)...);
	}
};

#endif ENTITY_H
