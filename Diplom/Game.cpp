#include "Game.h"

Game::Game(int X, int Y) : _window(VideoMode(X,Y), "among sand")
{
	sf::Image icon;
	icon.loadFromFile("data/img/sign.png"); // File/Image/Pixel
	_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	prom.loadFromFile("data/img/icons/prompt1.png");
	prompt.setTexture(prom);
	education = true;

	if (!font.loadFromFile("data/fons/calibri.ttf")) std::cout << "ne naideno";
	_txt.setFont(font);
	_txt.setCharacterSize(24);
}

void Game::run(int minimum_frame_per_seconds)
{
	menu.update(_window, wSize, amountStone, amountIron, amountBoss);

	generator();

   Clock clock;
   Time timeSinceLastUpdate;
   Time TimePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
	
	while (_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}

		update(timeSinceLastUpdate);
		render();
	}
}

void Game::processEvents()
{
	while (_window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_window.close();
	}

	if (event.type == Event::MouseButtonReleased)
		IsKeyPressed = false;

	if (event.type == Event::KeyReleased)
		IsKeyPress = false;

	if (Keyboard::isKeyPressed(Keyboard::Escape) && stop == false && IsKeyPress == false)
	{
		IsKeyPressed = true;
		stop = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && stop == true && IsKeyPress == false)
	{
		IsKeyPressed = true;
		stop = false;
	}
}

void Game::update(Time deltaTime)
{
	if (stop)
	{
		return;
	}

	pixelPos = Mouse::getPosition(_window);
	mousePos = _window.mapPixelToCoords(pixelPos);

	camera.update(deltaTime, wSize);
	storage.setPos(camera.view.getCenter());

	for (auto& l : leviathans)
	{
		l->update(deltaTime, enemys, bots);
	}

	for (auto& e : enemys)
	{
		e->update(deltaTime, enemys, leviathans, bots, structure);
	}

	for (auto& bot : bots)
	{
		//выбор бота
		if (Mouse::isButtonPressed(Mouse::Right) && bot->_sprite.getGlobalBounds().contains(mousePos))
		{
			for (auto& b : bots) { b->selected = false; }
			bot->selected = true;

			pressed = 6;
		}

		//добавление команд
		if (storage.bAdd.getGlobalBounds().contains(mousePos))
		{
			if (bot->selected)
			{
				storage.bAdd.setColor(Color::Green);
			}
			if (!IsKeyPressed)
			{
				if (Mouse::isButtonPressed(Mouse::Left) && bot->selected)
				{
					bot->AddCommand(font);
					IsKeyPressed = true;
					pressed = 7;
				}
			}
		}
		else
		{
			storage.bAdd.setColor(Color::White);
		}

		//управление командами
		if (bot->selected)
		{
			bot->_sprite.setTextureRect(IntRect(0, 0, 50, 50));
			bot->delCommand(mousePos, IsKeyPressed);
			for (auto& com : bot->command)
			{
				com->update(mousePos, IsKeyPressed, bot->command, pressed);
			}
			bot->setPosCommand(storage.consol.getPosition());
		}
		else
		{
			bot->_sprite.setTextureRect(IntRect(50, 0, 50, 50));
		}

		bot->update(mousePos, mineobj, structure, storage, enemys, leviathans, bullets);
		bot->moveTo(deltaTime);
	}

	for (auto& str: structure)
	{
		str->update(mousePos, IsKeyPressed, bots, enemys, mineobj, storage);
	}

	for (auto& bul : bullets)
		bul->update(deltaTime, enemys);

	//удаление трупов
	deads();

	//обучение
	if (education)
	{
		if (pressed == 6)
		{
			prom.loadFromFile("data/img/icons/prompt2.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 20);
		}

		if (pressed == 7)
		{
			prom.loadFromFile("data/img/icons/prompt3.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 60);
		}

		if (pressed == 1)
		{
			prom.loadFromFile("data/img/icons/prompt4.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 60);
		}

		if (pressed == 4)
		{
			prom.loadFromFile("data/img/icons/prompt5.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 60);
		}

		if (pressed == 2)
		{
			prom.loadFromFile("data/img/icons/prompt6.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 60);
		}

		if (pressed == 5)
		{
			prom.loadFromFile("data/img/icons/prompt7.png");
			prompt.setTextureRect(IntRect(0, 0, prom.getSize().x, prom.getSize().y));
			prompt.setPosition(storage.consol.getPosition().x - prompt.getGlobalBounds().width, storage.consol.getPosition().y + 60);
		}

		//if (pressed == 3)
		//{
		//	education = false;
		//}
	}

	//цель
	_txt.setString(L"Левеафанов\nосталось: " + std::to_string(leviathans.size()));
	_txt.setPosition(camera.view.getCenter().x - 800, camera.view.getCenter().y - 300);
}

void Game::render()
{
	//Clear screen
	_window.clear(Color(255, 125, 50, 255));

	//Draw
	// камера
	_window.draw(camera);
	//обекты игры
	for (auto& m : mineobj)
	{
		normal = m->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);

		if (dis < 1000)
		{
			_window.draw(*m);
		}
	}

	for (auto& s : structure)
	{
		normal = s->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);

		if (dis < 1000)
		{
			if (s->getRect().contains(mousePos))
			{
				//std::cout << "a";
				_window.draw(s->reviewBox);
			}
			_window.draw(*s);
			_window.draw(s->addB);
		}
	}

	for (auto& bot : bots)
	{
		normal = bot->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);
		if (dis < 1000)
		{
			if (bot->getRect().contains(mousePos))
			{
				_window.draw(bot->reviewBox);
			}

			for (auto& com : bot->command)
			{
				for (auto& p : com->points)
				{
					_window.draw(p);
				}

				if (com->isMove || com->isDrop)
					_window.draw(com->mpoint);
			}

			_window.draw(*bot);
		}
	}

	for (auto& enemy : enemys)
	{
		normal = enemy->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);
		if (dis < 1000)
		{
			_window.draw(*enemy);
		}
	}

	for (auto& bullet : bullets)
	{
		normal = bullet->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);
		if (dis < 1000)
		{
			_window.draw(*bullet);
		}
	}

	for (auto& l : leviathans)
	{
		normal = l->getPosition() - camera.getCenter();
		dis = sqrt(normal.x * normal.x + normal.y * normal.y);
		if (dis < 1000)
		{
			_window.draw(*l);
		}
	}

	//интерфейс
	_window.draw(storage);

	for (auto& bot : bots)
		if (bot->selected)
		{
			_window.draw(bot->info);
			_window.draw(bot->infoTxt);
			for (auto& com : bot->command)
			{
				_window.draw(*com);
			}
		}

	if (education)
	{
		_window.draw(prompt);
	}

	_window.draw(_txt);
	//Update the window
	_window.display();
}

