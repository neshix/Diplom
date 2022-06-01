#include "Structure.h"

Structure::Structure(std::string selStruct): Entity()
{
	name = selStruct;
	build = true;

	Vector2f size;
	if (name == "factory")
	{
		_texture.loadFromFile("data/img/factory.png");
		_sprite.setTexture(_texture);

		factory = true;
		health = 100;
	}
	else if (name == "storage")
	{
		_texture.loadFromFile("data/img/storage.png");

		size = Vector2f(300, 300);
		reviewBox.setSize(size);
		reviewBox.setFillColor(Color(255,0,0,30));

		storage = true;
		health = 100;
	}
	else if (name == "energy tower")
	{
		if(_texture.loadFromFile("data/img/energy.png")) std::cout << "ok";

		size = Vector2f(500, 500);
		reviewBox.setSize(size);
		reviewBox.setFillColor(Color(0, 255, 0, 30));

		energy = true;
		health = 100;
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(getRect().width / 2, getRect().height / 2);

	reviewBox.setOrigin(size.x / 2, size.y / 2);
}

void Structure::update(Vector2f mousePos, bool& kp, std::list<Bots*>& bot, std::list<Enemy*>& enemy, std::list<MineObj*>& mine, Storage& store)
{
	if (factory)
	{

	}

	if (storage)
	{
		for (auto& m : mine)
		{
			if (m->name == "Materials")
			{
				normal = m->_sprite.getPosition() - _sprite.getPosition();
				distanse = sqrt(normal.x * normal.x + normal.y * normal.y);
				if (distanse <= 300)
				{
					//std::cout << m->amount;
					store.addMatirials(m->amount);
				}
			}
		}
	}

	if (energy)
	{
		t = cl.getElapsedTime();
		for (auto& b : bot)
		{
			if (b->getRect().intersects(reviewBox.getGlobalBounds()) && t.asSeconds() >= 1)
			{
				if (b->energy <= 100)
				{
					b->energy += 5;
				}
			}
		}

		for (auto& e : enemy)
		{
			if (e->getRect().intersects(reviewBox.getGlobalBounds()) && t.asSeconds() >= 1)
			{
				e->health -= 5;
			}
		}

		if (t.asSeconds() >= 1)
		{
			t = cl.restart();
		}
	}
}
