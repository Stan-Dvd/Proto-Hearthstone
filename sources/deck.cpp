
#include "deck.hpp"

#include <algorithm>
#include <random>

deck::deck() {
        cards.reserve(30);
    }

    deck::deck(deck &model) {
        for (unsigned int i=0; i < model.getSize(); ++i) {
            cards.push_back( model.cards[i] );
        }
    }

    void deck::deck_init( const card *card_pool, const int *card_freq, const int pool_size) {
        int i=0;
        for (i=0; i<pool_size; ++i) {
            int k=0;
            while (k < card_freq[i]) {
                cards.push_back( card_pool[i] );
                k++;
            }
        }
    }

    deck::~deck() {
        cards.clear();
    }

    //GET/SETTERS
    unsigned int deck::getSize() {
        return cards.size();
    }
    void deck::setCard(const int poz, const card& card) {
        cards[poz] = card;
    }

    void deck::setStartPos(const float posX, const float posY) {
        startPosX = posX;
        startPosY = posY;
    }

    card deck::getCard() {
        //draw card from deck
        card x = cards[cards.size() - 1];
        cards.pop_back();
        return x;

    }

    void deck::shuffle() {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(cards), std::end(cards), rng);
    }

    void deck::drawDeck(sf::RenderWindow window) {

    }


    std::ostream& operator<< (std::ostream &os, const deck &deck) {
        std::cout << deck.cards.size() << " cards\n";
        for (unsigned   int i=0; i < deck.cards.size(); ++i) {
            os << deck.cards[i] << "||";
        }
        return os;
    }
