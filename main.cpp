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
     p1Builder = new hunterBuilder();
     p2Builder = new warlockBuilder();
    //builders handle player setup, depending on class

    game::Instance().init(p1Builder, p2Builder);
    game::Instance().run();

    delete p1Builder;
    delete p2Builder;


    return 0;
}
