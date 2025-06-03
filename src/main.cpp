#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class GameState {
    Menu,
    Playing
};

class Kucing {
public:
    sf::RectangleShape shape;
    float speed;

    Kucing(float x) {
        shape.setSize(sf::Vector2f(40, 40));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(x, -40);
        speed = 2.0f + static_cast<float>(std::rand() % 4);
    }

    void update() {
        shape.move(0, speed);
    }

    bool isOutOfScreen(float screenHeight) const {
        return shape.getPosition().y > screenHeight;
    }

    bool isClicked(sf::Vector2f mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }
};

class Menu {
private:
    sf::Text title;
    sf::Text start;
    sf::Text quit;
    sf::Sprite background;

public:
    Menu(sf::Font& font, sf::Texture& bgTexture, sf::Vector2u windowSize) {
        // Background
        background.setTexture(bgTexture);
        background.setScale(
            windowSize.x / (float)bgTexture.getSize().x,
            windowSize.y / (float)bgTexture.getSize().y
        );

        // Title
        title.setFont(font);
        title.setString("The Nine Lives of Lulu");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::Black);
        title.setPosition(150, 50);

        // Start Button
        start.setFont(font);
        start.setString("Start");
        start.setCharacterSize(36);
        start.setFillColor(sf::Color::Black);
        start.setPosition(350, 200);

        // Quit Button
        quit.setFont(font);
        quit.setString("Quit");
        quit.setCharacterSize(36);
        quit.setFillColor(sf::Color::Black);
        quit.setPosition(350, 300);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(title);
        window.draw(start);
        window.draw(quit);
    }

    bool isStartClicked(sf::Vector2f mousePos) const {
        return start.getGlobalBounds().contains(mousePos);
    }

    bool isQuitClicked(sf::Vector2f mousePos) const {
        return quit.getGlobalBounds().contains(mousePos);
    }
};

class Game {
private:
    sf::RenderWindow window;
    GameState state;
    sf::Font font;
    sf::Texture bgTexture;
    Menu* menu;

    std::vector<Kucing> boxes;
    sf::Clock spawnClock;
    int score = 0;
    int health = 9;

    sf::Text scoreText;
    sf::Text healthText;

public:
    Game() : window(sf::VideoMode(800, 600), "The Nine Lives of Lulu"), state(GameState::Menu) {
        window.setFramerateLimit(60);
        std::srand(static_cast<unsigned>(std::time(0)));

        if (!font.loadFromFile("ARTIFAKT ELEMENT LIGHT.TTF")) {
            std::cerr << "failed" << std::endl;
            std::exit(1);
        }

        if (!bgTexture.loadFromFile("background.jpg")) {
            std::cerr << "failed" << std::endl;
            std::exit(1);
        }

        menu = new Menu(font, bgTexture, window.getSize());

        // Text UI
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(10, 10);

        healthText.setFont(font);
        healthText.setCharacterSize(24);
        healthText.setFillColor(sf::Color::Red);
        healthText.setPosition(10, 40);
    }

    ~Game() {
        delete menu;
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    void handleEvents() {
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
                }
                else if (state == GameState::Playing) {
                    for (auto it = boxes.begin(); it != boxes.end(); ) {
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

    void update() {
        if (state == GameState::Playing) {
            // Spawn box
            if (spawnClock.getElapsedTime().asSeconds() > 1.0f) {
                float x = static_cast<float>(std::rand() % (window.getSize().x - 40));
                boxes.emplace_back(x);
                spawnClock.restart();
            }

            // Update box positions
            for (auto it = boxes.begin(); it != boxes.end(); ) {
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

            // Update text
            scoreText.setString("Score: " + std::to_string(score));
            healthText.setString("Health: " + std::to_string(health));
        }
    }

    void render() {
        window.clear();

        if (state == GameState::Menu) {
            menu->draw(window);
        } else if (state == GameState::Playing) {
            sf::Sprite bg(bgTexture);
            bg.setScale(
                window.getSize().x / (float)bgTexture.getSize().x,
                window.getSize().y / (float)bgTexture.getSize().y
            );
            window.draw(bg);

            for (const auto& box : boxes)
                window.draw(box.shape);

            window.draw(scoreText);
            window.draw(healthText);
        }

        window.display();
    }
};
int main() {
    Game game;
    game.run();
    return 0;
}
