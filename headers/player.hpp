//
// Created by StanD on 30/11/2025.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <deck.hpp>
#include <minion.hpp>

class player {
private:
    int maxMana, curMana, health, player_id;
    bool active;
    float Hand_startPosX, Hand_startPosY, Board_startPosX, Board_startPosY;
    card* signature;
    std::vector<card*> hand;
    std::vector<minion*> board;
    deck p_deck;
    sf::Text mana_text, hp_text;
    sf::Sprite mana_sprite, hp_sprite;
public:
    explicit player(int id);
    ~player();

    void init(CardTypes * card_pool,
                const int *card_freq,
                const int pool_size,
                const CardTypes sig);

    //GAME ACTIONS
    void playCard( const unsigned int poz ); //debug
    void deployMinion(minion* atk);
    void remove_fromHand(const card* card);
    void drawFromDeck();
    void takeDMG(const int dmg);
    void heal(const int val);
    void payCost(const int cost);
    card* getMinion(const unsigned int poz);
    card* getCard(const unsigned int poz) const;
    unsigned int getBoardSize() const;
    void checkBoard();
    void startTurn();
    void endTurn();

    //MOUSE CHECKS
    card* selectHand(const sf::Vector2f mouse_pos) const;
    minion* selectBoard(const sf::Vector2f mouse_pos) const;
    card* selectCard(const sf::Vector2f mouse_pos) const;
    bool selectPlayer(const sf::Vector2f mouse_pos) const;

    //SPRITE/DRAW stuff
    void setStartPos(const sf::RenderWindow &window);
    sf::FloatRect getBoardBounds() const;
    void drawHand(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    void drawSig(sf::RenderWindow &window);
    void drawManaHp(sf::RenderWindow &window);
    void drawPlayer(sf::RenderWindow &window);

    //debug print
    void display();
    // friend std::ostream& operator<< (std::ostream &os, const player &p1);
};


#endif //PLAYER_HPP
