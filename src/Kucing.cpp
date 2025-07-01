#include "Kucing.hpp"

Kucing::Kucing(float x, sf::Texture* texture) {
    sprite.setTexture(*texture);
    sprite.setScale(40.f / texture->getSize().x, 40.f / texture->getSize().y);
    sprite.setPosition(x, -40);
    speed = 2.0f + static_cast<float>(std::rand() % 4);
}

void Kucing::update() {
    sprite.move(0, speed);
}

bool Kucing::isOutOfScreen(float screenHeight) const {
    return sprite.getPosition().y > screenHeight;
}

bool Kucing::isClicked(sf::Vector2f mousePos) const {
    return sprite.getGlobalBounds().contains(mousePos);
}
