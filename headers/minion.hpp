#ifndef MINION_HPP
#define MINION_HPP
#include <iostream>
#include "card.hpp"
#include "ResourceManager.hpp"

class player;
//why does this work what kind of forbidden black magic is this

class minion : public card{
private:
    int power, health;
    bool attackFlag; // tracks if card has attacked this turn
    bool deployFlag; //tracks if card is on the board or in hand
    sf::Text hp_txt, pow_txt;

public:

    // CONSTRUCTORS
    minion(int cost, int pow, int hp, std::string texture = PLACEHOLDER_MINION_TEXTURE);
    minion (const minion &model);// COPY constructor
    ~minion() override;

    // GET
    int getPower();
    int getHealth();
    bool check_atkFlag();
    bool check_deployFlag();

    //SETTERS / changers
    void set_atkFlag(const bool val);
    void set_deployFlag(const bool val);
    void buff(const bool val);
    void heal(const bool val);
    void takeDMG(const bool val);

    // GAME functions
    void action(player *p, bool owner, sf::Vector2f mouse_pos) override; //owner will be taken from turn_id
    void attack(minion *target);

    void draw_details(sf::RenderWindow &window) override;
    void setDetailscale(const float x, const float y) override;

    // card operator=(const card &model);
    // friend std::ostream& operator<< (std::ostream &os, const card &card);
    void displayDetails() override;

    card* clone() override;
};

#endif //MINION_HPP
