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

		//если нажал на квадрат команды
		if (box.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Right))
		{
			isPressed = true;
			text.clear();
			text.push_back(new Text("move", font, 15));
			text.push_back(new Text("mine", font, 15));
			text.push_back(new Text("patrol", font, 15));
			text.push_back(new Text("build", font, 15));
			text.push_back(new Text("attack", font, 15));
			text.push_back(new Text("drop", font, 15));
			text.push_back(new Text("if", font, 15));
		}

		//обработка нажатия на текст
		for (auto& t : text)
		{
			if (t->getGlobalBounds().contains(mousePos))
			{
				t->setFillColor(Color::Green);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					isPressed = true;

					if (t->getString() == "move")
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						isMove = true;

						text.clear();
						break;
					}

					if (t->getString() == "mine")//реализовано
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						isMine = true;
						moveTarget = true;

						text.clear();
						text.push_back(new Text("Iron", font, 15));
						text.push_back(new Text("Tree", font, 15));
						text.push_back(new Text("Stone", font, 15));
						break;
					}

					if (t->getString() == "patrol")//реализовано
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						movePatrolPos.clear();
						isPatrol = true;

						text.clear();
						break;
					}

					if (t->getString() == "build")//не реализовано
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						isBuild = true;

						text.clear();
						text.push_back(new Text("wall", font, 15));
						text.push_back(new Text("factory", font, 15));
						text.push_back(new Text("storage", font, 15));
						break;
					}

					if (t->getString() == "attack")//не реализовано
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						isAttack = true;

						text.clear();
						break;
					}

					if (t->getString() == "drop")//не реализовано
					{
						txt.setString(t->getString());
						txt.setPosition(box.getPosition());

						falcom();
						isDrop = true;

						text.clear();
						text.push_back(new Text("all", font, 15));
						text.push_back(new Text("materials", font, 15));
						break;
					}

					if (t->getString() == "if")//не реализовано
					{
						txt.setString("if - dont work");
						txt.setPosition(box.getPosition());
						
						falcom();

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

		if (isMove)
		{
			//нажать на команду чтобы выбрать куда двигаться
			if (box.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
			{
				isPressed = true;
				box.setFillColor(Color(255, 50, 100, 255));
				isMoving = true;
			}
			else if (!isMoving)
			{
				box.setFillColor(Color(255, 50, 50, 255));
			}

			//выбор позиции движения
			if (Mouse::isButtonPressed(Mouse::Right) && isMoving == true)
			{
				isMoving = false;
				onPoint = false;
				moveTarget = true;
				movePos = mousePos;
			}

			if (onPoint)
			{
				txt.setString("move(on point)");
			}
			else
			{
				txt.setString("move(goes to the point)");
			}
		}

		if (isMine)
		{
			std::cout << isMine << "\n";
			//выбор чего копать
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
							txt.setString("mine(Iron)");
							txt.setPosition(box.getPosition());
							isMineIron = true;
							break;
						}

						if (t->getString() == "Tree")
						{
							txt.setString("mine(Tree)");
							txt.setPosition(box.getPosition());
							isMineTree = true;
							break;
						}

						if (t->getString() == "Stone")
						{
							txt.setString("mine(Stone)");
							txt.setPosition(box.getPosition());
							isMineStone = true;
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

		if (isPatrol)
		{
			//нажать на команду чтобы выбрать куда двигаться
			if (box.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && !isMoving)
			{
				isPressed = true;
				box.setFillColor(Color(255, 50, 100, 255));
				isMoving = true;
			}
			else if (box.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && isMoving)
			{
				isPressed = true;
				isMoving = false;
				box.setFillColor(Color(255, 50, 50, 255));
			}

			//выбор позиции движения
			if (Mouse::isButtonPressed(Mouse::Right) && isMoving == true)
			{
				isPressed = true;

				startPatrol = true;
				onPoint = false;
				moveTarget = true;
				movePatrolPos.push_back(mousePos);
				txt.setString("Patrol(point = " + std::to_string(movePatrolPos.size()) + ")");
			}
		}

		if (isBuild)
		{

		}

		if (isAttack)
		{

		}

		if (isDrop)
		{

		}
	}
}

void Command::falcom()
{
	moveTarget = false;
	
	isMove = false, isMoving = false;
	
	isMine = false, mineobjinit = false;
	isMineIron = false, isMineTree = false, isMineStone = false;
	
	isPatrol = false;
	
	isBuild = false;
	
	isAttack = false;
	
	isDrop = false;
	
	onPoint = true;
}

void Command::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(deldox, states);
	target.draw(txt, states);
	target.draw(txtpriority, states);
	for (auto& t : text)
	{
		target.draw(*t, states);
	}
}
