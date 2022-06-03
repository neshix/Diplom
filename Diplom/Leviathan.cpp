#include "Leviathan.h"

Leviathan::Leviathan() : livingEntity("data/img/boss.png")
{
	random = rand() % 100;
	speed = 10;
}

void Leviathan::update(Time deltaTime)
{
	t = cl.getElapsedTime();
	if (wait && t.asSeconds() >= waitingTime)
	{
		wait = false;
		random = rand() % 100;
	}

	if (random >= 0 && random <= 50 && !wait)
	{
		//стоять на месте
		wait = true;
		waitingTime = rand() % 60;
		t = cl.restart();

		std::cout << random << "\n";
	}
	if (random > 50 && random <= 100 && !action)
	{
		//идти куда то
		action = true;
		target.x = _sprite.getPosition().x + (rand() % 2000 - 1000);
		target.y = _sprite.getPosition().y + (rand() % 2000 - 1000);

		std::cout << random << "\n";
	}
	move(deltaTime);
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
		}
		else
		{
			action = false;
			random = rand() % 100;

		}
	}
}

void Leviathan::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}