void Game::deads()
{
	for (auto c = mineobj.begin(); c != mineobj.end();)
	{
		MineObj* mine = *c;
		if (mine->amount <= 0)
		{
			mine->life = false;
		}

		if (mine->life == false)
		{
			delete* c;
			c = mineobj.erase(c);
		}
		else
		{
			c++;
		}
	}

	for (auto c = bots.begin(); c != bots.end();)
	{
		Bots* bot = *c;
		if (bot->health <= 0)
		{
			bot->life = false;
		}

		if (bot->life == false)
		{
			delete* c;
			c = bots.erase(c);
		}
		else
		{
			c++;
		}
	}

	for (auto c = enemys.begin(); c != enemys.end();)
	{
		Enemy* enemy = *c;
		if (enemy->health <= 0)
		{
			enemy->life = false;
		}

		if (enemy->life == false)
		{
			delete* c;
			c = enemys.erase(c);
		}
		else
		{
			c++;
		}
	}

	for (auto c = structure.begin(); c != structure.end();)
	{
		Structure* s = *c;
		if (s->health <= 0)
		{
			s->life = false;
		}

		if (s->life == false)
		{
			delete* c;
			c = structure.erase(c);
		}
		else
		{
			c++;
		}
	}

	for (auto c = bullets.begin(); c != bullets.end();)
	{
		Bullet* bullet = *c;
		if (bullet->health <= 0)
		{
			bullet->life = false;
		}

		if (bullet->life == false)
		{
			delete* c;
			c = bullets.erase(c);
		}
		else
		{
			c++;
		}
	}
}

void Game::generator()
{
	for (int i = 0; i <= amountStone; i++)
	{
		int w = rand() % wSize - wSize / 2;
		int h = rand() % wSize - wSize / 2;
		mineobj.push_back(new MineObj(w, h, 0));
	}

	for (int i = 0; i <= amountIron; i++)
	{
		int w = rand() % wSize - wSize / 2;
		int h = rand() % wSize - wSize / 2;
		mineobj.push_back(new MineObj(w, h, 1));
	}

	for (size_t i = 0; i < amountBoss; i++)
	{
		int gener = rand() % 80;

		int x = 0, y = 0;

		if (gener <= 20)
		{
			x = rand() % wSize - wSize / 2;
			y = wSize / 2 - 500;
		}

		if(gener <= 40 && gener > 20)
		{
			y = rand() % wSize - wSize / 2;
			x = wSize / 2 - 500;
		}

		if (gener <= 60 && gener > 40)
		{
			x = rand() % wSize - wSize / 2;
			y = -wSize / 2 + 500;
		}

		if (gener <= 80 && gener > 60)
		{
			y = rand() % wSize - wSize / 2;
			x = -wSize / 2 + 500;
		}

		std::cout << x << "  " << y << " " << gener <<  "\n";
		leviathans.push_back(new Leviathan(x, y));
	}

	bots.push_back(new Bots);
	bots.push_back(new Bots(300, 300));
	structure.push_back(new Structure("storage", Vector2f(0.0,0.0)));

	prompt.setPosition(bots.back()->getPosition().x - 25, bots.back()->getPosition().y - 75);
}