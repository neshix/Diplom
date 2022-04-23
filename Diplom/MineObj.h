#ifndef MINEOBJ_H
#define MINEOBJ_H

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;

class MineObj: public Drawable
{
public:
	enum idName
	{
		Tree, Stone, Iron
	};

	int amount = 0;
	int extractionTime = 0;
	std::string name;

private:
	RectangleShape obj;
	Vector2f size = Vector2f(50, 50);

public:
	MineObj(int X, int Y, int id)
	{
		switch (id)
		{
		case idName::Tree:
			name = "Tree";
			obj.setFillColor(Color(153, 75, 0, 255));
			extractionTime = 5;
			break;
		case idName::Stone:
			name = "Stone";
			obj.setFillColor(Color(136, 136, 136, 255));
			extractionTime = 15;
			break;
		case idName::Iron:
			name = "Iron";
			obj.setFillColor(Color(100, 136, 200, 255));
			extractionTime = 25;
			break;
		}

		obj.setSize(size);
		obj.setPosition(X, Y);
		obj.setOrigin(size / 2.0f);//центр обекта

		amount = rand() % 100 + 10;
	};

	RectangleShape getobj() 
	{
		return obj;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(obj, states);
	}
};
#endif MINEOBJ_H