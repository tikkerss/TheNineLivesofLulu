    #include "../include/Game_State.hpp"
    #include <iostream>
    #include <cstdlib>
    #include <ctime>

    Game::Game() 
    : window(sf::VideoMode(800, 600), "The Nine Lives of Lulu", sf::Style::Titlebar | sf::Style::Close),
    state(GameState::Menu) {
           

        window.setFramerateLimit(60);
        std::srand(static_cast<unsigned>(std::time(0)));

        tryAgainText.setFont(font);
        tryAgainText.setString("Try Again?");
        tryAgainText.setCharacterSize(20);
        tryAgainText.setFillColor(sf::Color::White);
        tryAgainText.setPosition(347, 252); 

        quitText.setFont(font);
        quitText.setString("Quit");
        quitText.setCharacterSize(25);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(370, 342); 

        if (!bgMenuTexture.loadFromFile("assets/bg_menu.jpg") ||
        !bgStoryTexture.loadFromFile("assets/bg_story.jpg") ||
        !bgIntroTexture.loadFromFile("assets/bg_intro.jpg") ||
        !bgGameTexture.loadFromFile("assets/bg_game.jpg") ||
        !bgWinTexture.loadFromFile("assets/bg_win.jpg") ||
        !bgLoseTexture.loadFromFile("assets/bg_lose.jpg") ||
        !font.loadFromFile("assets/Toasty Milk.ttf") ||
        !kucingTexture.loadFromFile("assets/kucing.png") ||
        !backgroundMusic.openFromFile("assets/music.ogg")) {
        std::cerr << "Failed to load one or more assets\n";
        std::exit(1);
    }

        backgroundMusic.setLoop(true);
        backgroundMusic.play();

        menu = new Menu(font, bgMenuTexture, window.getSize());
        story = new Story(window, font);  

        scoreText.setFont(font);
        scoreText.setCharacterSize(28);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(13, 30);


        healthText.setFont(font);
        healthText.setCharacterSize(15);
        healthText.setFillColor(sf::Color::Red);
        healthText.setPosition(10, 80);

        score = 0;
        health = 9;
    }

    Game::~Game() {
        delete menu;
        delete story;
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

                if (state == GameState::Win || state == GameState::Lose) {
                if (tryAgainText.getGlobalBounds().contains(mousePos)) {
        
                  score = 0;
                 health = 9;
                 cat.clear();
                  spawnClock.restart();
                state = GameState::Playing;
             }
}
                if (state == GameState::Win || state == GameState::Lose) {
                    if (quitText.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }

                if (state == GameState::Menu) {
                    if (menu->isStartClicked(mousePos)) {
                        state = GameState::Story;
                        story->setIntroTexture(bgIntroTexture); 
                        story->reset();                         
                    }
                    if (menu->isQuitClicked(mousePos)) {
                        window.close();
                    }
                } else if (state == GameState::Story) {
                story->handleClick(mousePos, window);
        
    }
    else if (state == GameState::Playing) {
        for (auto it = cat.begin(); it != cat.end();) {
            if (it->isClicked(mousePos)) {
                it = cat.erase(it);
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
        if (state == GameState::Story) {
            if (story->next()) {
                state = GameState::Playing;
            }
            return;
        }

        if (state == GameState::Playing) {
            if (spawnClock.getElapsedTime().asSeconds() > 1.0f) {
                float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
                cat.emplace_back(x, &kucingTexture);
                spawnClock.restart();
            }

            for (auto it = cat.begin(); it != cat.end();) {
                it->update();
                if (it->isOutOfScreen(window.getSize().y)) {
                    it = cat.erase(it);
                    health--;
                    if (health == 0) {
                        state = GameState::Lose;
                    }
                } else {
                    ++it;
                }
            }
            
            if (score >= 10) {
            state = GameState::Win;
            return;
        }

        if (health == 0) {
         state = GameState::Lose;
         return;
}

        scoreText.setString("Score: " + std::to_string(score));
        healthText.setString("Life Remaining: " + std::to_string(health));
        }
    }

    void Game::render() {
        window.clear();

        sf::Sprite bg;

        if (state == GameState::Menu) {
            bg.setTexture(bgMenuTexture);
            bg.setScale(
                window.getSize().x / (float)bgMenuTexture.getSize().x,
                window.getSize().y / (float)bgMenuTexture.getSize().y
            );
            window.draw(bg);
            menu->draw(window);
        }
        else if (state == GameState::Story) {
            bg.setTexture(bgStoryTexture);
            bg.setScale(
                window.getSize().x / (float)bgStoryTexture.getSize().x,
                window.getSize().y / (float)bgStoryTexture.getSize().y
            );
            window.draw(bg);
            story->draw();
        }
        else if (state == GameState::Playing) {
            bg.setTexture(bgGameTexture);
            bg.setScale(
                window.getSize().x / (float)bgGameTexture.getSize().x,
                window.getSize().y / (float)bgGameTexture.getSize().y
            );
            window.draw(bg);

            for (const auto& cat : cat)
                window.draw(cat.sprite);

            window.draw(scoreText);
            window.draw(healthText);
        }else if (state == GameState::Win) {
            bg.setTexture(bgWinTexture);
             bg.setScale(
            window.getSize().x / (float)bgWinTexture.getSize().x,
           window.getSize().y / (float)bgWinTexture.getSize().y
            );
            window.draw(bg);
            window.draw(tryAgainText);
                window.draw(quitText);

        }else if (state == GameState::Lose) {
        bg.setTexture(bgLoseTexture);
        bg.setScale(
        window.getSize().x / (float)bgLoseTexture.getSize().x,
        window.getSize().y / (float)bgLoseTexture.getSize().y
        );
        window.draw(bg);
        window.draw(tryAgainText);
        window.draw(quitText);
        }


        window.display();
}

