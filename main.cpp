#include <iostream>
#include "headers/ResourceManager.hpp"
#include "game.hpp"

int main() {
    playerBuilder *p1Builder = new hunterBuilder();
     playerBuilder *p2Builder = new warlockBuilder();
    //builders handle player setup, depending on class

    game::Instance().init(p1Builder, p2Builder);
    game::Instance().run();

    delete p1Builder;
    delete p2Builder;

    return 0;
}
