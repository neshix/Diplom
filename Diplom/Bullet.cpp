#include "Bullet.h"

void Bullet::update(Time deltaTime, std::list<Enemy*>& enemy)
{
	time = deltaTime.asSeconds();

	normal = target - _sprite.getPosition();
	float v = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
	moveToPoint = (normal / v) * speed * time;
	distanse = sqrt(normal.x * normal.x + normal.y * normal.y);

	if (distanse >= 5)
	{
		_sprite.move(moveToPoint);
	}
	else
	{
		life = false;
	}

	for (auto& en : enemy)
	{
		
		if (en->_sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds()))
		{
			en->health -= 20;
			life = false;
		}
	}
}