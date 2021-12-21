#include "Game.h"

#include "Configuration.h"
#include "random.h"
#include "Meteor.h"
#include "Saucer.h"
#include "Player.h"

Game::Game(int x, int y) :
    _window(sf::VideoMode(x, y), "StarS"), _world(x, y)
{
    _txt.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
    _txt.setCharacterSize(70);
    _txt.setString("Press any key to start");

    sf::FloatRect size = _txt.getGlobalBounds();
    _txt.setOrigin(size.width / 2, size.height / 2);
    _txt.setPosition(x / 2, y / 2);
}

void Game::run(int frame_per_second)
{
    sf::Clock clock;
    sf::Time TimeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / frame_per_second);
    while (_window.isOpen())
    {
        processEvents();
        bool repaint = false;

        TimeSinceLastUpdate += clock.restart();
        while (TimeSinceLastUpdate > TimePerFrame)
        {
            TimeSinceLastUpdate -= TimePerFrame;
            repaint = true;
            update(TimePerFrame);
        }
        if (repaint)
            render();
    }
}

void Game::initLevel()
{
    int nb_meteors;
    switch (Configuration::level)
    {
    case 1: nb_meteors = 4; break;
    case 2: nb_meteors = 5; break;
    case 3: nb_meteors = 7; break;
    case 4: nb_meteors = 9; break;
    default: nb_meteors = 11; break;
    }

    for (int i = 0; i < nb_meteors; ++i)
    {
        Meteor* meteor = new BigMeteor(_world);
        do {
            meteor->setPosition(
                random(0.f, (float)_world.getX()),
                random(0.f, (float)_world.getY())
            );
        } while (_world.isCollide(*meteor));
        _world.add(meteor);
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) _window.close();
        }

        if (Configuration::isGameOver())
        {
            if (event.type == sf::Event::KeyPressed)
                reset();
        }
        else
        {
            if (Configuration::player != nullptr)
                Configuration::player->processEvent(event);
        }
    }
    if (not Configuration::isGameOver() and Configuration::player != nullptr)
        Configuration::player->processEvents();

}

void Game::update(sf::Time deltaTime)
{
    if (not Configuration::isGameOver())
    {
        _world.update(deltaTime);
        if (Configuration::player == nullptr)
        {
            Configuration::player = new Player(_world);
            Configuration::player->setPosition(_world.getX() / 2, _world.getY() / 2);
            _world.add(Configuration::player);
        }
        _nextSaucer -= deltaTime;

        if (_nextSaucer < sf::Time::Zero)
        {
            Saucer::newSaucer(_world);
            _nextSaucer = sf::seconds(random(10.f, 60.f - Configuration::level * 2));
        }

        if (_world.size() <= 1)
        {
            ++Configuration::level;
            initLevel();
        }
    }
}

void Game::render()
{
    _window.clear();
    
    if (Configuration::isGameOver())
    {
        _window.draw(_txt);
    }
    else
    {
        _window.draw(_world);
        Configuration::draw(_window);
    }

    _window.display();
}

void Game::reset()
{
    _nextSaucer = sf::seconds(random(5.f, 6.f - Configuration::level * 2));
    _world.clear();
    Configuration::player = nullptr;
    Configuration::reset();
    initLevel();
}
