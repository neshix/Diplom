#ifndef MINEOBJ_H
#define MINEOBJ_H

#include <SFML/Graphics.hpp>
#include <random>

#include "Entity.h"

using namespace sf;

class MineObj: public Entity
{
public:
	enum idName
	{
		Stone, Iron, Materials
	};

	int amount = 0;
	int extractionTime = 0;
	std::string name;

private:
	Vector2f size = Vector2f(50, 50);

public:
	MineObj(int X, int Y, int id): Entity()
	{
		switch (id)
		{
		case idName::Stone:
			name = "Stone";
			_texture.loadFromFile("data/img/stone.png");
			_sprite.setTexture(_texture);

			extractionTime = 15;
			amount = rand() % 100 + 10;
			break;
		case idName::Iron:
			name = "Iron";
			_texture.loadFromFile("data/img/iron.png");
			_sprite.setTexture(_texture);

			extractionTime = 25;
			amount = rand() % 100 + 10;
			break;
		case idName::Materials:
			name = "Materials";
			_texture.loadFromFile("data/img/box.png");
			_sprite.setTexture(_texture);

			break;
		}
		setPosition(X, Y);
	};
};
#endif MINEOBJ_H