#include "../include/Kucing.hpp"

Kucing::Kucing(float x, sf::Texture* texture) {
    sprite.setTexture(*texture);
    sprite.setPosition(x, -60);
    speed = 3.0f + static_cast<float>(std::rand() % 4);
     sprite.setScale(0.3f, 0.3f);
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
