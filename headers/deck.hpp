#ifndef DECK_HPP
#define DECK_HPP
#include <vector>
#include "card.hpp"

class deck {
private:
    std::vector<card> cards;
    float startPosX, startPosY;
    int player_id;

public:

    // CONSTRUCTORS
    deck(int id);

    deck(deck &model);

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size);

    ~deck();

    //GET/SETTERS
    unsigned int getSize();
    void setCard(const int poz, const card& card);
    void setStartPos(sf::RenderWindow window);

    card getCard();
    void shuffle();

    void drawDeck(sf::RenderWindow window);

    friend std::ostream& operator<< (std::ostream &os, const deck &deck);

};

#endif //DECK_HPP
