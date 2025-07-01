#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(800, 600), "The Nine Lives of Lulu"), state(GameState::Menu) {
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(0)));

    if (!font.loadFromFile("assets/Toasty Milk.ttf") ||
        !bgTexture.loadFromFile("assets/background.jpg") ||
        !kucingTexture.loadFromFile("assets/kucing.png") ||
        !backgroundMusic.openFromFile("assets/music.ogg")) {
        std::cerr << "Failed to load one or more assets\n";
        std::exit(1);
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    menu = new Menu(font, bgTexture, window.getSize());

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);

    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(10, 40);

    score = 0;
    health = 9;
}

Game::~Game() {
    delete menu;
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (state == GameState::Menu) {
                if (menu->isStartClicked(mousePos)) {
                    state = GameState::Playing;
                    score = 0;
                    health = 9;
                    boxes.clear();
                    spawnClock.restart();
                }
                if (menu->isQuitClicked(mousePos)) {
                    window.close();
                }
            } else if (state == GameState::Playing) {
                for (auto it = boxes.begin(); it != boxes.end();) {
                    if (it->isClicked(mousePos)) {
                        it = boxes.erase(it);
                        score++;
                    } else {
                        ++it;
                    }
                }
            }
        }
    }
}

void Game::update() {
    if (state == GameState::Playing) {
        if (spawnClock.getElapsedTime().asSeconds() > 1.0f) {
            float x = static_cast<float>(std::rand() % (window.getSize().x - 40));
            boxes.emplace_back(x, &kucingTexture);
            spawnClock.restart();
        }

        for (auto it = boxes.begin(); it != boxes.end();) {
            it->update();
            if (it->isOutOfScreen(window.getSize().y)) {
                it = boxes.erase(it);
                health--;
                if (health <= 0) {
                    std::cout << "Game Over!\n";
                    state = GameState::Menu;
                }
            } else {
                ++it;
            }
        }

        scoreText.setString("Score: " + std::to_string(score));
        healthText.setString("Health: " + std::to_string(health));
    }
}

void Game::render() {
    window.clear();
    if (state == GameState::Menu) {
        menu->draw(window);
    } else {
        sf::Sprite bg(bgTexture);
        bg.setScale(
            window.getSize().x / (float)bgTexture.getSize().x,
            window.getSize().y / (float)bgTexture.getSize().y
        );
        window.draw(bg);

        for (const auto& box : boxes)
            window.draw(box.sprite);

        window.draw(scoreText);
        window.draw(healthText);
    }
    window.display();
}
