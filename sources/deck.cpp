
#include "deck.hpp"

#include <algorithm>
#include <random>

#include "player.hpp"

deck::deck(int id) {
    cards.reserve(30);
    player_id = id;
    startPosX = 0;
    startPosY = 0;
}

deck::deck(deck &model) {
    for (unsigned int i=0; i < model.getSize(); ++i) {
        cards.push_back( model.cards[i] );
    }
    startPosX = model.startPosX;
    startPosY = model.startPosY;
    player_id = model.player_id;
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
    if (player_id == 1) {
        for (unsigned int i=0; i < cards.size(); ++i) {
            cards[i].draw(window, startPosX + static_cast<float>(i* SLOT_WIDTH), startPosY);
        }
    }
    if (player_id == 2) {
        for (unsigned int i=0; i < cards.size(); ++i) {
            cards[i].draw(window, startPosX - static_cast<float>(i* SLOT_WIDTH), startPosY);
        }
    }
}

void deck::setStartPos(sf::RenderWindow window) {
    sf::Vector2u size = window.getSize();
    if (player_id == 1) {
        startPosX = static_cast<float>(size.x) * 0.2f;
        startPosY = static_cast<float>(size.y) * 0.85f;
    }
    else {
        startPosX = static_cast<float>(size.x) * 0.8f;
        startPosY = static_cast<float>(size.y) * 0.15f;
    }
}


std::ostream& operator<< (std::ostream &os, const deck &deck) {
    std::cout << deck.cards.size() << " cards\n";
    for (unsigned   int i=0; i < deck.cards.size(); ++i) {
        os << deck.cards[i] << "||";
    }
    return os;
}
