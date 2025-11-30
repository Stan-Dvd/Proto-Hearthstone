#ifndef DECK_HPP
#define DECK_HPP
#include <vector>
#include "card.h"

class deck {
private:
    std::vector<card> cards;
    float startPosX, startPosY;
    bool player_id;

public:

    // CONSTRUCTORS
    deck();

    deck(deck &model);

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size);

    ~deck();

    //GET/SETTERS
    unsigned int getSize();
    void setCard(const int poz, const card& card);
    void setStartPos(const float posX, const float posY);

    card getCard();
    void shuffle();

    // void drawDeck(sf::RenderWindow window);

    friend std::ostream& operator<< (std::ostream &os, const deck &deck);

};

#endif //DECK_HPP
