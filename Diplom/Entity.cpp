#include "Entity.h"

Entity::Entity()
{
	life = true;
	//_sprite.setTexture(_texture);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
