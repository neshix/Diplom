#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;

class Entity : public Drawable
{
protected:
	friend class Bullet;
	friend class Bots;
	friend class Enemy;
	friend class Structure;

	friend class Command;

public:
	Texture _texture;
	Sprite _sprite;

	Vector2f normal;

public:
	int health = 100;
	float distanse = 0;

	bool life = false;
private:
	float time = 0;

	//bool life = false;

public:
	Entity(std::string pathToTexture);

	Entity();

	template<typename ... Args>
	void setPosition(Args&& ... args)
	{
		_sprite.setPosition(std::forward<Args>(args)...);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif ENTITY_H