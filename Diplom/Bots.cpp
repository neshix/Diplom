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
		if (Mouse::isButtonPressed(Mouse::Left) && com->xb.getGlobalBounds().contains(mpos) && press == false)
		{
			com->falcom();

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
		dbpos = Vector2f(com->box.getPosition().x + (com->box.getSize().x - com->xb.getGlobalBounds().width),
						 com->box.getPosition().y + (com->box.getSize().y - com->xb.getGlobalBounds().height));
		com->txt.setPosition(com->box.getPosition());
		com->choice->setPosition(com->txt.getPosition().x + com->txt.getGlobalBounds().width, com->txt.getPosition().y + 3);
		com->xb.setPosition(dbpos);
		com->plusb.setPosition(dbpos.x - 25, dbpos.y);

		com->priorityBox.setPosition(com->box.getPosition().x + (com->box.getSize().x - 20), com->box.getPosition().y);
		com->txtpriority.setPosition(com->priorityBox.getPosition().x + 5 , com->priorityBox.getPosition().y);

		com->txtif.setPosition(com->box.getPosition().x, com->box.getPosition().y + (com->box.getSize().y / 2));
		com->iBox.setPosition(com->txtif.getPosition().x + 25, com->txtif.getPosition().y + 5);

		int k = 0;
		float tsize = 0;
		for (auto& t : com->text)
		{
			if (t->getGlobalBounds().width +5 >= tsize)
			{
				tsize = t->getGlobalBounds().width + 5;
			}
			t->setPosition(Vector2f(com->box.getPosition().x - tsize, com->box.getPosition().y + (t->getCharacterSize() * k)));
			k++;
		}
		i++;
	}

	info.setPosition(pos.x - info.getSize().x, pos.y);
	infoTxt.setPosition(info.getPosition().x + 1, info.getPosition().y + 1);
}

