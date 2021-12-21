#include "Shoot.h"

#include "Collision.h"
#include "Enemy.h"
#include "Player.h"
#include "Saucer.h"
#include "Meteor.h"
#include "World.h"

#include "random.h"

Shoot::Shoot(Configuration::Textures textures, World& world) : 
    Entity(textures, world)
{
    float angle = random(0.f, 2.f * M_PI);
    _impulse = sf::Vector2f(std::cos(angle), std::sin(angle));
}

void Shoot::update(sf::Time deltaTime)
{
    float seconds = deltaTime.asSeconds();
    _sprite.move(seconds * _impulse);
    _duration -= deltaTime;

    if (_duration < sf::Time::Zero)
    {
        _alive = false;
    }
}

ShootPlayer::ShootPlayer(Player& from) :
    Shoot(Configuration::Textures::ShootPlayer, from._world)
{
    _duration = sf::seconds(5);

    float angle = from._sprite.getRotation() / 180 * M_PI - M_PI / 2;
    _impulse = sf::Vector2f(std::cos(angle), std::sin(angle));

    setPosition(from.getPosition());
    _sprite.setRotation(from._sprite.getRotation());
    _world.add(Configuration::Sounds::LaserPlayer);
}

bool ShootPlayer::isCollide(const Entity& other) const
{
    if (dynamic_cast<const Enemy*>(&other) != nullptr)
    {
        return Collision::circleTest(_sprite, other._sprite);
    }
    return false;
}

ShootSaucer::ShootSaucer(SmallSaucer& from) :
    Shoot(Configuration::Textures::ShootSaucer, from._world)
{
    _duration = sf::seconds(5);

    sf::Vector2f pos = Configuration::player->getPosition() - from.getPosition();

    float accuracy_lost = random(-1.f, 1.f) * M_PI / ((200 + Configuration::getScore()) / 100.f);
    float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
    float angle_deg = angle_rad * 180 / M_PI;

    _impulse = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;

    setPosition(from.getPosition());
    _sprite.setRotation(angle_deg + 90);
    _world.add(Configuration::Sounds::LaserEnemy);
}

bool ShootSaucer::isCollide(const Entity& other) const
{
    if (dynamic_cast<const Player*>(&other) or dynamic_cast<const Meteor*>(&other))
    {
        return Collision::circleTest(_sprite, other._sprite);
    }
    return false;
}
