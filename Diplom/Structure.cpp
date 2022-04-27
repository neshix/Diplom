#include "Structure.h"

Structure::Structure(std::string selStruct): Entity(50)
{
	name = selStruct;
	speed = 0;

	if (name == "wooden wall")
	{
		health = 100;

		_shape.setFillColor(Color(253, 235, 165, 255));
		_shape.setOutlineColor(Color::White);
	}
	else if (name == "iron wall")
	{
		health = 250;

		_shape.setFillColor(Color(5, 127, 233, 255));
		_shape.setOutlineColor(Color::White);
	}
	else if (name == "stone wall")
	{
		health = 500;

		_shape.setFillColor(Color(120, 119, 118, 255));
		_shape.setOutlineColor(Color::White);
	}
	else if (name == "gates")
	{
		gates = true;
		health = 250;

		_shape.setFillColor(Color(254, 134, 21, 255));
		_shape.setOutlineColor(Color::White);
	}
	else if (name == "factory")
	{
		factory = true;
		health = 100;

		_shape.setFillColor(Color(254, 127, 233, 255));
		_shape.setOutlineColor(Color::White);
	}
	else if (name == "storage")
	{
		storage = true;
		health = 100;

		_shape.setFillColor(Color(254, 255, 83, 255));
		_shape.setOutlineColor(Color::White);
	}
}
