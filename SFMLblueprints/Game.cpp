#include "Game.h"

Game::Game() :
    _window(sf::VideoMode(800, 600), "StarS")
{
    _player.setPosition(100, 100);
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
    }

    _player.processEvents();
}

void Game::update(sf::Time deltaTime)
{
    _player.update(deltaTime);
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);
    _window.display();
}
