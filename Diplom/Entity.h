#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;

class Entity : public Drawable
{
protected:
	friend class Bots;
	friend class Enemy;
	friend class Structure;

	friend class Command;

public:
	CircleShape _shape;
	Vector2f target;

public:
	float speed = 100;
	int health = 100;

private:
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

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif ENTITY_H
