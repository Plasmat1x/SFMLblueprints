#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "World.h"

class Game
{
public:
    Game(const Game&) = delete; //delete constructor ??
    Game& operator=(const Game&) = delete; //delete copy operator
    //make class noCopyable
    Game(int x = 1600, int y = 900);
    void run(int frame_per_second = 30);
    void initLevel();

private:

    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void reset();

    sf::RenderWindow _window;

    World _world;
    sf::Time _nextSaucer;
    sf::Text _txt;
};
