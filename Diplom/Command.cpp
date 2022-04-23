#include "Command.h"

void Command::create(Vector2f mousePos, bool& isPressed)
{
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
		if (box.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Right))
		{
			isPressed = true;
			text.clear();
			text.push_back(new Text("move", font, 15));
			text.push_back(new Text("mine", font, 15));
			text.push_back(new Text("if", font, 15));
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
					if (t->getString() == "move")
					{
						txt.setString("move");
						txt.setPosition(box.getPosition());

						falcom();
						isMove = true;

						text.clear();
						break;
					}

					if (t->getString() == "mine")
					{
						txt.setString("mine");
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

					if (t->getString() == "if")
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
			//������ �� ������� ����� ������� ���� ���������
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

			//����� ������� ��������
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

	}
}

void Command::falcom()
{
	moveTarget = false;

	isMoving = false, isMove = false;

	isMine = false, mineobjinit = false;
	isMineIron = false, isMineTree = false, isMineStone = false;

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
