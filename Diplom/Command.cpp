#include "Command.h"

void Command::create(Vector2f mousePos, bool& isPressed)
{
	//std::cout << isPressed << "\n";
	if (!isPressed)
	{

		if (txtpriority.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
		{
			isPressed = true;
			if (priority <= 9)
			{
				priority++;
			}
			else
			{
				priority = 1;
			}
			txtpriority.setString(std::to_string(priority));
		}

		//���� ����� �� ������� �������
		if (plusb.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
		{
			falcom();

			isPressed = true;
			text.clear();
			text.push_back(new Text("move", font, 15));
			text.push_back(new Text("mine", font, 15));
			text.push_back(new Text("patrol", font, 15));
			text.push_back(new Text("build", font, 15));
			text.push_back(new Text("attack", font, 15));
			text.push_back(new Text("drop", font, 15));
			text.push_back(new Text("pickUp", font, 15));

			//text.push_back(new Text("if", font, 15));//��� �������� if ���� �������(
		}

		//��������� ������� �� �����
		for (auto& t : text)
		{
			if (t->getGlobalBounds().contains(mousePos))
			{
				t->setFillColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isPressed = true;

					//�����������++
					if (t->getString() == "move")
					{
						txt.setString(t->getString() + " -> ");
						txt.setPosition(box.getPosition());

						//falcom();
						isMove = true;

						text.clear();
						choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
						choice->setSize(Vector2f(50, 15));
						choice->setFillColor(Color::Green);
						break;
					}

					//�����������++
					if (t->getString() == "mine")
					{
						txt.setString(t->getString() + " -> ");
						txt.setPosition(box.getPosition());

						//falcom();
						isMine = true;
						moveTarget = true;

						text.clear();
						choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
						choice->setSize(Vector2f(50, 15));
						choice->setFillColor(Color::Green);
						break;
					}

					//�����������++
					if (t->getString() == "patrol")
					{
						txt.setString(t->getString() + " -> ");
						txt.setPosition(box.getPosition());

						//falcom();
						movePatrolPos.clear();
						points.clear();
						isPatrol = true;

						text.clear();
						choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
						choice->setSize(Vector2f(50, 15));
						choice->setFillColor(Color::Green);
						break;
					}

					//�����������++
					if (t->getString() == "build")
					{
						txt.setString(t->getString() + " -> ");
						txt.setPosition(box.getPosition());

						//falcom();
						isBuild = true;

						text.clear();
						choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
						choice->setSize(Vector2f(50, 15));
						choice->setFillColor(Color::Green);
						break;
					}

					//�����������++
					if (t->getString() == "attack")
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						//falcom();
						isAttack = true;

						text.clear();
						break;
					}

					//����������� ��������
					if (t->getString() == "drop")
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						//falcom();
						isDrop = true;

						text.clear();
						//text.push_back(new Text("materials", font, 15));
						break;
					}

					//����������� �������� (�������� ����� ������������)
					if (t->getString() == "pickUp")
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						//falcom();
						isPickUp = true;

						text.clear();
						//text.push_back(new Text("materials", font, 15));
						break;
					}
				}
			}
			else
			{
				t->setFillColor(Color::White);
			}
		}

		//++
		if (isMove)
		{
			//������ �� ������� ����� ������� ���� ���������
			if (choice->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
			{
				isPressed = true;
				choice->setFillColor(Color(150, 255, 0, 255));
				isMoving = true;
			}
			else if (!isMoving)
			{
				choice->setFillColor(Color::Green);
			}

			//����� ������� ��������
			if (Mouse::isButtonPressed(Mouse::Right) && isMoving == true)
			{
				isMoving = false;
				onPoint = false;
				moveTarget = true;
				movePos = mousePos;
				mpoint.setPosition(mousePos);
			}
		}

		//++
		if (isMine)
		{
			if (choice->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
			{
				text.clear();
				text.push_back(new Text("Iron", font, 15));
				text.push_back(new Text("Stone", font, 15));
			}

			//����� ���� ������
			for (auto& t : text)
			{
				if (t->getGlobalBounds().contains(mousePos))
				{
					t->setFillColor(Color::Green);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						mineobjinit = false;
						isPressed = true;
						if (t->getString() == "Iron")
						{
							txt.setString("mine -> Iron ");
							txt.setPosition(box.getPosition());
							isMineIron = true;
							choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
							break;
						}

						if (t->getString() == "Stone")
						{
							txt.setString("mine -> Stone ");
							txt.setPosition(box.getPosition());
							isMineStone = true;
							choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
							break;
						}
					}
				}
				else
				{
					t->setFillColor(Color::White);
				}
			}
		}

		//++
		if (isPatrol)
		{
			//������ �� ������� ����� ������� ���� ���������
			if (choice->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && !isMoving)
			{
				isPressed = true;
				choice->setFillColor(Color(150, 255, 0, 255));
				isMoving = true;
			}
			else if (choice->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && isMoving)
			{
				isPressed = true;
				isMoving = false;
				choice->setFillColor(Color::Green);
			}

			//����� ������� ��������
			if (Mouse::isButtonPressed(Mouse::Right) && isMoving == true)
			{
				isPressed = true;

				startPatrol = true;
				onPoint = false;
				moveTarget = true;
				movePatrolPos.push_back(mousePos);

				ppoint.setPosition(mousePos);
				points.push_back(ppoint);

				txt.setString("patrol -> " + std::to_string(movePatrolPos.size()) + " ");
				choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
			}
		}

		//++
		if (isBuild)
		{
			if (choice->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
			{
				text.clear();
				text.push_back(new Text("factory", font, 15));
				text.push_back(new Text("storage", font, 15));
			}

			if (Mouse::isButtonPressed(Mouse::Left) && bildpos)
			{
				isPressed = true;
				bildpos = false;
				startbulid = true;
				movePos = mousePos;
			}

			for (auto& t : text)
			{
				if (t->getGlobalBounds().contains(mousePos))
				{
					t->setFillColor(Color::Green);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						isPressed = true;
						bildpos = true;

						buildingName = t->getString();
						txt.setString("Build -> " + buildingName + " ");
						txt.setPosition(box.getPosition());
						choice->setPosition(txt.getPosition().x + txt.getGlobalBounds().width, txt.getPosition().y + 3);
						text.clear();
						break;
					}
				}
				else
				{
					t->setFillColor(Color::White);
				}
			}
		}

		//+
		if (isDrop)
		{
			for (auto& t : text)
			{
				if (t->getGlobalBounds().contains(mousePos))
				{
					t->setFillColor(Color::Green);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						isPressed = true;

						if (t->getString() == "materials")
						{
							txt.setString("drop(materials)");
							txt.setPosition(box.getPosition());

							isMaterials = true;

							text.clear();
							break;
						}
					}
				}
				else
				{
					t->setFillColor(Color::White);
				}
			}
		}
	}
}

void Command::falcom()
{
	moveTarget = false;

	isMove = false, isMoving = false;

	isMine = false, mineobjinit = false;
	isMineIron = false, isMineStone = false;

	isPatrol = false;
	startPatrol = false;

	isBuild = false;
	bildpos = false, startbulid = false;
	
	isAttack = false;

	isDrop = false;
	isMaterials = false, isWeapon = false;
	isPickUp = false;

	onPoint = true;

	txt.setString("");
	delete choice;
	choice = new RectangleShape;
}

void Command::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& p : points)
	{
		target.draw(p, states);
	}

	if (isMove)
		target.draw(mpoint, states);

	target.draw(box, states);
	target.draw(plusb, states);
	target.draw(xb, states);
	target.draw(txt, states);
	target.draw(txtpriority, states);
	for (auto& t : text)
	{
		target.draw(*t, states);
	}

	target.draw(*choice, states);
}
