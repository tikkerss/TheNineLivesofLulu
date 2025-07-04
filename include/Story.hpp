#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class StoryState {
    Dialog,
    Choice,
    IntroAfterChoice,
    Done
};

class Story {
private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::vector<std::string> dialog;
    std::size_t currentLine;


    sf::Text text;
    sf::Text hintText;

    // Untuk pilihan
    StoryState state;
    bool bantuAndi;

    sf::Text questionText;
    sf::RectangleShape yaButton;
    sf::RectangleShape tidakButton;
    sf::Text yaText;
    sf::Text tidakText;
    sf::Texture introTexture;

public:
    Story(sf::RenderWindow& win, sf::Font& f);
    
    void loadDialog();
    void draw();
    bool next(); // lanjut dialog
    void handleClick(sf::Vector2f pos, sf::RenderWindow& window);
    void reset();

    bool isFinished() const; // cek apakah dialog + pilihan sudah selesai
    bool isBantuAndi() const; // hasil pilihan YA/TIDAK
    void setIntroTexture(sf::Texture& tex);

};
