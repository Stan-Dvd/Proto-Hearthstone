#ifndef CARDS_DEF_HPP
#define CARDS_DEF_HPP

#include "spell.hpp"

class fireball : public spell {
public:
    fireball() : spell(1, "Fireball", "Deal 2 damage"){};
    void action(player *p, bool owner, sf::Vector2f) override;
    card* clone() override{ return new fireball(*this); }
};

#endif //CARDS_DEF_HPP
