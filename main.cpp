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

    playerBuilder *p1Builder, *p2Builder;

    p1Builder = new hunterBuilder(1);
    p2Builder = new warlockBuilder(2);

    game::Instance().init(p1Builder, p2Builder);
    game::Instance().run();

    return 0;
}
