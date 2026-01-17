#ifndef CARDS_DEF_HPP
#define CARDS_DEF_HPP

#include "spell.hpp"
#include "minion.hpp"

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
    card* clone() override { return new mend_wounds(*this); }
};

class hunters_gift : public spell {
public:
    hunters_gift() : spell(2, "Hunter's Gift", "Give minion \n+1dmg"){}
    void action(player *p, bool owner, sf::Vector2f mouse_pos) override;
    card* clone() override { return new hunters_gift(*this); }
};

class eldritch_blast : public spell {
public:
    eldritch_blast() : spell(2, "Eldritch Blast", "Deal 3 damage"){}
    void action(player *p, bool owner, sf::Vector2f mouse_pos) override;
    card *clone() override { return new eldritch_blast(*this); }
};

#endif //CARDS_DEF_HPP
