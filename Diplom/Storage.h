#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

class Storage : public Drawable
{
private:
	int tree = 0;
	int stone = 0;
	int iron = 0;

	int s = 150;
	Vector2f size = Vector2f(s, s);
	RectangleShape box;

	Font f;
	Text text;

public:
	Storage()
	{
		box.setSize(size);
		box.setFillColor(Color(50, 50, 50, 150));

		if (!f.loadFromFile("fons/calibri.ttf"));
		text.setFont(f);
		text.setCharacterSize(30);

		setTxt();
	};

	void setPos()
	{

	};

	void addMatirials(int& amount)
	{
		//тут раскидываем матириалы
		tree += (amount / 100) % 100;
		stone += (amount / 10000) % 100;
		iron += amount % 100;

		int i = amount % 1000000;
		amount -= i;
		i = 0;
		setTxt();
	}

	bool delMatirials(int& amount)
	{
		//тут раскидываем матириалы

		if (tree >= (amount / 100) % 100 && stone >= (amount / 10000) % 100 && iron >= amount % 100)
		{
			std::cout << "yes" << "\n";
			return true;
		}
		else
		{
			std::cout << "no" << "\n";
			return false;
		}
	}

	void dm(int& am)
	{
		std::cout << am % 100 << "\n";
		tree -= (am / 100) % 100;
		stone -= (am / 10000) % 100;
		iron = iron - (am % 100);
		setTxt();
	}

	void setTxt()
	{
		std::cout << tree << stone << iron << "\n";
		text.setString("Tree = " + std::to_string(tree)
			+ "\n Stone = " + std::to_string(stone)
			+ "\n Iron = " + std::to_string(iron));
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(box, states);
		target.draw(text, states);
	}
};
#endif