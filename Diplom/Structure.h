#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Structure : public Entity
{
private:
	std::string name;

	bool gates = false;
	bool factory = false;
	bool storage = false;

	bool build = false;

public:
	Structure(std::string name);

	void update(Vector2f mousePos, bool& kp);
};
#endif STRUCTURE_H