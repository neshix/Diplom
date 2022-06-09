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

	void update(Time deltaTime, int worldSize)
	{
		float time = deltaTime.asSeconds();

		velocity.x = 0;
		velocity.y = 0;

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			velocity.y = -speed * time;

			int h = view.getViewport().height / 2;
			if (view.getCenter().y - h <= -worldSize / 2)
			{
				velocity.y = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			velocity.x = -speed * time;

			int w = view.getViewport().width / 2;
			if (view.getCenter().x - w <= -worldSize / 2)
			{
				velocity.x = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			velocity.y = speed * time;

			int h = view.getViewport().height / 2;
			if (view.getCenter().y + h >= worldSize / 2)
			{
				velocity.y = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			velocity.x = speed * time;

			int w = view.getViewport().width / 2;
			if (view.getCenter().x + w >= worldSize / 2)
			{
				velocity.x = 0;
			}
		}

		view.move(velocity);
	};

	Vector2f getCenter()
	{
		return view.getCenter();
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.setView(view);
	};
};

