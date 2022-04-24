#include "Game.h"

Game::Game(int X, int Y) : _window(VideoMode(X,Y), "diplom")
{
    if (!font.loadFromFile("fons/calibri.ttf")) std::cout << "ne naideno";
}

void Game::run(int minimum_frame_per_seconds)
{
    bots.push_back(new Bots);
    bots.push_back(new Bots(300, 300));
    enemys.push_back(new Enemy);

    mineobj.push_back(new MineObj(50, 50, 2));
    mineobj.push_back(new MineObj(100, 300, 0));
    mineobj.push_back(new MineObj(550, 200, 1));

   Clock clock;
   Time timeSinceLastUpdate;
   Time TimePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
    
    while (_window.isOpen())
    {
        processEvents();

        timeSinceLastUpdate = clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }

        update(timeSinceLastUpdate);
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _window.close();
    }

    if (event.type == Event::MouseButtonReleased)
        IsKeyPressed = false;
}

void Game::update(Time deltaTime)
{
    Vector2i pixelPos = Mouse::getPosition(_window);
    Vector2f mousePos = _window.mapPixelToCoords(pixelPos);

    for (auto& bot : bots)
    {
        bot->moveTo(deltaTime);

        //����� ����
        if (Mouse::isButtonPressed(Mouse::Right) && bot->_shape.getGlobalBounds().contains(mousePos))
        {
            for (auto& b : bots) { b->selected = false; }
            bot->selected = true;
        }

        //���������� ������
        if (console.bAdd.getGlobalBounds().contains(mousePos))
        {
            console.bAdd.setFillColor(Color(0, 255, 0, 255));
            if (!IsKeyPressed)
            {
                if (Mouse::isButtonPressed(Mouse::Right) && bot->selected)
                {
                    bot->AddCommand(font);
                    IsKeyPressed = true;
                }
            }
        }
        else
        {
            console.bAdd.setFillColor(Color(255, 100, 0, 255));
        }

        //���������� ���������
        if (bot->selected)
        {
            bot->delCommand(mousePos, IsKeyPressed);
            bot->setPosCommand(console.consol.getPosition());

            bot->realization(mousePos, mineobj);

            for (auto& com : bot->command)
            {
                com->create(mousePos, IsKeyPressed);
            }

            bot->_shape.setOutlineThickness(3);
        }
        else
        {
            bot->_shape.setOutlineThickness(0);
        }
    }
}

void Game::render()
{
    //Clear screen
    _window.clear();

    //Draw
    //������ ����
    for (auto& bot : bots)
    {
        _window.draw(*bot);
    }

    for (auto& enemy : enemys)
    {
        _window.draw(*enemy);
    }

    for (auto& m : mineobj)
    {
        _window.draw(*m);
    }

    //���������
    _window.draw(console);

    for (auto& bot : bots)
        if (bot->selected)
        {
            _window.draw(bot->info);
            _window.draw(bot->infoTxt);
            for (auto& com : bot->command)
            {
                _window.draw(*com);
            }
        }

    //Update the window
    _window.display();
}
