#include <iostream>
#include <memory>
#include "headers/ResourceManager.hpp"
// #include "card.hpp"
// #include "minion.hpp"
// #include "deck.hpp"
// #include "player.hpp"
#include "cards_def.hpp"
#include "game.hpp"
#include "spell.hpp"




// class Game {
// private:
//     player p1, p2;
//     bool turn; // 0 for p1, 1 for p2
//
//     sf::RenderWindow window;
//     sf::Font font;
//     sf::Sprite background;
// };

int main() {

    card* card_pool[5] { new minion(3, 4, 2), new minion(2, 1, 4),
                        new minion(1, 2, 1), new fireball(), new pot_of_greed()};
    int const card_freq[5]{2, 2, 2, 2, 2};

    game master;
    master.init(card_pool, card_freq, 5, card_pool, card_freq, 5);
    // master.demo();
    master.run();

    for (int i=0; i < 3; ++i)
        delete card_pool[i];

    return 0;
}
