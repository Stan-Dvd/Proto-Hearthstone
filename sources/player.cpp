#include "player.hpp"

#include "exceptions.hpp"

player::player(const int id) : maxMana(1), curMana(1), health(10), player_id(id), active(false),
                               Hand_startPosX(0), Hand_startPosY(0), Board_startPosX(0), Board_startPosY(0),
                               signature(nullptr),
                               mana_text(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                               hp_text(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                               mana_sprite(ResourceManager::Instance().getTexture("crystal.png")),
                               hp_sprite(ResourceManager::Instance().getTexture("blood.png")) {
    mana_text.setCharacterSize(FONT_SIZE);
    hand.reserve(10); // max hand size is 10
    board.reserve(7); //max minions on board is 7
}

//better if it's just deleted, it doesn't make sense anyway
// player player::operator=(const player &model) {
//     p_deck = model.p_deck;
//     unsigned int i;
//     for (i = 0; i < model.hand.size(); ++i) {
//         hand[i] = model.hand[i]->clone();
//     }
//     for (i = 0; i < model.board.size(); ++i) {
//         board[i] = dynamic_cast<minion*>(model.board[i]->clone());
//     }
//     signature = model.signature->clone();
//     return *this;
// }

player::~player() {
    unsigned int i;
    std::cout << "p" << player_id << " delHand\n";
    for (i = 0; i < hand.size(); ++i) {
        delete hand[i];
    }
    std::cout << "p" << player_id << " delBoard\n";
    for (i = 0; i < board.size(); ++i) {
        delete board[i];
    }
    // delete signature;
    std::cout <<"player deleted" <<player_id << "\n";
};

void player::setSignature(CardTypes sig) {
    signature = CardFactory::Instance().create_card(sig);
}

void player::setDeck(const CardTypes *card_pool, const int *card_freq, const int pool_size) {
    p_deck.deck_init(card_pool, card_freq, pool_size); // nu imi place asta
    p_deck.shuffle();
}

void player::playCard(const unsigned int poz) {
    if (!active) {
        std::cout << "player inactive!\n";
        return;
        // va fi folosit pt butoane probabil
    }
    if (poz > hand.size() - 1) {
        // teoretic n-ar trb sa se intample la butoane
        std::cout << "card beyond hand!\n";
        return;
    }
    if (board.size() >= 7) {
        std::cout << "board is full\n";
        return;
    }
    if (hand[poz]->is_playable(curMana)) {
        // check if player has enough mana
        board.push_back(static_cast<minion *>(hand[poz])); //place card on board
        board[board.size() - 1]->setScale(BOARD_SCALE, BOARD_SCALE);
        board[board.size() - 1]->set_selectFlag(false);
        board[board.size() - 1]->set_atkFlag(true);
        board[board.size() - 1]->set_deployFlag(true);

        curMana = curMana - hand[poz]->getCost(); // pay mana cost
        //DELETE card from hand (in a very scuffed way because pointers)
        hand.erase(hand.begin() + poz);
        return;
    }
    std::cout << "not enough mana!\n";
}

void player::deployMinion(minion *atk) {
    if (board.size() >= 7) {
        std::cout << "board is full\n";
        throw overflow_exception("Board");
    }
    if (atk->is_playable(curMana)) {
        // check if player has enough mana
        atk->set_selectFlag(false);
        atk->set_atkFlag(true);
        atk->set_deployFlag(true);
        atk->setScale(BOARD_SCALE, BOARD_SCALE);

        board.push_back(atk); //place card on board
        curMana = curMana - atk->getCost(); // pay mana cost

        //DELETE card from hand (in a very scuffed way because pointers)
        remove_fromHand(atk);
        return;
    }
    std::cout << "not enough mana!\n";
    throw mana_exception(atk->getCost() - curMana);
}

void player::remove_fromHand(const card *card) {
    for (unsigned int i = 0; i < hand.size(); ++i) {
        if (hand[i] == card) {
            hand.erase(hand.begin() + i);
            std::cout << "played card" << i << "from hand\n";
        }
    }
}


void player::drawFromDeck() {
    // std::cout << p_deck.getSize() << '\n';
    if (p_deck.getSize() == 0) {
        std::cout << "deck empty!\n";
        throw empty_exception("Deck");
    }
    if (hand.size() >= 10) {
        p_deck.getCard(); // "destroy" card you would have drawn
        throw overflow_exception("Hand");
    }
    hand.push_back(p_deck.getCard());
}

void player::takeDMG(const int dmg) {
    health -= dmg;
}

void player::heal(const int val) {
    health += val;
}

void player::payCost(const int cost) {
    if (cost > curMana) {
        throw mana_exception(cost - curMana);
    }
    curMana -= cost;
}

//obsolete in GUI
// card* player::getMinion(const unsigned int poz) { // a minion is a card on the board
//     if (poz > board.size()-1) {
//         std::cout << "minion beyond board!\n";
//         // return card(0, 0, 0);
//         // ce returnez aici even?
//     }
//     return board[poz];
// }
// card *player::getCard(const unsigned int poz) const{
//     if (poz > hand.size()) {
//         std::cout << "nu nu";
//     }
//     return hand[poz];
// }

unsigned int player::getBoardSize() const {
    return board.size();
}

void player::checkBoard() {
    // removes dead minions from board
    for (unsigned int i = 0; i < board.size(); ++i) {
        if (board[i]->getHealth() <= 0) {
            delete board[i];
            board.erase(board.begin() + i);
            // ulog << "Minion " << i << " has died\n";
            std::cout << "Minion " << i << " has died\n";
        }
    }
}

void player::startTurn() {
    active = true;
    this->drawFromDeck();
}

void player::endTurn() {
    if (maxMana < 10)
        maxMana += 1;
    curMana = maxMana;
    active = false;
    for (minion *card: board) {
        card->set_atkFlag(false);
        //reset all minions on board
    }
}

// ====SELECT====

card *player::selectHand(const sf::Vector2f mouse_pos) const {
    //search hand
    for (unsigned int i = 0; i < hand.size(); ++i) {
        if (hand[i]->getGlobalBounds().contains(mouse_pos)) {
            // hand[i].set_selectFlag(true);
            return hand[i];
        }
    }
    return nullptr;
}

minion *player::selectBoard(const sf::Vector2f mouse_pos) const {
    for (unsigned int i = 0; i < board.size(); ++i) {
        if (board[i]->getGlobalBounds().contains(mouse_pos)) {
            // board[i].set_selectFlag(true);
            return board[i];
        }
    }
    return nullptr;
}

card *player::selectCard(const sf::Vector2f mouse_pos) const {
    //asta e kinda stupid

    if (signature->getGlobalBounds().contains(mouse_pos)) {
        return signature;
    }

    card *select;
    if ((select = selectHand(mouse_pos)) != nullptr) {
        return select;
    }
    if ((select = selectHand(mouse_pos)) != nullptr) {
        return select;
    }

    return selectBoard(mouse_pos);
}

bool player::selectPlayer(const sf::Vector2f mouse_pos) const {
    if (hp_sprite.getGlobalBounds().contains(mouse_pos))
        return true;
    return false;
}

sf::FloatRect player::getBoardBounds() const {
    sf::FloatRect bounds;
    if (player_id == 2)
        bounds.position.x = Board_startPosX - 7 * SLOT_WIDTH * BOARD_SCALE;
    else
        bounds.position.x = Board_startPosX;
    bounds.position.y = Board_startPosY;
    bounds.size.x = 7 * SLOT_WIDTH * BOARD_SCALE;
    bounds.size.y = SLOT_HEIGHT * BOARD_SCALE;

    return bounds;
}

// ====DRAW====

void player::setStartPos(const sf::RenderWindow &window) {
    //set positions for displaying hand, board, mana, hp
    sf::Vector2u size = window.getSize();
    if (player_id == 1) {
        //hand
        Hand_startPosX = static_cast<float>(size.x) * 0.05f;
        Hand_startPosY = static_cast<float>(size.y) * 0.75f;
        //board
        Board_startPosX = static_cast<float>(size.x) * 0.3f;
        Board_startPosY = static_cast<float>(size.y) * 0.5f;
        //mana
        mana_text.setPosition({
            static_cast<float>(size.x) * 0.65f,
            static_cast<float>(size.y) * 0.68f
        });
        mana_sprite.setPosition({
            static_cast<float>(size.x) * 0.61f,
            static_cast<float>(size.y) * 0.68f
        });
        mana_sprite.setScale({0.6f, 0.6f});
        //hp
        hp_sprite.setPosition({
            static_cast<float>(size.x) * 0.35f,
            static_cast<float>(size.y) * 0.67f
        });
        hp_sprite.setScale({0.15f, 0.15f});
        hp_text.setPosition({
            static_cast<float>(size.x) * 0.36f,
            static_cast<float>(size.y) * 0.69f
        });
        // std::cout<< "player1\n";
    } else {
        //hand
        Hand_startPosX = static_cast<float>(size.x) * 0.85f;
        Hand_startPosY = static_cast<float>(size.y) * 0.03f;
        //board
        Board_startPosX = static_cast<float>(size.x) * 0.6f;
        Board_startPosY = static_cast<float>(size.y) * 0.32f;
        //hp
        mana_text.setPosition({
            static_cast<float>(size.x) * 0.37f,
            static_cast<float>(size.y) * 0.25f
        });
        mana_sprite.setPosition({
            static_cast<float>(size.x) * 0.33f,
            static_cast<float>(size.y) * 0.25f
        });
        mana_sprite.setScale({0.6f, 0.6f});
        //hp
        hp_sprite.setPosition({
            static_cast<float>(size.x) * 0.6f,
            static_cast<float>(size.y) * 0.25f
        });
        hp_sprite.setScale({0.15f, 0.15f});
        hp_text.setPosition({
            static_cast<float>(size.x) * 0.612f,
            static_cast<float>(size.y) * 0.27f
        });
    }
}

void player::drawHand(sf::RenderWindow &window) const {
    float offset; //if select flag is 0, set 0 (no drawing offset)
    if (player_id == 1) {
        for (unsigned int i = 0; i < hand.size(); ++i) {
            offset = hand[i]->check_selectFlag() ? SELECT_OFFSET / 1.6 : 0;
            hand[i]->draw(window, Hand_startPosX + static_cast<float>(i * SLOT_WIDTH), Hand_startPosY - offset);
        }
    } else {
        for (unsigned int i = 0; i < hand.size(); ++i) {
            offset = hand[i]->check_selectFlag() ? SELECT_OFFSET / 1.6 : 0;
            hand[i]->draw(window, Hand_startPosX - static_cast<float>(i * SLOT_WIDTH), Hand_startPosY + offset);
        }
    }
}

void player::drawBoard(sf::RenderWindow &window) const {
    float offset; //if select flag is 0, set 0 (no drawing offset)
    if (player_id == 1) {
        for (unsigned int i = 0; i < board.size(); ++i) {
            offset = board[i]->check_selectFlag() ? SELECT_OFFSET / 1.6 : 0;
            board[i]->draw(window, Board_startPosX + static_cast<float>(i * SLOT_WIDTH / 1.6),
                           Board_startPosY - offset);
        }
    } else {
        for (unsigned int i = 0; i < board.size(); ++i) {
            offset = board[i]->check_selectFlag() ? SELECT_OFFSET / 1.6 : 0;
            board[i]->draw(window, Board_startPosX - static_cast<float>(i * SLOT_WIDTH / 1.6),
                           Board_startPosY + offset);
        }
    }
}

void player::drawSig(sf::RenderWindow &window) const {
    sf::Vector2u size = window.getSize();

    //if select flag is 0, set 0 (no drawing offset)
    float offset = signature->check_selectFlag() ? SELECT_OFFSET : 0;

    if (player_id == 1) {
        signature->draw(window, static_cast<float>(size.x) * 0.03f,
                        static_cast<float>(size.y) * 0.5f - offset);
    } else {
        signature->draw(window, static_cast<float>(size.x) * 0.9f,
                        static_cast<float>(size.y) * 0.3f + offset);
    }
}


void player::drawManaHp(sf::RenderWindow &window) {
    std::ostringstream buf;
    buf << curMana << "/" << maxMana;
    mana_text.setString(buf.str());
    hp_text.setString(std::to_string(health));
    window.draw(mana_text);
    window.draw(hp_sprite);
    window.draw(hp_text);
    window.draw(mana_sprite);
}

void player::drawPlayer(sf::RenderWindow &window) {
    this->drawBoard(window);
    this->drawHand(window);
    this->drawManaHp(window);
    this->drawSig(window);
}

void player::display() {
    std::cout << "act:" << active << " MM:" << maxMana << " M:" << curMana;
    std::cout << " HP:" << health << " Hand: " << hand.size() << " cards\n";
    for (unsigned int i = 0; i < hand.size(); ++i) {
        std::cout << i;
        hand[i]->display();
        std::cout << "||";
    }
    std::cout << "\nBoard: " << board.size() << " cards\n";
    for (unsigned int i = 0; i < board.size(); ++i) {
        std::cout << i;
        board[i]->display();
        std::cout << "||";
    }
    std::cout << "\nDeck: ";
    p_deck.display();
    std::cout << "\n\n";
}


// std::ostream& operator<< (std::ostream &os, const player &p1) {
//     os << "act:" << p1.active;
//     os << " MCap:" << p1.maxMana;
//     os << " M:" << p1.curMana;
//     os << " hp:" << p1.health;
//     os << '\n' << "hand: " << p1.hand.size() << " cards\n";
//     for (unsigned int i=0; i < p1.hand.size(); ++i)
//         os << i << p1.hand[i] << "||";
//     os << '\n' << "board: " << p1.board.size() << " minions\n";
//     for (const card& card : p1.board)
//         os << card << "||";
//     os << '\n' << "deck: ";
//     os << p1.p_deck << "\n\n";
//     return os;
// }
