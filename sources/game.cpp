
#include "game.hpp"


game::game() :
    p1(1), p2(2), card_clicked(false),
    Board(ResourceManager::Instance().getTexture(BOARD_TEXTURE)),
    turn_button(ResourceManager::Instance().getTexture(TURN_P1_T))
{
    window.create(sf::VideoMode({1920, 1200}), "Proto-Hearthstone", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    //set board sprite scale
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = Board.getTexture().getSize();
    const float scale_x = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
    const float scale_y = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);
    Board.scale({scale_x, scale_y});

    p1.setStartPos(window);
    p2.setStartPos(window);
}

void game::init(const card *card_pool1, const int *card_freq1, const int pool_size1,
                const card *card_pool2, const int *card_freq2, const int pool_size2) {
    p1.deck_init(card_pool1, card_freq1, pool_size1);
    p2.deck_init(card_pool2, card_freq2, pool_size2);
}

void game::run() {
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
        p1.drawPlayer(window);
        p2.drawPlayer(window);

        window.display();
    }
}

void game::demo() {
    for (int i=0; i < 3; ++i) {
        p1.drawFromDeck();
        p2.drawFromDeck();
    }
        p1.startTurn();
        p1.playCard(0);
        p1.endTurn();

        p2.startTurn();
        p2.playCard(0);
        p2.endTurn();

        p1.startTurn();
        p1.atkPlayer(p2, 0);
        p1.playCard(0);
        p1.playCard(1);
        p1.endTurn();
        p1.startTurn();
        p1.playCard(0);
        p1.playCard(0);
        p1.playCard(0);
        p1.endTurn();
        p1.startTurn();
        p1.playCard(0);
        p1.playCard(0);
        p1.endTurn();
        p1.startTurn();
        p1.playCard(0);
        p1.endTurn();
        p1.startTurn();
        p1.playCard(0);


        std::cout << p1 << '\n';
    }


