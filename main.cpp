#include <iostream>
#include <memory>
#include "headers/ResourceManager.hpp"
// #include "card.hpp"
// #include "minion.hpp"
// #include "deck.hpp"
// #include "player.hpp"
#include "cards_def.hpp"
#include "card_factory.hpp"
#include "game.hpp"
#include "spell.hpp"

int main() {

    // card* card_pool[6] { new minion(3, 4, 2), new minion(2, 1, 4),
    //                     new minion(1, 2, 1), new fireball(), new pot_of_greed(), new mend_wounds()};
    CardTypes card_pool[6] {CardTypes::Minion3, CardTypes::Minion2, CardTypes::Minion1,
                            CardTypes::Fireball, CardTypes::PotOfGreed, CardTypes::MendWounds};

    int const card_freq[6]{3, 3, 3, 2, 2, 2};

    game master;
    master.init(card_pool, card_freq, 6, card_pool, card_freq, 6);
    // master.demo();
    master.run();

    return 0;
}
