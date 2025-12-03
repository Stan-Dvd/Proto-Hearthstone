
#include "player.hpp"

sf::Sprite player::turn_button(ResourceManager::Instance().getTexture("turn_end.png"));

player::player(const int id) :
    maxMana(1), curMana(1), health(10), player_id(id), active(false),
    Hand_startPosX(0), Hand_startPosY(0), Board_startPosX(0), Board_startPosY(0),  p_deck(id),
    mana_text(ResourceManager::Instance().getFont(FONT_DEFUALT)),
    hp_text(ResourceManager::Instance().getFont(FONT_DEFUALT)),
    mana_sprite(ResourceManager::Instance().getTexture("crystal.png")),
    hp_sprite(ResourceManager::Instance().getTexture("blood.png"))
{
    mana_text.setCharacterSize(FONT_SIZE);
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
        board[board.size() - 1].setScale(0.65f, 0.65f);
        curMana = curMana - hand[poz].getCost(); // pay mana cost
        hand.erase(hand.begin() + poz); // erase card from hand
        std::cout << "played card " << poz << " from hand\n";
        return;
    }
    std::cout << "not enough mana!\n";
}

void player::drawFromDeck() {
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
    if (atk_poz > board.size()-1) {
        std::cout << "own minion beyond board!\n";
        return;
    }
    if (targ_poz > p2.board.size()-1) {
        std::cout << "enemy minion beyond board!\n";
        return;
    }
    if (board[atk_poz].check_atkFlag()) {
        std::cout << "minion has already attacked!\n";
        return;
    }
    board[atk_poz].attack(p2.getMinion(targ_poz));
    // ulog << "attacked minion " << targ_poz << "with minion " << atk_poz << '\n';
    std::cout << "attacked minion " << targ_poz << " with minion " << atk_poz << '\n';
    this->checkBoard();
    p2.checkBoard();

}

void player::atkPlayer(player &p2, const unsigned int atk_poz) {
    if (atk_poz > board.size()-1) {
        std::cout << "minion beyond board!\n";
        return;
    }
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
    this->drawFromDeck();
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
    if (player_id == 1)
        turn_button.setTexture(ResourceManager::Instance().getTexture("turn_end_p2.png"));
    else
        turn_button.setTexture(ResourceManager::Instance().getTexture("turn_end.png"));
}

void player::setStartPos(const sf::RenderWindow &window) {
    //set positions for displaying hand, board, mana, hp
    sf::Vector2u size = window.getSize();

    turn_button.setPosition({static_cast<float>(size.x) * 0.76f,
                            static_cast<float>(size.y) * 0.43f});
    turn_button.setScale({0.7f, 0.7f});
    if (player_id == 1) {
        //hand
        Hand_startPosX = static_cast<float>(size.x) * 0.05f;
        Hand_startPosY = static_cast<float>(size.y) * 0.75f;
        //board
        Board_startPosX = static_cast<float>(size.x) * 0.3f;
        Board_startPosY = static_cast<float>(size.y) * 0.5f;
        //mana
        mana_text.setPosition({static_cast<float>(size.x) * 0.65f,
                        static_cast<float>(size.y) * 0.68f});
        mana_sprite.setPosition({static_cast<float>(size.x) * 0.61f,
                        static_cast<float>(size.y) * 0.68f});
        mana_sprite.setScale({0.6f, 0.6f});
        //hp
        hp_sprite.setPosition({static_cast<float>(size.x) * 0.35f,
                static_cast<float>(size.y) * 0.67f});
        hp_sprite.setScale({0.15f, 0.15f});
        hp_text.setPosition({static_cast<float>(size.x) * 0.36f,
                        static_cast<float>(size.y) * 0.69f});
        // std::cout<< "player1\n";
    }
    else {
        //hand
        Hand_startPosX = static_cast<float>(size.x) * 0.85f;
        Hand_startPosY = static_cast<float>(size.y) * 0.05f;
        //board
        Board_startPosX = static_cast<float>(size.x) * 0.6f;
        Board_startPosY = static_cast<float>(size.y) * 0.32f;
        //hp
        mana_text.setPosition({static_cast<float>(size.x) * 0.37f,
                        static_cast<float>(size.y) * 0.25f});
        mana_sprite.setPosition({static_cast<float>(size.x) * 0.33f,
                        static_cast<float>(size.y) * 0.25f});
        mana_sprite.setScale({0.6f, 0.6f});
        //hp
        hp_sprite.setPosition({static_cast<float>(size.x) * 0.6f,
                static_cast<float>(size.y) * 0.25f});
        hp_sprite.setScale({0.15f, 0.15f});
        hp_text.setPosition({static_cast<float>(size.x) * 0.612f,
                        static_cast<float>(size.y) * 0.27f});
    }
}

void player::drawHand(sf::RenderWindow &window) {
    if (player_id == 1) {
        for (unsigned int i=0; i < hand.size(); ++i) {
            hand[i].draw(window, Hand_startPosX + static_cast<float>(i* SLOT_WIDTH), Hand_startPosY);
        }
    }
    else {
        for (unsigned int i=0; i < hand.size(); ++i) {
            hand[i].draw(window, Hand_startPosX - static_cast<float>(i* SLOT_WIDTH), Hand_startPosY);
        }
    }
}

void player::drawBoard(sf::RenderWindow &window) {
    if (player_id == 1) {
        for (unsigned int i=0; i < board.size(); ++i) {
            board[i].draw(window, Board_startPosX + static_cast<float>(i * SLOT_WIDTH/1.6), Board_startPosY);
        }
    }
    else {
        for (unsigned int i=0; i < board.size(); ++i) {
            board[i].draw(window, Board_startPosX - static_cast<float>(i * SLOT_WIDTH/1.6), Board_startPosY);
        }
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
    window.draw(turn_button);
    window.draw(mana_sprite);
}

void player::drawPlayer(sf::RenderWindow &window) {
    this->drawBoard(window);
    this->drawHand(window);
    this->drawManaHp(window);
}

std::ostream& operator<< (std::ostream &os, const player &p1) {
    os << "act:" << p1.active;
    os << " MCap:" << p1.maxMana;
    os << " M:" << p1.curMana;
    os << " hp:" << p1.health;
    os << '\n' << "hand: " << p1.hand.size() << " cards\n";
    for (unsigned int i=0; i < p1.hand.size(); ++i)
        os << i << p1.hand[i] << "||";
    os << '\n' << "board: " << p1.board.size() << " minions\n";
    for (const card& card : p1.board)
        os << card << "||";
    os << '\n' << "deck: ";
    os << p1.p_deck << "\n\n";
    return os;
}