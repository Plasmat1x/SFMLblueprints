#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>

#include "ActionTarget.h"
#include "Configuration.h"

class Player : public sf::Drawable, public ActionTarget<int>
{
public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player();

    template<typename ... Args>
    void setPosition(Args&& ... args);

    void processEvents();
    void update(sf::Time deltaTime);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite _ship;
    sf::Vector2f _velocity;

    bool _isMoving;
    int _rotation;

    static ActionMap<int> _playerInputs;

};

//#include "Player.tpl"
#include <utility>

template<typename ... Args>
void Player::setPosition(Args&& ... args)
{
    _ship.setPosition(std::forward<Args>(args)...);
}
