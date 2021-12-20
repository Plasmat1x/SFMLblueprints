#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:
    Game(const Game&) = delete; //delete constructor
    Game& operator=(const Game&) = delete; //delete copy operator
    //make class noCopyable
    Game();
    void run(int frame_per_second);

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    sf::RenderWindow _window;
    Player _player;
};

int main(int argc, char* argv[])
{
    Game game;
    game.run(60);

    return EXIT_SUCCESS;
}
