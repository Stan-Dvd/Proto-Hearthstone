//
// Created by StanD on 03/12/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"

class game{
private:
    player p1, p2;
    bool card_clicked;
    sf::Sprite Board, turn_button;
    sf::RenderWindow window;

public:
    game();
    void init(const card *card_pool1, const int *card_freq1, const int pool_size1,
                const card *card_pool2, const int *card_freq2, const int pool_size2);
    void run();
    void demo();
};

#endif //GAME_HPP
