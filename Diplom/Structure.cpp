#include "Structure.h"

Structure::Structure(std::string selStruct): Entity()
{
	name = selStruct;
	build = true;

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
		_sprite.setTexture(_texture);

		storage = true;
		health = 100;
	}
}

void Structure::update(Vector2f mousePos, bool& kp, std::list<Bots*>& bot, std::list<MineObj*>& mine, Storage& store)
{
	if (factory)
	{

	}
	else if (storage)
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
}
