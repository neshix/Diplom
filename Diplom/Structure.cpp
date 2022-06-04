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

		texture.loadFromFile("data/img/icons/plus.png");
		addB.setTexture(texture);
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
		if (!kp)
		{
			addB.setPosition(_sprite.getPosition().x + 10, _sprite.getPosition().y - 10);
			if (addB.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Right) && !AB)
			{
				int i = 2525;
				if (store.delMatirials(i)) 
				{
					store.dm(i);

					kp = true;
					t = cl.restart();
					AB = true;
				}
			}

			t = cl.getElapsedTime();
			if (AB && t.asSeconds() >= 5)
			{
				AB = false;
				int x = rand() % 200 - 100;
				if (x > 0)
					x += _sprite.getPosition().x + 75;
				else
					x += _sprite.getPosition().x - 75;

				int y = rand() % 200 - 100;
				if (y > 0)
					y += _sprite.getPosition().y + 75;
				else
					y += _sprite.getPosition().y - 75;

				sp = Vector2f(x,y);

				//std::cout << "x: " << x << " y: " << y << "\n";
				bot.push_back(new Bots(_sprite.getPosition().x, _sprite.getPosition().y));
				bot.back()->target = sp;
				bot.back()->finish = true;
				bot.back()->point = &move;
			}
		}
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
