#include "Structure.h"

Structure::Structure(std::string selStruct): Entity(50)
{
	name = selStruct;
	speed = 0;
	build = true;

	if (name == "wooden wall")
	{
		health = 100;

		this->_shape.setFillColor(Color(253, 235, 165, 255));
		this->_shape.setOutlineColor(Color::White);
	}
	else if (name == "iron wall")
	{
		health = 250;

		this->_shape.setFillColor(Color(5, 127, 233, 255));
		this->_shape.setOutlineColor(Color::White);
	}
	else if (name == "stone wall")
	{
		health = 500;

		this->_shape.setFillColor(Color(120, 119, 118, 255));
		this->_shape.setOutlineColor(Color::White);
	}
	else if (name == "gates")
	{
		gates = true;
		health = 250;

		this->_shape.setFillColor(Color(254, 134, 21, 255));
		this->_shape.setOutlineColor(Color::White);
	}
	else if (name == "factory")
	{
		factory = true;
		health = 100;

		this->_shape.setFillColor(Color(254, 127, 233, 255));
		this->_shape.setOutlineColor(Color::White);
	}
	else if (name == "storage")
	{
		storage = true;
		health = 100;

		this->_shape.setFillColor(Color(254, 255, 83, 255));
		this->_shape.setOutlineColor(Color::White);
	}
}

void Structure::update(Vector2f mousePos, bool& kp, std::list<MineObj*> mine, std::list<Bots*> bot)
{

	if (build)
	{
		_shape.setPosition(mousePos);
		for (auto& m : mine)
		{
			if (_shape.getGlobalBounds().intersects(m->getobj().getGlobalBounds()))
			{
				constructionZone = false;
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left) && !kp && constructionZone)
		{
			kp = true;
			build = false;
		}

		constructionZone = true;
	}

	if (gates)
	{

	}
	else if (factory)
	{

	}
	else if (storage)
	{

	}
	
}
