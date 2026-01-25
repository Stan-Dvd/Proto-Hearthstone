
#include "deck.hpp"

#include <algorithm>
#include <random>

#include "card_factory.hpp"

deck::deck() {
    cards.reserve(30);
//    player_id = id;
}

// deck::deck(deck &model) {
//     for (unsigned int i=0; i < model.getSize(); ++i) {
//         cards.push_back( model.cards[i] );
//     }
//     startPosX = model.startPosX;
//     startPosY = model.startPosY;
//     player_id = model.player_id;
// }

void deck::deck_init(const CardTypes * card_pool, const int *card_freq, const int pool_size) {
    int i=0;
    for (i=0; i<pool_size; ++i) {
        int k=0;
        while (k < card_freq[i]) {
            cards.push_back( CardFactory::Instance().create_card(card_pool[i]) );
            k++;
        }
    }
}

deck::~deck() {
    for (unsigned int i=0; i<cards.size(); ++i)
        delete cards[i];
    cards.clear();
}

//GET/SETTERS
unsigned int deck::getSize() {
    return cards.size();
}

// void deck::setCard(const int poz, card* card) {
//     cards[poz] = card->clone();
// }

//void deck::setStartPos(sf::RenderWindow& window) {
//    const sf::Vector2u size = window.getSize();
//    if (player_id == 1) {
//        startPosX = static_cast<float>(size.x) * 0.2f;
//        startPosY = static_cast<float>(size.y) * 0.85f;
//    }
//    else {
//        startPosX = static_cast<float>(size.x) * 0.8f;
//        startPosY = static_cast<float>(size.y) * 0.15f;
//    }
//}

card* deck::getCard() {
    //draw card from deck
    card* x = cards[cards.size() - 1]->clone();
    cards.pop_back();
    return x;
}

void deck::shuffle() {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine { rd() };
    std::ranges::shuffle(cards, rng);
}

//void deck::drawDeck(sf::RenderWindow& window){
//    if (player_id == 1) {
//        for (unsigned int i=0; i < cards.size(); ++i) {
//            cards[i]->draw(window, startPosX + static_cast<float>(i* SLOT_WIDTH), startPosY);
//        }
//    }
//    if (player_id == 2) {
//        for (unsigned int i=0; i < cards.size(); ++i) {
//            cards[i]->draw(window, startPosX - static_cast<float>(i* SLOT_WIDTH), startPosY);
//        }
//    }
//}

void deck::display() const{
    std::cout << cards.size() << " cards in deck \n";
    for (unsigned int i=0; i<cards.size(); ++i) {
        cards[i]->display();
        std::cout << " || ";
    }
}

//std::ostream& operator<< (std::ostream &os, const deck &deck) {
//    std::cout << deck.cards.size() << " cards\n";
//    for (unsigned   int i=0; i < deck.cards.size(); ++i) {
//        // os << deck.cards[i] << "||";
//    }
//    return os;
//}
