#include "cards_def.hpp"
#include "exceptions.hpp"
#include "player.hpp"

void fireball::action(player *p, const bool owner, const sf::Vector2f mouse_pos) {
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
    throw target_exception("enemy");
}

void pot_of_greed::action(player *p, const bool owner, const sf::Vector2f mouse_pos) {
    // check if friendly board is clicked
    if (p[owner].getBoardBounds().contains(mouse_pos)) {
        p[owner].payCost(this->getCost());
        for (int i=0; i<3; i++)
            p[owner].drawFromDeck();
        p[owner].remove_fromHand(this);
    }
    throw target_exception("friendly board");

}

void mend_wounds::action(player *p, bool owner, sf::Vector2f mouse_pos) {

    if (p[owner].selectPlayer(mouse_pos)) {
        p[owner].payCost(this->getCost()); //can throw mana exception

        p[owner].heal(MEND_WOUNDS_HEAL);
        p[owner].remove_fromHand(this);
        return;
    }
    //check if minion is target
    minion* target = p[owner].selectBoard(mouse_pos);
    if ( target != nullptr ) {
        p[owner].payCost(this->getCost()); //can throw mana exception

        target->heal(MEND_WOUNDS_HEAL);
        p[owner].remove_fromHand(this);
        return;
    }
    throw target_exception("friendly");
}

