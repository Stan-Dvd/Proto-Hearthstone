//
// Created by StanD on 30/11/2025.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <deck.hpp>

class player {
private:
    int maxMana, curMana, health;
    bool active;
    std::vector<card> hand, board;
    deck p_deck;
public:
    player();
    ~player();

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size);

    void playCard(const unsigned int poz);

    void drawCard();

    void takeDMG(int dmg);

    void atkMinion(player &p2, const unsigned int atk_poz, const unsigned int targ_poz);

    void atkPlayer(player &p2, const unsigned int atk_poz);

    card& getMinion(const unsigned int poz);

    void checkBoard();

    void startTurn();

    void endTurn();

    friend std::ostream& operator<< (std::ostream &os, const player &p1);
};

#endif //PLAYER_HPP
