//
// Created by StanD on 05/12/2025.
//

#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <exception>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "exceptions.hpp"
#include "ResourceManager.hpp"

class player;
//why does this work what kind of forbidden black magic is this

class card {
private:
    int cost;
    bool selectFlag;
    sf::Text cost_txt;

protected:
    sf::Sprite card_sprite; // need to draw details in child class
    sf::Text flavor_txt; // need to redefine for every child

public:

    // CONSTRUCTORS
    card(const int cost, std::string texture = PLACEHOLDER_MINION_TEXTURE);
    card (const card &model);// COPY constructor
    virtual ~card();

    // GET/SETTERS

    int getCost();
    bool check_selectFlag();
    sf::FloatRect getGlobalBounds();
    void set_selectFlag(const bool val);

    // GAME functions

    virtual void action(player *p, bool owner, sf::Vector2f mouse_pos) = 0; //owner will be taken from turn_id
    int is_playable(int mana);

    void draw(sf::RenderWindow &window, float x, float y);
    virtual void draw_details(sf::RenderWindow& window) = 0;

    void setScale(const float x, const float y);
    virtual void setDetailscale(const float x, const float y) = 0;

    // card operator=(const card &model);
    // friend std::ostream& operator<< (std::ostream &os, const card &card);
    void display(const bool &endl = false);
    virtual void displayDetails() = 0;

    virtual card* clone() = 0;
};


#endif //CARD_HPP
