#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

class Storage : public Drawable
{
private:
	int stone = 100;
	int iron = 100;

	int s = 160;
	Vector2f size = Vector2f(s, s/2);
	RectangleShape box;

	Font f;
	Text text;

public:
	RectangleShape consol;
	Texture bad;
	Sprite bAdd;

public:
	Storage()
	{
		box.setSize(size);
		box.setFillColor(Color(50, 50, 50, 150));

		if (!f.loadFromFile("data/fons/calibri.ttf"));
		text.setFont(f);
		text.setCharacterSize(30);

		setTxt();

		consol.setSize(Vector2f(200, 800));
		consol.setPosition(1400, 0);
		consol.setFillColor(Color::Red);

		bad.loadFromFile("data/img/icons/ADD.png");
		bAdd.setTexture(bad);
		bAdd.setPosition(1400, 0);
		bAdd.setColor(Color::White);
	};

	void setPos(Vector2f pos)
	{
		consol.setPosition(pos.x + 600, pos.y - 450);
		bAdd.setPosition(consol.getPosition());

		box.setPosition(pos.x - 800, pos.y - 450);
		text.setPosition(box.getPosition());
	};

	void addMatirials(int& amount)
	{
		//тут раскидываем матириалы
		stone += (amount / 100) % 100;
		iron += amount % 100;

		int i = amount % 10000;
		amount -= i;
		i = 0;
		setTxt();
	}

	bool delMatirials(int& amount)
	{
		//тут раскидываем матириалы

		if (stone >= (amount / 100) % 100 && iron >= amount % 100)
		{
			return true;
		}
		else
		{
			//std::cout << "no" << "\n";
			return false;
		}
	}

	void dm(int& am)
	{
		stone -= (am / 100) % 100;
		iron -=  (am % 100);
		setTxt();
	}

	void setTxt()
	{
		text.setString(" Stone = " + std::to_string(stone)
			+ "\n Iron = " + std::to_string(iron));
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(box, states);
		target.draw(text, states);
		target.draw(consol);
		target.draw(bAdd);
	}
};
#endif