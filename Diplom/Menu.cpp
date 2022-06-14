#include "Menu.h"

Menu::Menu()
{
	menuOpen = true;

	f.loadFromFile("data/fons/F77.ttf");

	tplay.loadFromFile("data/img/MENU/play.png");
	tautor.loadFromFile("data/img/MENU/author.png");
	texit.loadFromFile("data/img/MENU/exit.png");

	splay.setTexture(tplay);
	sautor.setTexture(tautor);
	sexit.setTexture(texit);

	autor.setFont(f);
	autor.setCharacterSize(30);

	rectautor.setFillColor(Color(255, 50, 50, 255));

	//çàãðóçêà êíîïîê ãåíåðàöèè
	generbox.setFillColor(Color(255, 50, 50, 255));

	tgener.setFont(f);
	tgener.setCharacterSize(30);

	tstone.setFont(f);
	tstone.setCharacterSize(25);
	stoneShape.setFillColor(Color(0, 50, 50, 255));
	cstoneShape.setFillColor(Color(0, 150, 50, 255));

	tiron.setFont(f);
	tiron.setCharacterSize(25);
	ironShape.setFillColor(Color(0, 50, 50, 255));
	cironShape.setFillColor(Color(0, 150, 50, 255));

	tsize.setFont(f);
	tsize.setCharacterSize(25);
	sizeShape.setFillColor(Color(0, 50, 50, 255));
	csizeShape.setFillColor(Color(0, 150, 50, 255));

	tboss.setFont(f);
	tboss.setCharacterSize(25);
	bossShape.setFillColor(Color(0, 50, 50, 255));
	cbossShape.setFillColor(Color(0, 150, 50, 255));
}

