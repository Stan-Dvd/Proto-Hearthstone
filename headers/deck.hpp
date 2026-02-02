#ifndef DECK_HPP
#define DECK_HPP
#include <random>
#include <vector>

#include "card.hpp"
#include "card_factory.hpp"

class deck {
private:
    std::vector<card*> cards;

public:

    // CONSTRUCTORS
    deck();
    ~deck();
    // deck(deck &model);


    //GET/SETTERS
    unsigned int getSize();
    void deck_init(const CardTypes * card_pool, const int *card_freq, const int pool_size);
    // void setCard(const int poz, card* card);
    // void setStartPos(sf::RenderWindow& window);

    card* getCard();
    void shuffle();

    // void drawDeck(sf::RenderWindow& window);
//    friend std::ostream& operator<< (std::ostream &os, const deck &deck);
    void display() const;
};

#endif //DECK_HPP
