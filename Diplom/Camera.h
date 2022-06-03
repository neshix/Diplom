#pragma once

#include "Entity.h"


class Camera : public Drawable
{
public:
	View view;
	Vector2f velocity;

	float speed = 400;

public:
	Camera()
	{
		view.reset(sf::FloatRect(0, 0, 1600, 900));
	};

	void update(Time deltaTime)
	{
		float time = deltaTime.asSeconds();

		velocity.x = 0;
		velocity.y = 0;

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			velocity.y = -speed * time;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			velocity.x = -speed * time;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			velocity.y = speed * time;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			velocity.x = speed * time;
		}

		view.move(velocity);
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.setView(view);
	};
};

