#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Text title, start, quit;
    sf::Sprite background;

public:
    Menu(sf::Font& font, sf::Texture& bgTexture, sf::Vector2u windowSize);
    void draw(sf::RenderWindow& window);
    bool isStartClicked(sf::Vector2f mousePos) const;
    bool isQuitClicked(sf::Vector2f mousePos) const;
};
