#include "cards_def.hpp"
#include "exceptions.hpp"
#include "player.hpp"

void fireball::action(player *p, bool owner, sf::Vector2f mouse_pos) {
    //check if player is target
    if (p[!owner].selectPlayer(mouse_pos)) {
        p[owner].payCost(this->getCost()); //can throw mana exception

        p[!owner].takeDMG(FIREBALL_DMG);
        p[owner].remove_fromHand(this);
        return;
    }
    //check if minion is target
    minion* target = p[!owner].selectBoard(mouse_pos);
    if ( target != nullptr ) {
        p[owner].payCost(this->getCost()); //can throw mana exception

        target->takeDMG(FIREBALL_DMG);
        p[!owner].checkBoard();
        p[owner].remove_fromHand(this);
        return;
    }
    throw noTarget_exception("enemy");
}