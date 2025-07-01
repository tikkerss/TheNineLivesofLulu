#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Menu.hpp"
#include "Kucing.hpp"

enum class GameState {
    Menu,
    Playing
};

class Game {
private:
    sf::RenderWindow window;
    GameState state;
    sf::Font font;
    sf::Texture bgTexture;
    sf::Texture kucingTexture;
    sf::Music backgroundMusic;

    Menu* menu;
    std::vector<Kucing> boxes;
    sf::Clock spawnClock;
    int score, health;
    sf::Text scoreText, healthText;

public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
};
