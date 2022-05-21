#include "Structure.h"

Structure::Structure(std::string selStruct): Entity()
{
	name = selStruct;
	speed = 0;
	build = true;

	if (name == "factory")
	{
		factory = true;
		health = 100;
	}
	else if (name == "storage")
	{
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
				normal = m->getobj().getPosition() - _sprite.getPosition();
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
