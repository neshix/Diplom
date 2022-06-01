#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Entity.h"

class livingEntity : public Entity
{
public:
	float speed = 100;

	Vector2f moveToPoint;
	Vector2f target;

	float angle = 0;

public:
	livingEntity(std::string pathToTexture);
};
#endif LIVINGENTITY_H