
#include "player.hpp"


    player::player() {
        health = 10;
        maxMana = 1;
        curMana = 1;
        active = false;
        hand.reserve(10); // max hand size is 10
        board.reserve(7); //max minions on board is 7
    }
    player::~player() = default;

    void player::deck_init( const card *card_pool, const int *card_freq, const int pool_size) {
        p_deck.deck_init(card_pool, card_freq, pool_size);
        // nu imi place asta
    }

    void player::playCard(const unsigned int poz) {
        if (!active) {
            std::cout << "player inactive!\n";
            return;
            // va fi folosit pt butoane probabil
        }
        if (poz > hand.size()-1) {
            // teoretic n-ar trb sa se intample la butoane
            std::cout << "card beyond hand!\n";
            return;
        }
        if (board.size() >= 7) {
            std::cout << "board is full\n";
            return;
        }
        if (hand[poz].is_playable(curMana)) { // check if player has enough mana
            board.push_back(hand[poz]); //place card on board
            curMana = curMana - hand[poz].getCost(); // pay mana cost
            hand.erase(hand.begin() + poz); // erase card from hand
            std::cout << "played card " << poz << " from hand\n";
            return;
        }
        std::cout << "not enough mana!\n";
    }

    void player::drawCard() {
        if (p_deck.getSize() == 0) {
            std::cout << "deck empty!\n";
            return;
        }
        if (hand.size() >= 10) {
            std::cout << "hand is full\n";
            p_deck.getCard(); // "destroy" card you would have drawn
            return;
        }
        hand.push_back(p_deck.getCard() );
    }

    void player::takeDMG(int dmg) {
        health -= dmg;
    }

    void player::atkMinion(player &p2, const unsigned int atk_poz, const unsigned int targ_poz) {
        if (board[atk_poz].check_atkFlag()) {
            std::cout << "minion has already attacked!\n";
            return;
        }
        if (atk_poz > board.size()-1) {
            std::cout << "minion beyond board!\n";
            return;
        }
        board[atk_poz].attack(p2.getMinion(targ_poz));
        // ulog << "attacked minion " << targ_poz << "with minion " << atk_poz << '\n';
        std::cout << "attacked minion " << targ_poz << " with minion " << atk_poz << '\n';
        this->checkBoard();
        p2.checkBoard();

    }

    void player::atkPlayer(player &p2, const unsigned int atk_poz) {
        if (board[atk_poz].check_atkFlag()) {
            std::cout << "minion has already attacked!\n";
            return;
        }
        p2.takeDMG( board[atk_poz].getPower() );
        board[atk_poz].set_atkFlag(true);
        // ulog << "attacked player with minion " << atk_poz << '\n';
        std::cout << "attacked player with minion " << atk_poz << '\n';
    }

    card& player::getMinion(const unsigned int poz) { // a minion is a card on the board
        if (poz > board.size()-1) {
            std::cout << "minion beyond board!\n";
            // return card(0, 0, 0);
            // ce returnez aici even?
        }
        return board[poz];
    }

    void player::checkBoard() {
        // removes dead minions from board
        for (unsigned int i=0; i < board.size(); ++i) {
            if (board[i].getHealth() <= 0 ) {
                board.erase(board.begin() + i);
                // ulog << "Minion " << i << " has died\n";
                std::cout << "Minion " << i << " has died\n";

            }
        }
    }

    void player::startTurn() {
        active = true;
        this->drawCard();
    }

    void player::endTurn() {
        if (maxMana < 10)
            maxMana += 1;
        curMana = maxMana;
        active = false;
        for (card &card : board) {
            card.set_atkFlag(false);
            //reset all minions on board
        }
    }

    std::ostream& operator<< (std::ostream &os, const player &p1) {
        os << "act:" << p1.active;
        os << " MCap:" << p1.maxMana;
        os << " M:" << p1.curMana;
        os << " hp:" << p1.health;
        os << '\n' << "hand: " << p1.hand.size() << " cards\n";
        for (const card& card : p1.hand)
            os << card << "||";
        os << '\n' << "board: " << p1.board.size() << " minions\n";
        for (const card& card : p1.board)
            os << card << "||";
        os << '\n' << "deck: ";
        os << p1.p_deck << "\n\n";
        return os;
    }