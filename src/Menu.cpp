#include "Menu.hpp"

Menu::Menu(sf::Font& font, sf::Texture& bgTexture, sf::Vector2u windowSize) {
    background.setTexture(bgTexture);
    background.setScale(
        windowSize.x / (float)bgTexture.getSize().x,
        windowSize.y / (float)bgTexture.getSize().y
    );

    title.setFont(font);
    title.setString("The Nine Lives of Lulu");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Black);
    title.setPosition(150, 50);

    start.setFont(font);
    start.setString("Start");
    start.setCharacterSize(36);
    start.setFillColor(sf::Color::Black);
    start.setPosition(350, 200);

    quit.setFont(font);
    quit.setString("Quit");
    quit.setCharacterSize(36);
    quit.setFillColor(sf::Color::Black);
    quit.setPosition(350, 300);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);
    window.draw(start);
    window.draw(quit);
}

bool Menu::isStartClicked(sf::Vector2f mousePos) const {
    return start.getGlobalBounds().contains(mousePos);
}

bool Menu::isQuitClicked(sf::Vector2f mousePos) const {
    return quit.getGlobalBounds().contains(mousePos);
}
