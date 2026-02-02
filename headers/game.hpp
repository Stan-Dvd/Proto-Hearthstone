//
// Created by StanD on 03/12/2025.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "minion.hpp"
#include "playerBuilder.hpp"
#include "player.hpp"

class game : public Singleton<game>{
    friend class Singleton<game>;
private:
    player p[2];
    bool turn_id; // traks whose turn it is
    bool select_flag;
    card *selected_card;
    sf::Sprite Board, turn_button;
    sf::RectangleShape text_box;
    sf::Text message;
    sf::RenderWindow window;

    game();
public:
    void init(playerBuilder* p1Builder, playerBuilder* p2Builder);
    void display();
    void switchTurn();
    void selectCard(const auto mouse_pos);
    void handle_click(const auto mouse_pos);

    void run();
    void demo();
};

#endif //GAME_HPP
