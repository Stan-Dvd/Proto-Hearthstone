//
// Created by StanD on 30/11/2025.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <deck.hpp>

class player {
private:
    int maxMana, curMana, health, player_id;
    bool active;
    float Hand_startPosX, Hand_startPosY, Board_startPosX, Board_startPosY;
    std::vector<card> hand, board;
    deck p_deck;
    sf::Text mana_text, hp_text;
    sf::Sprite mana_sprite, hp_sprite;
public:
    player(int id);
    ~player();

    void deck_init( const card *card_pool, const int *card_freq, const int pool_size);

    void playCard( const unsigned int poz ); //debug
    void playCard(card* atk);
    void drawFromDeck();
    void takeDMG(int dmg);
    void atkMinion(player &p2, const unsigned int atk_poz, const unsigned int targ_poz); //debug
    void atkMinion(player &p2, card* atk, card* target);
    void atkPlayer(player &p2, const unsigned int atk_poz); //debug
    void atkPlayer(player &p2, card* atk);

    card& getMinion(const unsigned int poz);

    void checkBoard();
    void startTurn();
    void endTurn();

    card* selectCard(const sf::Vector2f mouse_pos);

    void setStartPos(const sf::RenderWindow &window);
    sf::FloatRect getBoardBounds() const;
    void drawHand(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    void drawManaHp(sf::RenderWindow &window);
    void drawPlayer(sf::RenderWindow &window);

    friend std::ostream& operator<< (std::ostream &os, const player &p1);
};

#endif //PLAYER_HPP
