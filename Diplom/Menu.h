#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu
{
private:
	Font f;
	Text autor;
	RectangleShape rectautor;
	bool openeutor = false;

	Texture tplay, tautor, texit;
	Sprite splay, sautor, sexit;

	Text tgener, tstone, tiron, tsize, tboss;
	RectangleShape generbox;

	RectangleShape stoneShape, ironShape, sizeShape, bossShape;
	RectangleShape cstoneShape, cironShape, csizeShape, cbossShape;
	float distanse = 0;
	float step = 0;

	bool menuOpen = false;

	bool IsKeyPressed = false;
public:
	Menu();

	void update(RenderWindow& w, int& sizeworld, int& aStone, int& aIron, int& aBoss);
};

