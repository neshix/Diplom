#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Entity.h"
#include "MineObj.h"
#include "Bots.h"
#include "Storage.h"

class Structure : public Entity
{
private:
	std::string name;

	bool gates = false;
	bool factory = false;
	bool storage = false;

	bool build = false;
	bool constructionZone = false;

public:
	Structure(std::string name);
	void update(Vector2f mousePos, bool& kp, std::list<Bots*>& bot, std::list<MineObj*>& mine, Storage& store);
};
#endif