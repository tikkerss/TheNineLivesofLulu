#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Menu_State.hpp"
#include "Kucing.hpp"
#include "Story.hpp"

enum class GameState {
    Menu,
    IntroAfterChoice,
    Story,
    Playing,
    Win,
    Lose
};

class Game {
private:
    sf::RenderWindow window;
    GameState state;
    sf::Font font;
    sf::View view;

    sf::Texture bgMenuTexture;
    sf::Texture bgStoryTexture;
    sf::Texture bgGameTexture;
    sf::Texture kucingTexture;
    sf::Texture bgIntroTexture;
    sf::Texture bgWinTexture;
    sf::Texture bgLoseTexture;
    sf::Music backgroundMusic;
    sf::Text tryAgainText;
    sf::Text quitText;
    sf::Text scoreText;
    sf::Text healthText;
    sf::Clock spawnClock;


    Menu* menu;
    Story* story;
    std::vector<Kucing> cat;
    int score, health;

public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
};
