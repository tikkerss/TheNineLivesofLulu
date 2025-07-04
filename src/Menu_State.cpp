#include "../include/Menu_State.hpp"

Menu::Menu(sf::Font& font, sf::Texture& bgTexture, sf::Vector2u windowSize) {
    background.setTexture(bgTexture);
    background.setScale(
        windowSize.x / (float)bgTexture.getSize().x,
        windowSize.y / (float)bgTexture.getSize().y
    );

  
    start.setFont(font);
    start.setString("Start");
    start.setCharacterSize(36);
    start.setFillColor(sf::Color::White);
    start.setPosition(575, 375);

    quit.setFont(font);
    quit.setString("Quit");
    quit.setCharacterSize(36);
    quit.setFillColor(sf::Color::White);
    quit.setPosition(590, 475);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(start);
    window.draw(quit);
}

bool Menu::isStartClicked(sf::Vector2f mousePos) const {
    return start.getGlobalBounds().contains(mousePos);
}

bool Menu::isQuitClicked(sf::Vector2f mousePos) const {
    return quit.getGlobalBounds().contains(mousePos);
}
