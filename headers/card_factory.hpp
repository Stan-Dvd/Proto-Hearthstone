#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include "cards_def.hpp"

enum CardTypes { Minion1, Minion2, Minion3,
                Fireball, PotOfGreed, MendWounds,
                Hunters_Gift, Eldritch_Blast};

class CardFactory :public Singleton<CardFactory> {
    friend class Singleton<CardFactory>;
private:
    CardFactory() = default;
    ~CardFactory() = default;
public:
    static card* create_card(const CardTypes type) {
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
            case CardTypes::Hunters_Gift:
                return new hunters_gift();
            case CardTypes::Eldritch_Blast:
                return new eldritch_blast();
            default:
                return nullptr;
        }
    }
};

#endif //CARD_FACTORY_HPP
