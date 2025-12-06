#ifndef CARDS_DEF_HPP
#define CARDS_DEF_HPP

#include "spell.hpp"

class fireball : public spell {
public:
    fireball() : spell(1, "Fireball", "Deal 2 damage"){};
    void action(player *p, bool owner, sf::Vector2f) override;
    card* clone() override{ return new fireball(*this); }
};

class pot_of_greed : public spell {
public:
    pot_of_greed() : spell(2, "Pot of greed", "Draw 3 cards"){};
    void action(player *p, bool owner, sf::Vector2f) override;
    card* clone() override{ return new pot_of_greed(*this); }
};

class mend_wounds : public spell {
public:
    mend_wounds() : spell(2, "Mend Wounds", "Heal 3 hp"){};
    void action(player *p, bool owner, sf::Vector2f mouse_pos) override;
    card* clone() override { return new mend_wounds(*this); };
};

#endif //CARDS_DEF_HPP
