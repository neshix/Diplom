#pragma once

#include "livingEntity.h"

class Leviathan : public livingEntity
{
public:
	Leviathan();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};