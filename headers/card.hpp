#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "ResourceManager.hpp"

class card {
private:
    int cost, power, health;
    bool attackFlag; // tracks if card has attacked this turn
    bool selectFLag; //tracks if card is selected
    bool deployFlag; //tracks if card is on the board or in hand
    sf::Sprite card_sprite;
    sf::Text hp_txt, pow_txt, cost_txt;

public:

    // CONSTRUCTORS
    card(int cost, int pow, int hp, std::string texture = PLACEHOLDER_MINION_TEXTURE);
    card (const card &model);// COPY constructor
    ~card();

    // GET/SETTERS

    int getCost();
    int getPower();
    int getHealth();
    sf::FloatRect getGlobalBounds();
    bool check_atkFlag();
    bool check_deployFlag();
    bool check_selectFlag();
    void set_atkFlag(const bool val);
    void set_selectFlag(const bool val);
    void set_deployFlag(const bool val);


    void attack(card *target);
    int is_playable(int mana);

    void draw(sf::RenderWindow &window, const float x, const float y);
    void setScale(const float x, const float y);

    // card operator=(const card &model);
    friend std::ostream& operator<< (std::ostream &os, const card &card);
};

#endif //CARD_H
