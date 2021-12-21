// SFMLblueprint2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <box2d/box2d.h>

#include <iostream>
#include <vector>

#include "Converter.h"

b2Body* b2createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_dynamicBody);
sf::RectangleShape* sfcreateBox(int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_dynamicBody);

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "b2d");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    std::vector<b2Body*> bodies;
    std::vector<sf::RectangleShape*> shapes;
    bodies.emplace_back(b2createBox(world, 400, 590, 800, 20, b2_staticBody));
    shapes.emplace_back(sfcreateBox(400, 590, 800, 20, b2_staticBody));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;
            bodies.emplace_back(b2createBox(world, x, y, 32, 32));
            shapes.emplace_back(sfcreateBox(x, y, 32, 32));
        }
       
        world.Step(1.0 / 60, int32(8), int32(3));
        window.clear();

        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->setPosition(converter::metersToPixels(bodies[i]->GetPosition().x),
                converter::metersToPixels(bodies[i]->GetPosition().y));
            shapes[i]->setRotation(converter::radToDeg<double>(bodies[i]->GetAngle()));
            window.draw(*shapes[i]);

        }
        window.display();
    }

    for (b2Body* body : bodies)
    {
        world.DestroyBody(body);
    }

    for (sf::RectangleShape* shape : shapes)
    {
        delete shape;
    }

    return 0;
}

b2Body* b2createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(converter::pixelsToMeters<double>(pos_x),
        converter::pixelsToMeters<double>(pos_y));
    bodyDef.type = type;
    b2PolygonShape b2shape;
    b2shape.SetAsBox(converter::pixelsToMeters<double>(size_x / 2.0),
        converter::pixelsToMeters<double>(size_y / 2.0));

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.4;
    fixtureDef.restitution = 0.5;
    fixtureDef.shape = &b2shape;

    b2Body* res = world.CreateBody(&bodyDef);
    res->CreateFixture(&fixtureDef);

    return res;
}

sf::RectangleShape* sfcreateBox(int pos_x, int pos_y, int size_x, int size_y, b2BodyType type)
{
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(size_x, size_y));
    shape->setOrigin(size_x / 2, size_y / 2);
    shape->setPosition(sf::Vector2f(pos_x, pos_y));
    if (type == b2_dynamicBody)
        shape->setFillColor(sf::Color::Blue);
    else
        shape->setFillColor(sf::Color::White);

    return shape;
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
