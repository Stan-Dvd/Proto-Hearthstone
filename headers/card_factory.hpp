#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include "cards_def.hpp"

enum CardTypes { Minion1, Minion2, Minion3, Fireball, PotOfGreed, MendWounds };

class CardFactory {
public:
    CardFactory() = default;
    ~CardFactory() = default;

    card* create_card(const CardTypes type) {
        switch (type) {
            case CardTypes::Minion1:
                return new minion(1, 2, 1);
            case CardTypes::Minion2:
                return new minion(2, 1, 4);
            case CardTypes::Minion3:
                return new minion(3, 4, 2);
            case CardTypes::Fireball:
                return new fireball();
            case CardTypes::MendWounds:
                return new mend_wounds();
            case CardTypes::PotOfGreed:
                return new pot_of_greed();
            default:
                return nullptr;
        }
    }
};

#endif //CARD_FACTORY_HPP
