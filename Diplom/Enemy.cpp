#include "Enemy.h"

Enemy::Enemy(Vector2f pos) :livingEntity("data/img/enemy.png")
{
	setPosition(pos);

	reviewBox.setFillColor(Color(255, 0, 0, 30));
	reviewBox.setSize(Vector2f(370, 370));
	reviewBox.setOrigin(Vector2f(370 / 2, 370 / 2));

	//определение поведения врага
	int i = rand() % 100;
	std::cout << i << "\n";
	if (i >= 0 && i <= 70)
	{
		follow = false;
		followE = false;
		followL = false; 
		random = rand() % 100;
	}
	else if (i >= 70 && i <= 85)
	{
		follow = true;
		followL = true;
	}
	else
	{
		follow = true;
		followE = true;
	}

};

void Enemy::update(Time deltaTime, std::list<Enemy*>& enemy, std::list<Leviathan*> leviathan, std::list<Bots*> bot, std::list<Structure*>& s)
{
	for (auto& l : leviathan)
	{
		if (l->attack)
		{
			normal = l->_sprite.getPosition() - _sprite.getPosition();
			distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

			if (distanse <= 1500)
			{
				target = l->attBotPos;
				action = true;
			}
		}
	}

	if (follow == false)
	{
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

		//если стоять
		t = cl.getElapsedTime();
		if (wait && t.asSeconds() >= waitingTime)
		{
			wait = false;
			random = rand() % 100;
		}
	}
	else
	{
		//follow
		if (who == 1 && ene == NULL)
		{
			followE = true;
		}
		if (who == 2 && lev == NULL)
		{
			followL = true;
		}

		if (followE)
		{
			int num = rand() % enemy.size();
			for (auto& e : enemy)
			{
				if (num <= 1)
				{
					ene = e;
					who = 1;
					break;
				}
				else
				{
					num--;
				}
			}
			followE = false;
		}
		if (followL)
		{
			int num = rand() % enemy.size();
			for (auto& l : leviathan)
			{
				if (num <= 1)
				{
					lev = l;
					who = 2;
					break;
				}
				else
				{
					num--;
				}
			}
			followL = false;
		}

		switch (who)
		{
		case 1:
			if (!action)
			{
				action = true;
				target.x = ene->_sprite.getPosition().x + (rand() % 200 - 75);
				target.y = ene->_sprite.getPosition().y + (rand() % 200 - 75);
			}
			break;
		case 2:
			if (!action)
			{
				action = true;
				target.x = lev->_sprite.getPosition().x + (rand() % 500 - 250);
				target.y = lev->_sprite.getPosition().y + (rand() % 500 - 250);
			}
			break;
		}
	}

	for (auto& sr : s)
	{
		if (sr->getRect().intersects(reviewBox.getGlobalBounds()))
		{
			normal = sr->_sprite.getPosition() - _sprite.getPosition();
			distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

			if (distanse > 150)
			{
				target = sr->_sprite.getPosition();
				action = true;
			}
			else
			{
				t = cl.getElapsedTime();
				if (t.asMilliseconds() >= 1000)
				{
					t = cl.restart();
					sr->health -= 10;
				}
				action = false;
			}
			break;
		}
	}

	for (auto& b : bot)
	{
		if (b->getRect().intersects(reviewBox.getGlobalBounds()))
		{
			normal = b->_sprite.getPosition() - _sprite.getPosition();
			distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

			std::cout << action << "  ";
			if (distanse >= 25)
			{
				target = b->_sprite.getPosition();
				action = true;
			}
			std::cout << action << "  ";
			if (distanse <= 30)
			{
				t = cl.getElapsedTime();
				if (t.asMilliseconds() >= 1000)
				{
					t = cl.restart();
					b->health -= 10;
				}
				action = false;
			}
			std::cout << action << "\n";
			break;
		}
	}

	//идти
	move(deltaTime);
}

void Enemy::move(Time deltaTime)
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