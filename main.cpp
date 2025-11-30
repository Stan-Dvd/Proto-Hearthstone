#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "headers/ResourceManager.hpp"
#include "card.h"
#include "deck.hpp"
#include "player.hpp"


// class Game {
// private:
//     player p1, p2;
//     bool turn; // 0 for p1, 1 for p2
//
//     sf::RenderWindow window;
//     sf::Font font;
//     sf::Sprite background;
// };

int main() {

    // card c1(1, 3, 4);
    // card const card_pool[3]{ card(3, 4, 2) , card(2, 1, 4), card(1, 2, 1)};
    // int const card_freq[3]{3, 3, 3};
    // player p1, p2;
    //
    // // deck shuffle test
    // deck test_deck;
    // test_deck.deck_init(card_pool, card_freq, 3);
    // test_deck.shuffle();
    // std::cout << test_deck << '\n' << '\n';
    //
    // p1.deck_init(card_pool, card_freq, 3);
    // p2.deck_init(card_pool, card_freq, 3);

    card c1(1, 3, 3);


    sf::RenderWindow window;

    window.create(sf::VideoMode({1920, 1200}), "Proto-Hearthstone", sf::State::Fullscreen);
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    std::cout << "Fereastra a fost creată\n";
    window.setFramerateLimit(60);

    sf::Texture board_texture;
    try {
        board_texture = ResourceManager::Instance().getTexture("board_texture.png");
        // dummyTexture = ResourceManager::Instance().getTexture("fizzbuzz.png"); // @
    } catch(std::exception& exp) {
        std::cout << exp.what() << std::endl;
        return 0;
    }

    sf::Sprite Board(board_texture);

    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = board_texture.getSize();

    const float scale_x = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
    const float scale_y = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);

    Board.scale({scale_x, scale_y});
    sf::FloatRect boardBounds = Board.getGlobalBounds();

    while(window.isOpen()) {
        bool shouldExit = false;

        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }
        }

        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        window.clear();

        window.draw(Board);
        const float x = boardBounds.position.x + boardBounds.size.x * 0.3f;
        const float y = boardBounds.position.y + boardBounds.size.y - boardBounds.size.y*0.3f;
        c1.setScale(scale_x, scale_y);
        c1.draw(window, x, y);

        window.display();
    }

    return 0;
}
