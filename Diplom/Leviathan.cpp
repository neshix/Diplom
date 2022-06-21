#include "Leviathan.h"

Leviathan::Leviathan(int x, int y) : livingEntity("data/img/boss.png")
{
	health = 1000;
	setPosition(x,y);

	reviewBox.setFillColor(Color(255, 0, 0, 30));
	reviewBox.setSize(Vector2f(700, 700));
	reviewBox.setOrigin(Vector2f(700 / 2, 700 / 2));

	random = rand() % 100;
	speed = 10;
}

void Leviathan::update(Time deltaTime, std::list<Enemy*>& enemy, std::list<Bots*> bot)
{
	// тут х для дипплома
	if (bot.empty())
	{
		attack = false;
	}

	for (auto& b : bot)
	{
		if (b->getRect().intersects(reviewBox.getGlobalBounds()))
		{
			attBotPos = b->_sprite.getPosition();
			attack = true;
			break;
		}
		else
		{
			attack = false;
		}
	}

	//работа с передвижением
	if (random >= 0 && random <= 50 && !wait)
	{
		//стоять на месте
		wait = true;
		waitingTime = rand() % 60;
		t = cl.restart();

		//std::cout << random << "\n";
	}
	if (random > 50 && random <= 100 && !action)
	{
		//идти куда то
		action = true;
		target.x = _sprite.getPosition().x + (rand() % 2000 - 1000);
		target.y = _sprite.getPosition().y + (rand() % 2000 - 1000);

		//std::cout << random << "\n";
	}

	t = cl.getElapsedTime();
	if (wait && t.asSeconds() >= waitingTime)
	{
		wait = false;
		random = rand() % 100;
	}

	move(deltaTime);
	//////////////////////////////////////////////////////////////
	// спавн ботов

	tSpawn = clSpawn.getElapsedTime();
	if (tSpawn.asSeconds() >= enemy.size())
	{
		tSpawn = clSpawn.restart();
		int x = rand() % 50 - 25;
		if (x > 0)
			x += _sprite.getPosition().x + 150;
		else
			x += _sprite.getPosition().x - 150;

		int y = rand() % 50 - 25;
		if (y > 0)
			y += _sprite.getPosition().y + 150;
		else
			y += _sprite.getPosition().y - 150;

		enemy.push_back(new Enemy(Vector2f(x,y)));
	}
}

void Leviathan::move(Time deltaTime)
{
	if (action)
	{
		time = deltaTime.asSeconds();

		normal = target - _sprite.getPosition();
		float v = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
		moveToPoint = (normal / v) * speed * time;
		distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

		angle = std::atan2(normal.y, normal.x) * 180 / 3.14159265;

		if (distanse >= 5)
		{
			_sprite.move(moveToPoint);
			_sprite.setRotation(angle);

			reviewBox.setPosition(_sprite.getPosition());
		}
		else
		{
			action = false;
			random = rand() % 100;

		}
	}
}