void Bots::update(Vector2f mp, std::list<MineObj*>& mine, std::list<Structure*>& str, Storage& stor, std::list<Enemy*>& enemy, std::list<Bullet*>& bul)
{
	statup(enemy);

	maxPriority = 0;
	for (auto& com : command)
	{
		if (com->priority > maxPriority)
		{
			if (com->iÑhoice == 0)
			{
				com->activcom = true;
				maxPriority = com->priority;
			}
			else if (fullInv && com->iÑhoice == 1)
			{
				com->activcom = true;
				maxPriority = com->priority;
			}
			else if (emptyInv && com->iÑhoice == 2)
			{
				com->activcom = true;
				maxPriority = com->priority;
			}
			else if (enemyDetected && com->iÑhoice == 3)
			{
				com->activcom = true;
				edt = edcl.getElapsedTime();
				if (edt.asSeconds() >= 10)
				{
					edt = edcl.restart();
				}
			}
			else if (noEnergy && com->iÑhoice == 4)
			{
				com->activcom = true;
				maxPriority = com->priority;
			}
			else
			{
				com->activcom = false;
			}

			if (edt.asSeconds() <= 10)
			{
				edt = edcl.getElapsedTime();

				maxPriority = com->priority;
			}
		}

		if (finish && com->moveTarget)
		{
			com->onPoint = false;
		}
	}

	for (auto& com : command)
	{
		if (maxPriority == com->priority && com->activcom == true)
		{
			point = &com->onPoint;
			if (!*point)
			{
				finish = true;
				target = com->movePos;
			}

			//++
			if (com->isMine)
			{
				if (!com->mineobjinit)
				{
					smallerDistance = 10000;
					for (auto& e : mine)
					{
						if (com->isMineIron && e->name == "Iron")
						{
							normal = e->_sprite.getPosition() - _sprite.getPosition();
							distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

							std::cout << distanse << "\n";

							if (smallerDistance > distanse)
							{
								com->movePos = e->_sprite.getPosition();
								com->mineobjinit = true;
								*point = false;
								obj = e;

								smallerDistance = distanse;
							}
						}

						if (com->isMineStone && e->name == "Stone")
						{
							normal = e->_sprite.getPosition() - _sprite.getPosition();
							distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

							if (smallerDistance > distanse)
							{
								com->movePos = e->_sprite.getPosition();
								com->mineobjinit = true;
								*point = false;
								obj = e;

								smallerDistance = distanse;
							}
						}
					}
					com->isMineStone = false;
					com->isMineIron = false;
				}

				if (*point && com->mineobjinit)
				{
					//êð÷ áëÿòü òóò õóÿðèòü íà÷èíàåì
					capacity = (iventory % 100) + ((iventory / 100) % 100);
					//std::cout << obj->amount << "\n";
					t = cl.getElapsedTime();
					if (capacity < 50 && t.asSeconds() >= obj->extractionTime + en)
					{
						energy--;
						t = cl.restart();
						if (obj->name == "Stone")
						{
							iventory += 1;
							obj->amount--;
						}

						if (obj->name == "Iron")
						{
							iventory += 100;
							obj->amount--;
						}
					}

					if (obj->amount <= 0 )
					{
						com->isMineStone = true;
						com->isMineIron = true;
						com->mineobjinit = false;
					}
				}
			}

			//++
			if (com->isPatrol)
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

			//++
			if (com->isDrop)
			{
				if (iventory > 0)
				{
					if (com->droping)
					{
						if (*point)
						{
							com->txt.setString("drop -> ");
							mine.push_back(new MineObj(_sprite.getPosition().x, _sprite.getPosition().y, 2));
							MineObj& m = *mine.back();
							m.amount = iventory % 1000000;
							iventory -= m.amount;

							capacity = (iventory % 100) + ((iventory / 100) % 100);
						}
					}
				}
			}

			//++
			if (com->isPickUp)
			{
				if (!com->mineobjinit)
				{
					smallerDistance = 10000;
					for (auto& e : mine)
					{
						if (e->name == "Materials")
						{
							normal = e->_sprite.getPosition() - _sprite.getPosition();
							distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

							if (smallerDistance > distanse)
							{
								com->movePos = obj->_sprite.getPosition();
								*point = false;

								com->mineobjinit = true;
								obj = e;

								smallerDistance = distanse;
							}
						}
					}
				}

				if (*point && com->mineobjinit)
				{
					capacity = (iventory % 100) + ((iventory / 100) % 100);
					
					if (capacity < 50)
					{
						if (obj->name == "Materials")
						{
							com->mineobjinit = false;

							iventory += obj->amount;
							obj->life = false;
						}
					}
				}
			}

			//++
			if (com->isBuild)
			{
				build = true;
				if (com->startbulid)
				{
					int i = 0;
					if (com->buildingName == "factory")
					{
						i = 2020;
						if (stor.delMatirials(i))
						{
							if (*point)
							{
								stor.dm(i);

								com->startbulid = false;

								*point = false;
								str.push_back(new Structure(com->buildingName, com->movePos));
							}
						}
					}

					if (com->buildingName == "storage")
					{
						i = 2010;
						if (stor.delMatirials(i))
						{
							if (*point)
							{
								stor.dm(i);

								com->startbulid = false;

								*point = false;
								str.push_back(new Structure(com->buildingName, com->movePos));
							}
						}
					}

					if (com->buildingName == "energy tower")
					{
						i = 3030;
						if (stor.delMatirials(i))
						{
							if (*point)
							{
								stor.dm(i);

								com->startbulid = false;

								*point = false;
								str.push_back(new Structure(com->buildingName, com->movePos));
							}
						}
					}

				}
			}

			//++
			if (com->isAttack)
			{
				//std::cout << "a";
				for (auto& e : enemy)
				{
					normal = e->_sprite.getPosition() - _sprite.getPosition();
					distanse = sqrt(normal.x * normal.x + normal.y * normal.y);
					if (distanse >= 200)
					{
						*point = false;
						com->movePos = e->_sprite.getPosition();
					}
					else
					{
						t = cl.getElapsedTime();
						if (t.asMilliseconds() >= 500 + (en * 50))
						{
							energy--;
							t = cl.restart();
							bul.push_back(new Bullet(_sprite.getPosition(), e->_sprite.getPosition()));
						}
						finish = false;
						*point = true;
					}
				}
			}

			break;
		}
	}
	setInfoTXT();
}

void Bots::statup(std::list<Enemy*>& enemy)
{
	capacity = (iventory % 100) + ((iventory / 100) % 100);
	enemyDetected = false;

	if (capacity >= 50)
	{
		fullInv = true;
		emptyInv = false;
	}
	else
	{
		fullInv = false;
		emptyInv = true;
	}

	for (auto& e: enemy)
	{
		if (e->_sprite.getGlobalBounds().intersects(reviewBox.getGlobalBounds()))
			enemyDetected = true;
	}

	if (energy >= 99)
	{
		noEnergy = false;
	}

	if (energy >= 0)
	{
		speed = 100;
		en = 0;
	}
	else
	{
		en = 20;
		speed = 15;
		noEnergy = true;
	}
	//std::cout << "fullInv: " << fullInv << " emptyInv: " << emptyInv << " enemyDetected: " << enemyDetected << "\n";
}

void Bots::moveTo(Time deltaTime)
{
	if (finish)
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
			finish = false;
			*point = true;
		}

		t = enrgycl.getElapsedTime();
		if (t.asSeconds() >= 2)
		{
			t = enrgycl.restart();
			energy--;
		}
	}
};

void Bots::setInfoTXT()
{
	infoTxt.setString(std::to_string(capacity) + "/50		health = " + std::to_string(health)
		+ "\n Iron = " + std::to_string((iventory / 100) % 100)
		+ "\n Stone = " + std::to_string(iventory % 100)
		+ "\n" "\n Energy = " + std::to_string(energy)
	);
}
