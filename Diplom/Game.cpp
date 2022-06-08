#include "Game.h"

Game::Game(int X, int Y) : _window(VideoMode(X,Y), "diplom")
{
    if (!font.loadFromFile("fons/calibri.ttf")) std::cout << "ne naideno";
}

void Game::run(int minimum_frame_per_seconds)
{
    generator();

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
    pixelPos = Mouse::getPosition(_window);
    mousePos = _window.mapPixelToCoords(pixelPos);

    camera.update(deltaTime, wSize);
    storage.setPos(camera.view.getCenter());

    for (auto& l : leviathans)
    {
        l->update(deltaTime, enemys, bots);
    }

    for (auto& e : enemys)
    {
        e->update(deltaTime, enemys, leviathans, bots, structure);
    }

    for (auto& bot : bots)
    {
        bot->update(mousePos, mineobj, structure, storage, enemys, bullets);
        bot->moveTo(deltaTime);

        //выбор бота
        if (Mouse::isButtonPressed(Mouse::Right) && bot->_sprite.getGlobalBounds().contains(mousePos))
        {
            for (auto& b : bots) { b->selected = false; }
            bot->selected = true;
        }

        //добавление команд
        if (storage.bAdd.getGlobalBounds().contains(mousePos))
        {
            storage.bAdd.setFillColor(Color(0, 255, 0, 255));
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
            storage.bAdd.setFillColor(Color(255, 100, 0, 255));
        }

        //управление командами
        if (bot->selected)
        {
            bot->delCommand(mousePos, IsKeyPressed);
            bot->setPosCommand(storage.consol.getPosition());

            //bot->update(mousePos, mineobj, structure, storage);

            for (auto& com : bot->command)
            {
                com->create(mousePos, IsKeyPressed);
            }

            //bot->_sprite.setOutlineThickness(3);
        }
        else
        {
            //bot->_sprite.setOutlineThickness(0);
        }
    }

    for (auto& str: structure)
    {
        str->update(mousePos, IsKeyPressed, bots, enemys, mineobj, storage);
    }

    for (auto& bul : bullets)
        bul->update(deltaTime, enemys);

    //удаление трупов
    deads();
}

void Game::render()
{
    //Clear screen
    _window.clear(Color(255, 125, 50, 255));

    //Draw
    // камера
    _window.draw(camera);
    //обекты игры
    for (auto& m : mineobj)
    {
        _window.draw(*m);
    }

    for (auto& s : structure)
    {
        if (s->getRect().contains(mousePos))
        {
            //std::cout << "a";
            _window.draw(s->reviewBox);
        }
        _window.draw(*s);
        _window.draw(s->addB);
    }

    for (auto& bot : bots)
    {
        _window.draw(*bot);
    }

    for (auto& enemy : enemys)
    {
        _window.draw(*enemy);
    }

    for (auto& bullet : bullets)
    {
        _window.draw(*bullet);
    }
    for (auto& l : leviathans)
    {
        _window.draw(*l);
    }

    //интерфейс
    _window.draw(storage);

    for (auto& bot : bots)
        if (bot->selected)
        {
            _window.draw(bot->reviewBox);

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

void Game::deads()
{
    for (auto c = mineobj.begin(); c != mineobj.end();)
    {
        MineObj* mine = *c;
        if (mine->amount <= 0)
        {
            mine->life = false;
        }

        if (mine->life == false)
        {
            c = mineobj.erase(c);
        }
        else
        {
            c++;
        }
    }

    for (auto c = bots.begin(); c != bots.end();)
    {
        Bots* bot = *c;
        if (bot->health <= 0)
        {
            bot->life = false;
        }

        if (bot->life == false)
        {
            c = bots.erase(c);
        }
        else
        {
            c++;
        }
    }

    for (auto c = enemys.begin(); c != enemys.end();)
    {
        Enemy* enemy = *c;
        if (enemy->health <= 0)
        {
            enemy->life = false;
        }

        if (enemy->life == false)
        {
            c = enemys.erase(c);
        }
        else
        {
            c++;
        }
    }

    for (auto c = structure.begin(); c != structure.end();)
    {
        Structure* s = *c;
        if (s->health <= 0)
        {
            s->life = false;
        }

        if (s->life == false)
        {
            c = structure.erase(c);
        }
        else
        {
            c++;
        }
    }

    for (auto c = bullets.begin(); c != bullets.end();)
    {
        Bullet* bullet = *c;
        if (bullet->health <= 0)
        {
            bullet->life = false;
        }

        if (bullet->life == false)
        {
            c = bullets.erase(c);
        }
        else
        {
            c++;
        }
    }
}

void Game::generator()
{
    for (int i = 0; i <= amountStone + amountIron;)
    {
        if (amountStone >=0)
        {
            int w = rand() % wSize - wSize / 2;
            int h = rand() % wSize - wSize / 2;
            mineobj.push_back(new MineObj(w, h, 0));
            i++;
        }

        if (amountIron >= 0)
        {
            int w = rand() % wSize - wSize / 2;
            int h = rand() % wSize - wSize / 2;
            mineobj.push_back(new MineObj(w, h, 1));
            i++;
        }
    }

    for (size_t i = 0; i < amountBoss; i++)
    {
        int gener = rand() % 80;

        int x = 0, y = 0;

        if (gener <= 20)
        {
            x = rand() % wSize - wSize / 2;
            y = wSize / 2 - 500;
        }

        if(gener <= 40 && gener > 20)
        {
            y = rand() % wSize - wSize / 2;
            x = wSize / 2 - 500;
        }

        if (gener <= 60 && gener > 40)
        {
            x = rand() % wSize - wSize / 2;
            y = -wSize / 2 + 500;
        }

        if (gener <= 80 && gener > 60)
        {
            y = rand() % wSize - wSize / 2;
            x = -wSize / 2 + 500;
        }

        std::cout << x << "  " << y << " " << gener <<  "\n";
        leviathans.push_back(new Leviathan(x, y));
    }

    bots.push_back(new Bots);
    bots.push_back(new Bots(300, 300));

    //leviathans.push_back(new Leviathan);
}