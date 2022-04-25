#include "Bots.h"

void Bots::AddCommand(Font font)
{
	if (command.size() == 14)
	{
		return;
	}
	command.push_back(new Command(font));
}

void Bots::delCommand(Vector2f mpos, bool& press)
{
	for (auto c = command.begin(); c != command.end();)
	{
		Command *com = *c;
		if (Mouse::isButtonPressed(Mouse::Left) && com->deldox.getGlobalBounds().contains(mpos) && press == false)
		{
			press = true;
			c = command.erase(c);
		}
		else
		{
			c++;
		}
	}
}

void Bots::setPosCommand(Vector2f pos)
{
	Vector2f dbpos;
	int i = 0;
	for (auto& com : command)
	{
		com->box.setPosition(pos.x, pos.y + 100 + (com->box.getSize().y * i));
		dbpos = Vector2f(com->box.getPosition().x + (com->box.getSize().x - com->deldox.getSize().x),
						 com->box.getPosition().y + (com->box.getSize().y - com->deldox.getSize().y));
		com->txt.setPosition(com->box.getPosition());
		com->deldox.setPosition(dbpos);

		com->txtpriority.setPosition(com->box.getPosition().x + (com->box.getSize().x - 20), com->box.getPosition().y);
		
		int k = 0;
		for (auto& t : com->text)
		{
			t->setPosition(Vector2f(com->box.getPosition().x - 60, com->box.getPosition().y + (t->getCharacterSize() * k)));
			k++;
		}
		i++;
	}

	info.setPosition(pos.x - info.getSize().x, pos.y);
	infoTxt.setPosition(info.getPosition() * 1.01f);
}

void Bots::realization(Vector2f mp, std::list<MineObj*>& mine)
{
	maxPriority = 0;
	for (auto& com : command)
	{
		if (com->priority > maxPriority)
		{
			maxPriority = com->priority;
		}

		if (finish && com->moveTarget)
		{
			com->onPoint = false;
		}
	}

	for (auto& com : command)
	{
		if (maxPriority == com->priority)
		{
			point = &com->onPoint;
			if (!*point)
			{
				//std::cout << "move" << "\n";
				finish = true;
				target = com->movePos;
			}

			if (com->isMine)
			{
				if (!com->mineobjinit)
				{
					for (auto& e : mine)
					{
						if (com->isMineIron && e->name == "Iron")
						{
							com->isMineIron = false;
							com->movePos = e->getobj().getPosition();
							com->mineobjinit = true;
							*point = false;
							obj = e;
						}

						if (com->isMineTree && e->name == "Tree")
						{
							com->isMineTree = false;
							com->movePos = e->getobj().getPosition();
							com->mineobjinit = true;
							*point = false;
							obj = e;
						}

						if (com->isMineStone && e->name == "Stone")
						{
							com->isMineStone = false;
							com->movePos = e->getobj().getPosition();
							com->mineobjinit = true;
							*point = false;
							obj = e;
						}
					}
				}

				if (*point && com->mineobjinit)
				{
					//крч бл€ть тут ху€рить начинаем
					capacity = (iventory % 100) + ((iventory / 100) % 100) + ((iventory / 10000) % 100);
					std::cout << obj->amount << "\n";
					t = cl.getElapsedTime();
					if (capacity < 50 && t.asSeconds() >= obj->extractionTime)
					{
						t = cl.restart();
						if (obj->name == "Iron")
						{
							iventory += 1;
							obj->amount--;
						}

						if (obj->name == "Tree")
						{
							iventory += 100;
							obj->amount--;
						}

						if (obj->name == "Stone")
						{
							iventory += 10000;
							obj->amount--;
						}
					}
				}
			}
			else if(com->isPatrol)
			{
				if (com->movePatrolPos.empty())
					continue;

				if (com->startPatrol)
				{
					com->startPatrol = false;
					com->tpoint = com->movePatrolPos.begin();
					p = *com->tpoint;
					com->movePos = p;
					*point = false;
					//tpoint++;
				}
				
				if(*point && com->tpoint != com->movePatrolPos.end())
				{
					if (com->tpoint != com->movePatrolPos.end())
						com->tpoint++;
					if (com->tpoint == com->movePatrolPos.end())
						com->tpoint = com->movePatrolPos.begin();
					p = *com->tpoint;
					com->movePos = p;
					*point = false;
				}
			}
			else if (com->isDrop)
			{
				if (iventory > 0)
				{
					if (com->isMaterials)
					{
						com->isDrop = false;
						com->isMaterials = false;
						com->txt.setString("drop(matirials droped)");
						mine.push_back(new MineObj(_shape.getPosition().x, _shape.getPosition().y, 3));
						MineObj& m = *mine.back();
						m.amount = iventory % 1000000;
						iventory -= m.amount;

						//std::cout << m.amount << "   " << iventory << "\n";
					}

					if (com->isWeapon)
					{
						com->isDrop = false;
						com->isWeapon = false;
						com->txt.setString("drop(weapon droped)");
						mine.push_back(new MineObj(_shape.getPosition().x, _shape.getPosition().y, 3));
						MineObj& m = *mine.back();
						m.amount = iventory / 1000000;
						iventory -= m.amount;

						//std::cout << m.amount << "   " << iventory << "\n";
					}
				}
			}

			break;
		}
	}
	setInfoTXT();
}

void Bots::moveTo(Time deltaTime)
{
	if (finish)
	{
		time = deltaTime.asSeconds();

		normal = target - _shape.getPosition();
		float v = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
		moveToPoint = (normal / v) * speed * time;
		distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

		if (distanse >= 5)
		{
			_shape.move(moveToPoint);
		}
		else
		{
			finish = false;
			*point = true;
		}
	}
};

void Bots::setInfoTXT()
{
	infoTxt.setString(std::to_string(capacity) + "/50		health = " + std::to_string(health)
		+ "\n Tree = " + std::to_string((iventory / 100) % 100)
		+ "\n Stone = " + std::to_string((iventory / 10000) % 100)
		+ "\n Iron = " + std::to_string(iventory % 100));
}
