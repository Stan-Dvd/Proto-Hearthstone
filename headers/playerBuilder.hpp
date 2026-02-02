#ifndef PLAYERBUILDER_HPP
#define PLAYERBUILDER_HPP

#include "player.hpp"

//builders set the cards from the players deck and the signature spell
//depending on the player class

class playerBuilder {
protected:
    player *p;

protected:
    virtual void buildSignature() = 0;
    virtual void buildDeck() = 0;

public:
    explicit playerBuilder() : p(nullptr) {}
    explicit playerBuilder(const playerBuilder &pb) = delete;
    playerBuilder *operator=(const playerBuilder &pb) = delete;
    virtual ~playerBuilder() = default;

    virtual void buildPlayer(const int id) = 0;
    void reset() {
        p = nullptr;
    }
    [[nodiscard]] player *getPlayer() {
        //once passed to the caller, the pointer in builder is set to null
        player *result = p;
        reset();
        return result;
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
        const CardTypes card_pool[5]{
            Minion3, Minion2, Minion1,
            Fireball, PotOfGreed
        };
        const int card_freq[5]{5, 3, 3, 3, 2};
        p->setDeck(card_pool, card_freq, 5);
    }

public:
    void buildPlayer(const int id) override {
        p = new player(id);
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
        const CardTypes card_pool[5]{
            Minion3, Minion2, Minion1,
            PotOfGreed, MendWounds
        };
        const int card_freq[5]{3, 4, 4, 3, 3};
        p->setDeck(card_pool, card_freq, 5);
    }

public:
    void buildPlayer(const int id) override {
        p = new player(id);
        buildSignature();
        buildDeck();
    }
};

#endif //PLAYERBUILDER_HPP
