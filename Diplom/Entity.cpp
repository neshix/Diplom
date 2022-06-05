#include "Entity.h"

Entity::Entity(std::string pathToTexture)
{
	life = true;

	_texture.loadFromFile(pathToTexture);
	_sprite.setTexture(_texture);
	Vector2f size= Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
	_sprite.setOrigin(size.x / 2, size.y / 2);
}

Entity::Entity()
{
	life = true;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
