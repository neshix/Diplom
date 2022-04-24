#include "Console.h"

Console::Console()
{
	consol.setSize(Vector2f(200, 800));
	consol.setPosition(1400, 0);
	consol.setFillColor(Color::Red);

	bAdd.setSize(Vector2f(50, 50));
	bAdd.setPosition(1400, 0);
	bAdd.setFillColor(Color(255, 100, 0, 255));
};

