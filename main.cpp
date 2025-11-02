#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>



class card {
private:
    int cost, power, health;
    bool attackFlag; // tracks if card has attacked this turn

public:

    // CONSTRUCTORS
    card() {
        cost = power = health = 0;
        attackFlag = false;
    }
    card(int cost, int pow, int hp) {
        this->cost = cost;
        power = pow;
        health = hp;
        attackFlag = false;
    }
    card (const card &model) {
        cost = model.cost;
        power = model.power;
        health = model.health;
        attackFlag = false;
    }// COPY constructor

    // GET/SETTERS

    int getCost() {
        return cost;
    }
    int getPower() {
        return power;
    }
    int getHealth() {
        return health;
    }
    void setFlag(const bool val) {
        attackFlag = val;
    }
    bool checkFlag() {
        return attackFlag;
    }

    card operator=(const card &model){
        cost = model.cost;
        power = model.power;
        health = model.health;
        attackFlag = model.attackFlag;
        return *this;
    }

    void attack(card &target) {
        target.health -= power;
        health -= target.power;
        // both cards damage each-other
        attackFlag = true;
    }

    int is_playable(int mana) {
        if (mana >= cost)
            return 1;
        return 0;
    }

    friend std::ostream& operator<< (std::ostream &os, const card &card) {
        os << "c:"<< card.cost;
        os << " pwr:" << card.power;
        os << " hp:" << card.health;
        os << " flg:" << card.attackFlag;
        // os << " ";
        return os;
    }
};

class deck {
private:
    std::vector<card> cards;

public:

    // CONSTRUCTORS
    deck() {
        cards.reserve(30);
    }

    deck(deck &model) {
        for (unsigned int i=0; i < model.getSize(); ++i) {
            cards.push_back( model.cards[i] );
        }
    }

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size) {
        int i=0;
        for (i=0; i<pool_size; ++i) {
            int k=0;
            while (k < card_freq[i]) {
                cards.push_back( card_pool[i] );
                k++;
            }
        }
    }

    ~deck() {
        cards.clear();
    }

    //GET/SETTERS
    unsigned int getSize() {
        return cards.size();
    }
    // void setCard(const int poz, const card& card) {
    //     cards[poz] = card;
    // }
    // card showCard(const int poz) {
    //     return cards[poz];
    // }
    card deckDraw() {
        //draw card from deck
        card x = cards[cards.size() - 1];
        cards.pop_back();
        return x;

    }

    void shuffle() {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(cards), std::end(cards), rng);
    }

    friend std::ostream& operator<< (std::ostream &os, const deck &deck) {
        std::cout << deck.cards.size() << " cards\n";
        for (unsigned   int i=0; i < deck.cards.size(); ++i) {
            os << deck.cards[i] << "||";
        }
        return os;
    }

};

class player {
private:
    int maxMana, curMana, health;
    bool active;
    std::vector<card> hand, board;
    deck p_deck;
public:
    player() {
        health = 10;
        maxMana = 1;
        curMana = 1;
        active = false;
        hand.reserve(10); // max hand size is 10
        board.reserve(7); //max minions on board is 7
    }
    ~player() = default;

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size) {
        p_deck.deck_init(card_pool, card_freq, pool_size);
        // nu imi place asta
    }

    void playCard(const unsigned int poz) {
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

    void drawCard() {
        if (p_deck.getSize() == 0) {
            std::cout << "deck empty!\n";
            return;
        }
        if (hand.size() >= 10) {
            std::cout << "hand is full\n";
            p_deck.deckDraw(); // "destroy" card you would have drawn
            return;
        }
        hand.push_back(p_deck.deckDraw() );
    }

    void takeDMG(int dmg) {
        health -= dmg;
    }

    void atkMinion(player &p2, const unsigned int atk_poz, const unsigned int targ_poz) {
        if (board[atk_poz].checkFlag()) {
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

    void atkPlayer(player &p2, const unsigned int atk_poz) {
        if (board[atk_poz].checkFlag()) {
            std::cout << "minion has already attacked!\n";
            return;
        }
        p2.takeDMG( board[atk_poz].getPower() );
        board[atk_poz].setFlag(true);
        // ulog << "attacked player with minion " << atk_poz << '\n';
        std::cout << "attacked player with minion " << atk_poz << '\n';
    }

    card& getMinion(const unsigned int poz) { // a minion is a card on the board
        if (poz > board.size()-1) {
            std::cout << "minion beyond board!\n";
            // return card(0, 0, 0);
            // ce returnez aici even?
        }
        return board[poz];
    }

    void checkBoard() {
        // removes dead minions from board
        for (unsigned int i=0; i < board.size(); ++i) {
            if (board[i].getHealth() <= 0 ) {
                board.erase(board.begin() + i);
                // ulog << "Minion " << i << " has died\n";
                std::cout << "Minion " << i << " has died\n";

            }
        }
    }

    void startTurn() {
        active = true;
        this->drawCard();
    }

    void endTurn() {
        if (maxMana < 10)
            maxMana += 1;
        curMana = maxMana;
        active = false;
        for (card &card : board) {
            card.setFlag(false);
            //reset all minions on board
        }
    }

    friend std::ostream& operator<< (std::ostream &os, const player &p1) {
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
};

// WEIRD ERROR, gave up
// deck build_test_deck() {
//     deck temp;
//     card cards[3] {card(1, 2, 1), card(2, 1, 4), card(3, 4, 2)};
//     for (int i=0; i<30; ++i){
//         temp.setCard(i, cards[i%3]);
//     }
//
//     return temp;
// }

int main() {

    card c1(1, 3, 4), c2;
    card const card_pool[3]{ card(3, 4, 2) , card(2, 1, 4), card(1, 2, 1)};
    int const card_freq[3]{3, 3, 3};
    player p1, p2;
    p1.deck_init(card_pool, card_freq, 3);
    p2.deck_init(card_pool, card_freq, 3);
    for (int i=0; i < 2; ++i) {
        p1.drawCard();
        p2.drawCard();
    }
    p1.startTurn();
    p1.playCard(0);
    p1.endTurn();

    p2.startTurn();
    p2.playCard(0);
    p2.endTurn();

    p1.startTurn();
    p1.playCard(5); // beyond hand
    p1.playCard(0);
    p1.atkPlayer(p2, 0);
    p1.atkPlayer(p2, 0); // already attacked
    p1.atkMinion(p2, 1, 0);
    p1.endTurn(); // OBS! minion flag gets reset
    std::cout << '\n' << p1 << p2;



    return 0;
}
