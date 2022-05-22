#include "Entity.h"

Entity::Entity(std::string pathToTexture)
{
	life = true;
	_texture.loadFromFile(pathToTexture);
	_sprite.setTexture(_texture);
}

Entity::Entity()
{
	life = true;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
