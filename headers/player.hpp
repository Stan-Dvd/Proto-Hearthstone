#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <deck.hpp>
#include <minion.hpp>

class player {
private:
    int maxMana, curMana, health, player_id;
    bool active;
    float Hand_startPosX, Hand_startPosY, Board_startPosX, Board_startPosY;
    card *signature;
    std::vector<card *> hand;
    std::vector<minion *> board;
    deck p_deck;
    sf::Text mana_text, hp_text;
    sf::Sprite mana_sprite, hp_sprite;

public:
    explicit player(int id);
    player(const player &model) = delete;
    player operator=(const player &model) = delete;
    ~player();

    void init(const CardTypes *card_pool,
              const int *card_freq,
              int pool_size,
              CardTypes sig);

    void setSignature(CardTypes sig);
    void setDeck(const CardTypes *card_pool, const int *card_freq, const int pool_size);

    //GAME ACTIONS
    void playCard(unsigned int poz); //debug
    void deployMinion(minion *atk);
    void remove_fromHand(const card *card);
    void drawFromDeck();
    void takeDMG(int dmg);
    void heal(int val);
    void payCost(int cost);
    // card* getMinion(unsigned int poz);
    // card* getCard(const unsigned int poz) const;
    unsigned int getBoardSize() const;
    void checkBoard();
    void startTurn();
    void endTurn();

    //MOUSE CHECKS
    card *selectHand(sf::Vector2f mouse_pos) const;
    minion *selectBoard(sf::Vector2f mouse_pos) const;
    card *selectCard(sf::Vector2f mouse_pos) const;
    bool selectPlayer(sf::Vector2f mouse_pos) const;

    //SPRITE/DRAW stuff
    void setStartPos(const sf::RenderWindow &window);
    sf::FloatRect getBoardBounds() const;
    void drawHand(sf::RenderWindow &window) const;
    void drawBoard(sf::RenderWindow &window) const;
    void drawSig(sf::RenderWindow &window) const;
    void drawManaHp(sf::RenderWindow &window);
    void drawPlayer(sf::RenderWindow &window);

    //debug print
    void display();
    // friend std::ostream& operator<< (std::ostream &os, const player &p1);
};


#endif //PLAYER_HPP
