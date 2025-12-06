#include <iostream>
#include <memory>
#include "headers/ResourceManager.hpp"
// #include "card.hpp"
// #include "minion.hpp"
// #include "deck.hpp"
// #include "player.hpp"
#include "game.hpp"




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

    card* card_pool[3] { new minion(3, 4, 2), new minion(2, 1, 4), new minion(1, 2, 1)};
    int const card_freq[3]{3, 3, 3};

    game master;
    master.init(card_pool, card_freq, 3, card_pool, card_freq, 3);
    // master.demo();
    master.run();

    for (int i=0; i < 3; ++i)
        delete card_pool[i];

    return 0;
}
