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
    int turn_id, select_id;
    bool select_flag;
    card *selected_card;
    sf::Sprite Board, turn_button;
    sf::RectangleShape text_box;
    sf::Text text;
    sf::RenderWindow window;

public:
    game();
    void init(const card *card_pool1, const int *card_freq1, const int pool_size1,
                const card *card_pool2, const int *card_freq2, const int pool_size2);
    void display();
    void switchTurn();
    void selectCard(const auto mouse_pos);
    void handle_select(const auto mouse_pos);
    void handle_click(const auto mouse_pos);

    void run();
    void demo();
};

#endif //GAME_HPP
