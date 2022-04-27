#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Structure : public Entity
{
private:
	std::string name;

	bool gates = false;
	bool factory = false;
	bool storage = false;

public:
	Structure(std::string name);
};

