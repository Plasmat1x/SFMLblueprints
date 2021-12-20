// SFMLblueprints.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int mmain(int argc, char* argv[]) // test
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "StaR");
    window.setFramerateLimit(60);

    //create circle
    sf::CircleShape circle(150);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(10, 20);

    //gameloop
    while (window.isOpen())
    {
        //manage events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed)
                or (event.type == sf::Event::KeyPressed
                    and event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        window.clear();
        window.draw(circle);
        window.display();
    }

    return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
