#include "../include/Story.hpp"
#include <sstream>
#include <SFML/Window.hpp>

std::string wrapText(const std::string& input, sf::Font& font, unsigned int charSize, float maxWidth) {
    std::string result;
    std::string word;
    std::istringstream stream(input);
    sf::Text testText;
    testText.setFont(font);
    testText.setCharacterSize(charSize);

    while (stream >> word) {
        std::string nextWord = word + " ";
        testText.setString(result + nextWord);

        float width = testText.getLocalBounds().width;
        if (width > maxWidth) {
            result += "\n" + nextWord;
        } else {
            result += nextWord;
        }
    }

    return result;
}

Story::Story(sf::RenderWindow& win, sf::Font& f)
    : window(win), font(f), currentLine(0), state(StoryState::Dialog), bantuAndi(false) {
    
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    hintText.setFont(font);
    hintText.setCharacterSize(18);
    hintText.setFillColor(sf::Color::White);
    hintText.setString(">> Tekan ENTER untuk melanjutkan");

    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setString("Bantu Andi?");
    questionText.setPosition(100, window.getSize().y - 150);

    yaButton.setSize({100, 40});
    yaButton.setFillColor(sf::Color::White);
    yaButton.setPosition(100, window.getSize().y - 90);

    tidakButton.setSize({100, 40});
    tidakButton.setFillColor(sf::Color::White);
    tidakButton.setPosition(250, window.getSize().y - 90);

    yaText.setFont(font);
    yaText.setString("YA");
    yaText.setCharacterSize(20);
    yaText.setFillColor(sf::Color::Black);

    tidakText.setFont(font);
    tidakText.setString("TIDAK");
    tidakText.setCharacterSize(20);
    tidakText.setFillColor(sf::Color::Black);

    loadDialog();
}

void Story::setIntroTexture(sf::Texture& tex) {
    introTexture = tex;
}

void Story::loadDialog() {
    dialog = {
        "//SREKKK... SREKKK...",
        "??? : Haahhh... Oh... Halo disana!",
        "Siapa kamu?",
        "Andi : Oh maaf, aku Andi.",
        "Suara apa itu tadi? dan kenapa kamu terlihat capek?",
        "Andi : Oh aku sedang mencari Lulu, kucing kesayanganku.",
        "Ohh, apakah dia menghilang?",
        "Andi : Tidak, dia pasti sedang bermain diatas pohon, itu tempat favoritnya sejak kecil. Nakal, bukan?",
        "Andi : Ini saatnya Lulu untuk makan, dia pasti akan melompat secara tiba-tiba dari atas pohon.",
        "Andi : Apakah kamu mau membantuku menangkapnya?",
        "Andi : Dia suka sekali melompat dari atas pohon secara tiba-tiba, aku rasa kamu harus memiliki refleks yang cepat untuk menangkapnya.",
    };
}

void Story::draw() {
    float margin = 30.f;

    if (state == StoryState::Dialog && currentLine < dialog.size()) {
        float maxTextWidth = window.getSize().x - 2 * margin;
        std::string wrapped = wrapText(dialog[currentLine], font, text.getCharacterSize(), maxTextWidth);

        text.setString(wrapped);
        text.setPosition(margin, window.getSize().y - 150);

        sf::FloatRect hintBounds = hintText.getLocalBounds();
        hintText.setPosition(
            window.getSize().x - hintBounds.width - 20,
            window.getSize().y - hintBounds.height - 20
        );

        window.draw(text);
        window.draw(hintText);
    }

    else if (state == StoryState::Choice) {
        window.draw(questionText);

        yaText.setPosition(
            yaButton.getPosition().x + 25,
            yaButton.getPosition().y + 8
        );
        tidakText.setPosition(
            tidakButton.getPosition().x + 10,
            tidakButton.getPosition().y + 8
        );

        window.draw(yaButton);
        window.draw(tidakButton);
        window.draw(yaText);
        window.draw(tidakText);
    }

    else if (state == StoryState::IntroAfterChoice) {
        sf::Sprite introSprite;
        introSprite.setTexture(introTexture);
        introSprite.setScale(
            window.getSize().x / (float)introTexture.getSize().x,
            window.getSize().y / (float)introTexture.getSize().y
        );
        window.draw(introSprite);

        sf::Text prompt;
        prompt.setFont(font);
        prompt.setString(">> Tekan ENTER untuk mulai permainan");
        prompt.setCharacterSize(20);
        prompt.setFillColor(sf::Color::White);
        prompt.setPosition(350, window.getSize().y - 90);
        window.draw(prompt);
    }

    window.display();
}

bool Story::next() {
    if (state == StoryState::Dialog &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) )) {
        currentLine++;
        sf::sleep(sf::milliseconds(200));

        if (currentLine >= dialog.size()) {
            state = StoryState::Choice;
        }
    }
    else if (state == StoryState::IntroAfterChoice &&
             sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        state = StoryState::Done;
        sf::sleep(sf::milliseconds(200));
    }

    return state == StoryState::Done;
}

void Story::handleClick(sf::Vector2f pos, sf::RenderWindow& window) {
    if (state == StoryState::Choice) {
        if (yaButton.getGlobalBounds().contains(pos)) {
            bantuAndi = true;
            state = StoryState::IntroAfterChoice;  
        } else if (tidakButton.getGlobalBounds().contains(pos)) {
            bantuAndi = false;
            window.close(); 
        }
    }
}

void Story::reset() {
    currentLine = 0;
    state = StoryState::Dialog;
    bantuAndi = false;
}

bool Story::isFinished() const {
    return state == StoryState::Done;
}

bool Story::isBantuAndi() const {
    return bantuAndi;
}
