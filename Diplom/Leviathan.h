#pragma once

#include "livingEntity.h"
#include "Enemy.h"

class Leviathan : public livingEntity
{
private:
	bool action = false;
	bool wait = false;

	int random = 0;
	int waitingTime = 0;

	Clock cl;
	Time t;

	Clock clSpawn;
	Time tSpawn;

public:
	Leviathan();

	void update(Time deltaTime, std::list<Enemy*>& enemy);
	void move(Time deltaTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};