void Menu::update(RenderWindow& w, int& sizeworld, int& aStone, int& aIron, int& aBoss)
{
	std::cout << w.getPosition().x << "  " << w.getPosition().y;
	splay.setPosition(w.getView().getCenter().x - w.getSize().x/2+100, w.getView().getCenter().y - w.getSize().y / 2 + 50);
	sautor.setPosition(splay.getPosition().x, splay.getPosition().y + splay.getGlobalBounds().height);
	sexit.setPosition(sautor.getPosition().x, sautor.getPosition().y + sautor.getGlobalBounds().height);

	generbox.setSize(Vector2f(w.getSize().x / 1.25 ,w.getSize().y));
	generbox.setPosition(w.getView().getCenter().x - w.getSize().x / 4, w.getView().getCenter().y - w.getSize().y / 2);

	tgener.setString(L" ÍÀÑÒÐÎBÈÊÀ ÃÅÍÅÐÀÖÈÈ:");
	tgener.setPosition(generbox.getPosition());

	Vector2f pos = generbox.getPosition();
	Vector2f size = Vector2f(w.getSize().x / 1.50, w.getSize().y / 30);

	tsize.setString(L" ÐÀÇÌÅÐ ÌÈÐÀ: " + std::to_string(sizeworld));
	tsize.setPosition(pos.x, pos.y + 100);
	sizeShape.setSize(size);
	sizeShape.setPosition(tsize.getPosition().x + 50, tsize.getPosition().y + tsize.getGlobalBounds().height + 20);
	csizeShape.setPosition(tsize.getPosition().x + 52, tsize.getPosition().y + tsize.getGlobalBounds().height + 22);

	tstone.setString(L" ÊÎËÈ×ÅÑÒÂÎ ÊÀÌÍß: " + std::to_string(aStone));
	tstone.setPosition(pos.x, pos.y + 300);
	stoneShape.setSize(size);
	stoneShape.setPosition(tstone.getPosition().x + 50, tstone.getPosition().y + tstone.getGlobalBounds().height + 20);
	cstoneShape.setPosition(tstone.getPosition().x + 52, tstone.getPosition().y + tstone.getGlobalBounds().height + 22);

	tiron.setString(L" ÊÎËÈ×ÅÑÒÂÎ ÆÅËÅÇÀ: " + std::to_string(aIron));
	tiron.setPosition(pos.x, pos.y + 500);
	ironShape.setSize(size);
	ironShape.setPosition(tiron.getPosition().x + 50, tiron.getPosition().y + tiron.getGlobalBounds().height + 20);
	cironShape.setPosition(tiron.getPosition().x + 52, tiron.getPosition().y + tiron.getGlobalBounds().height + 22);

	tboss.setString(L" ÊÎËÈ×ÅÑÒÂÎ ËÅÂÈÀÔÀÍÎÂ: " + std::to_string(aBoss));
	tboss.setPosition(pos.x, pos.y + 700);
	bossShape.setSize(size);
	bossShape.setPosition(tboss.getPosition().x + 50, tboss.getPosition().y + tboss.getGlobalBounds().height + 20);
	cbossShape.setPosition(tboss.getPosition().x + 52, tboss.getPosition().y + tboss.getGlobalBounds().height + 22);

	while (w.isOpen() && menuOpen)
	{
		Event event;
		while (w.pollEvent(event))
		{
			if (event.type == Event::Closed)
				w.close();
		}

		if (event.type == Event::MouseButtonReleased)
			IsKeyPressed = false;

		Vector2i pixelPos = Mouse::getPosition(w);
		Vector2f mousePos = w.mapPixelToCoords(pixelPos);

		splay.setColor(Color::White);
		sautor.setColor(Color::White);
		sexit.setColor(Color::White);

		if (splay.getGlobalBounds().contains(mousePos))
		{
			splay.setColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left) && !IsKeyPressed)
			{
				IsKeyPressed = true;
				menuOpen = false;
			}
		}
		if (sautor.getGlobalBounds().contains(mousePos))
		{
			sautor.setColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left) && openeutor == false && !IsKeyPressed)
			{
				IsKeyPressed = true;
				IsKeyPressed = true;
				openeutor = true;
				autor.setString(L" ÌÀËÜÖÅÂ ÄÌÈÒÐÈÈ ÌÀÊÑÈÌÎÂÈ× \n     ñòóäåíò ãð.ÊÑÊ 19-26");
				autor.setPosition(w.getView().getCenter().x - w.getSize().x / 2 + 50, w.getView().getCenter().y + w.getSize().y / 2 - 150);
				rectautor.setPosition(autor.getPosition());
				rectautor.setSize(Vector2f(autor.getGlobalBounds().width, autor.getGlobalBounds().height));
			}

			if (Mouse::isButtonPressed(Mouse::Left) && openeutor == true && !IsKeyPressed)
			{
				IsKeyPressed = true;
				openeutor = false;
				autor.setString("");
				rectautor.setSize(Vector2f(autor.getGlobalBounds().width, autor.getGlobalBounds().height));
			}
		}
		if (sexit.getGlobalBounds().contains(mousePos))
		{
			sexit.setColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left) && !IsKeyPressed)
			{
				IsKeyPressed = true;
				w.close();
			}
		}

		if (stoneShape.getGlobalBounds().contains(mousePos))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				step = 1;
				distanse = mousePos.x - stoneShape.getPosition().x;
				cstoneShape.setSize(Vector2f(distanse, size.y));

				aStone = distanse / step + 10;
				tstone.setString(L" ÊÎËÈ×ÅÑÒÂÎ ÊÀÌÍß: " + std::to_string(aStone));
			}
		}
		if (ironShape.getGlobalBounds().contains(mousePos))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				step = 1;
				distanse = mousePos.x - ironShape.getPosition().x;
				cironShape.setSize(Vector2f(distanse, size.y));

				aIron = distanse / step + 10;
				tiron.setString(L" ÊÎËÈ×ÅÑÒÂÎ ÆÅËÅÇÀ: " + std::to_string(aIron));
			}
		}
		if (sizeShape.getGlobalBounds().contains(mousePos))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				step = 50;
				distanse = mousePos.x - sizeShape.getPosition().x;
				csizeShape.setSize(Vector2f(distanse, size.y));

				sizeworld = step * distanse + 5000;
				tsize.setString(L" ÐÀÇÌÅÐ ÌÈÐÀ: " + std::to_string(sizeworld));
			}
		}
		if (bossShape.getGlobalBounds().contains(mousePos))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				step = 30;
				distanse = mousePos.x - bossShape.getPosition().x;
				cbossShape.setSize(Vector2f(distanse, size.y));

				aBoss = distanse / step+1;
				tboss.setString(L" ÊÎËÈ×ÅÑÒÂÎ ËÅÂÈÀÔÀÍÎÂ: " + std::to_string(aBoss));
			}
		}
		



		//îòðèñîâêà
		w.clear(Color(129, 181, 221, 255));

		w.draw(generbox);
		w.draw(tgener);

		w.draw(tstone);
		w.draw(stoneShape);
		w.draw(cstoneShape);
		
		w.draw(tsize);
		w.draw(sizeShape);
		w.draw(csizeShape);
		
		w.draw(tiron);
		w.draw(ironShape);
		w.draw(cironShape);
		
		w.draw(tboss);
		w.draw(bossShape);
		w.draw(cbossShape);

		w.draw(rectautor);
		w.draw(autor);

		w.draw(splay);
		w.draw(sautor);
		w.draw(sexit);

		w.display();
	}
}
