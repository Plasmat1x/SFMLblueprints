#pragma once
#define _USE_MATH_DEFINES

#include "ActionTarget.h"
#include "Entity.h"

class Player : public Entity, public ActionTarget<int>
{
public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(World& world);

    virtual bool isCollide(const Entity& other) const;
    virtual void update(sf::Time deltaTime);

    void processEvents();

    void shoot();

    void goToHypespace();

    virtual void onDestroy();

private:

    bool _isMoving;
    bool _isMovingBack;
    int _rotation;

    sf::Time _timeSinceLastShoot;
};
