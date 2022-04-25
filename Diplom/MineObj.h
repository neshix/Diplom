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
		Tree, Stone, Iron, DMaterial
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
			amount = rand() % 100 + 10;
			break;
		case idName::Stone:
			name = "Stone";
			obj.setFillColor(Color(136, 136, 136, 255));
			extractionTime = 15;
			amount = rand() % 100 + 10;
			break;
		case idName::Iron:
			name = "Iron";
			obj.setFillColor(Color(100, 136, 200, 255));
			extractionTime = 25;
			amount = rand() % 100 + 10;
			break;
		case idName::DMaterial:
			name = "Materials";
			obj.setFillColor(Color(50, 50, 200, 255));
			break;
		}

		obj.setSize(size);
		obj.setPosition(X, Y);
		obj.setOrigin(size / 2.0f);//центр обекта
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