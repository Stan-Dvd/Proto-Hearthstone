//
// Created by StanD on 03/12/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "minion.hpp"
#include "player.hpp"

class game{
private:
    player p[2];
    bool turn_id; // traks whose turn it is
    bool select_flag;
    card *selected_card;
    sf::Sprite Board, turn_button;
    sf::RectangleShape text_box;
    sf::Text message;
    sf::RenderWindow window;

public:
    game();
    void init(CardTypes *card_pool1, const int *card_freq1, const int pool_size1,
                CardTypes *card_pool2, const int *card_freq2, const int pool_size2);
    void display();
    void switchTurn();
    void selectCard(const auto mouse_pos);
    void handle_click(const auto mouse_pos);

    void run();
    void demo();
};

#endif //GAME_HPP
