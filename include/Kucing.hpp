#pragma once
#include <SFML/Graphics.hpp>

class Kucing {
public:
    sf::Sprite sprite;
    float speed;

    Kucing(float x, sf::Texture* texture);
    void update();
    bool isOutOfScreen(float screenHeight) const;
    bool isClicked(sf::Vector2f mousePos) const;
};
