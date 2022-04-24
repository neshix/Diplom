#include "Entity.h"

Entity::Entity(float radius)
{
	life = true;

	_shape.setRadius(radius);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
