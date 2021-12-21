#include "Configuration.h"
#include "random.h"

ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

ActionMap<int> Configuration::playerInputs;

int Configuration::level;
int Configuration::lives;

Player* Configuration::player = nullptr;

int Configuration::_score;

sf::Text Configuration::_txt_score;
sf::Sprite Configuration::_spr_life;


void Configuration::initialize()
{
    initTextures();
    initFonts();
    initSounds();
    initMusics();

    initPlayerInputs();

    rand_init();
    _txt_score.setFont(fonts.get(Fonts::Gui));
    _txt_score.setCharacterSize(24);
    _spr_life.setTexture(textures.get(Textures::PlayerLife));

    musics.get(Music::Theme).setLoop(true);
    musics.get(Music::Theme).play();

    lives = level = _score = -1;
}

void Configuration::reset()
{
    level = 1;
    lives = 3;
    _score = 0;
    _txt_score.setString("0");
}

bool Configuration::isGameOver()
{
    return lives < 0;
}

void Configuration::addScore(int s)
{
    int old_score = _score;
    _score += s * level;
    lives += _score / 10000 - old_score / 10000;
    _txt_score.setString(std::to_string(_score));
}

int Configuration::getScore()
{
    return _score;
}

void Configuration::draw(sf::RenderTarget& target)
{
    target.draw(_txt_score);
    for (int i = 0; i < lives; ++i)
    {
        _spr_life.setPosition(40 * i, 40);
        target.draw(_spr_life);
    }
}

void Configuration::initTextures()
{
    //player
    textures.load(Textures::mPlayer, "../resources/Player/Ship.png");
    textures.load(Textures::PlayerLife, "../resources/Player/life.png");
    //saucers
    textures.load(Textures::BigSaucer, "../resources/Saucer/Big.png");
    textures.load(Textures::SmallSaucer, "../resources/Saucer/Small.png");
    //meteors
    textures.load(Textures::BigMeteor1, "../resources/Meteor/Big1.png");
    textures.load(Textures::BigMeteor2, "../resources/Meteor/Big2.png");
    textures.load(Textures::BigMeteor3, "../resources/Meteor/Big3.png");
    textures.load(Textures::BigMeteor4, "../resources/Meteor/Big4.png");

    textures.load(Textures::MediumMeteor1, "../resources/Meteor/Medium1.png");
    textures.load(Textures::MediumMeteor2, "../resources/Meteor/Medium2.png");

    textures.load(Textures::SmallMeteor1, "../resources/Meteor/Small1.png");
    textures.load(Textures::SmallMeteor2, "../resources/Meteor/Small2.png");
    textures.load(Textures::SmallMeteor3, "../resources/Meteor/Small3.png");
    textures.load(Textures::SmallMeteor4, "../resources/Meteor/Small4.png");
    //lasers
    textures.load(Textures::ShootPlayer, "../resources/Shoot/Player.png");
    textures.load(Textures::ShootSaucer, "../resources/Shoot/Saucer.png");
}

void Configuration::initFonts()
{
    fonts.load(Fonts::Gui, "../resources/font/trs-million.ttf");
}

void Configuration::initSounds()
{
    //laser
    sounds.load(Sounds::LaserPlayer, "../resources/sounds/laser1.ogg");
    sounds.load(Sounds::LaserEnemy, "../resources/sounds/laser2.ogg");
    //saucers
    sounds.load(Sounds::SaucerSpawn1, "../resources/sounds/spawn1.flac");
    sounds.load(Sounds::SaucerSpawn2, "../resources/sounds/spawn2.flac");
    // Boom
    sounds.load(Sounds::Boom, "../resources/sounds/boom.flac");
    sounds.load(Sounds::Boom2, "../resources/sounds/boom2.flac");
    // Explosion
    sounds.load(Sounds::Explosion1, "../resources/sounds/explosion1.flac");
    sounds.load(Sounds::Explosion2, "../resources/sounds/explosion2.flac");
    sounds.load(Sounds::Explosion3, "../resources/sounds/explosion3.flac");
    //others
    sounds.load(Sounds::Jump, "../resources/sounds/hyperspace.flac");
}

void Configuration::initMusics()
{
    musics.load(Music::Theme, "../resources/musics/theme.ogg");
}

void Configuration::initPlayerInputs()
{
    playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
    playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
    playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
    playerInputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::Down, Action::Type::Released));
    playerInputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Space));
}
