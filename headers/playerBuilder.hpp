#ifndef PLAYERBUILDER_HPP
#define PLAYERBUILDER_HPP

#include "player.hpp"

class playerBuilder {
protected:
  player * p;
protected:
    virtual void buildSignature() = 0;
    virtual void buildDeck() = 0;
public:
    playerBuilder(const int id) : p(new player(id)){}
    virtual ~playerBuilder() {
        delete p;
    }
    virtual void buildPlayer() = 0;

    player * getPlayer() const{
        return p;
    }
};

class warlockBuilder : public playerBuilder {
private:
    void buildSignature() override {
        p->setSignature(Eldritch_Blast);
    }
    void buildDeck() override {
        //doesn't have mend_wounds, has more fireball
        //has fewer small minions, for low-cost he has spells
        const CardTypes card_pool[5] {Minion3, Minion2, Minion1,
                                    Fireball, PotOfGreed};
        const int card_freq[5]{5, 3, 3, 3, 2};
        p->setDeck(card_pool, card_freq, 5);
    }

public:
    warlockBuilder(const int id) : playerBuilder(id) {}
    void buildPlayer() override {
        buildSignature();
        buildDeck();
    }
};

class hunterBuilder : public playerBuilder {
private:
    void buildSignature() override {
        p->setSignature(Hunters_Gift);
    }
    void buildDeck() override {
        //doesn't have fireball, has more potOfGreed and small minions he can buff
        const CardTypes card_pool[5] {Minion3, Minion2, Minion1,
                                        PotOfGreed, MendWounds};
        const int card_freq[5]{3, 4, 4, 3, 3};
        p->setDeck(card_pool, card_freq, 5);
    }

public:
    hunterBuilder(const int id) : playerBuilder(id) {}
    void buildPlayer() override {
        buildSignature();
        buildDeck();
    }
};

#endif //PLAYERBUILDER_HPP
