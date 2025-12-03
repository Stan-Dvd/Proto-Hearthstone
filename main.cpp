#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "headers/ResourceManager.hpp"
// #include "card.h"
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

    card c1(1, 3, 4);
    card const card_pool[3]{ card(3, 4, 2) , card(2, 1, 4), card(1, 2, 1)};
    int const card_freq[3]{3, 3, 3};

    game master;
    master.init(card_pool, card_freq, 3, card_pool, card_freq, 3);
    // master.demo();
    master.run();

    return 0;
}
