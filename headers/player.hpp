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
    std::vector<card*> hand;
    std::vector<minion*> board; //nuj daca are sens asta da vedem
    deck p_deck;
    sf::Text mana_text, hp_text;
    sf::Sprite mana_sprite, hp_sprite;
public:
    player(int id);
    ~player();

    void deck_init( card* *card_pool, const int *card_freq, const int pool_size);

    void playCard( const unsigned int poz ); //debug
    void deployMinion(minion* atk);
    void drawFromDeck();
    void takeDMG(int dmg);
    //TODO: obsolete
    // void atkMinion(player &p2, const unsigned int atk_poz, const unsigned int targ_poz); //debug
    // void atkMinion(player &p2, card* atk, card* target);
    // void atkPlayer(player &p2, const unsigned int atk_poz); //debug
    // void atkPlayer(player &p2, card* atk);

    card* getMinion(const unsigned int poz);
    card* getCard(const unsigned int poz);

    void checkBoard();
    void startTurn();
    void endTurn();

    card* selectHand(const sf::Vector2f mouse_pos);
    minion* selectBoard(const sf::Vector2f mouse_pos);
    card* selectCard(const sf::Vector2f mouse_pos);
    bool selectPlayer(const sf::Vector2f mouse_pos);

    void setStartPos(const sf::RenderWindow &window);
    sf::FloatRect getBoardBounds() const;
    void drawHand(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    void drawManaHp(sf::RenderWindow &window);
    void drawPlayer(sf::RenderWindow &window);

    void display();
    // friend std::ostream& operator<< (std::ostream &os, const player &p1);
};


#endif //PLAYER_HPP
