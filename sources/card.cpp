#include "card.h"
#include "ResourceManager.hpp"

    card::card(int cost, int pow, int hp, std::string texture):
                    cost(cost), power(pow), health(hp),
                    card_sprite(ResourceManager::Instance().getTexture(texture)),
                    hp_txt(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                    pow_txt(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                    cost_txt(ResourceManager::Instance().getFont(FONT_DEFUALT))
        {
            attackFlag = false;
            selectFLag = false;
            hp_txt.setString(std::to_string(health));
            hp_txt.setCharacterSize(FONT_SIZE);
            // hp_txt.setFillColor(sf::Color::Black);
            pow_txt.setString(std::to_string(power));
            pow_txt.setCharacterSize(FONT_SIZE);
            // pow_txt.setFillColor(sf::Color::Black);
            cost_txt.setString(std::to_string(cost));
            cost_txt.setCharacterSize(FONT_SIZE);
            // cost_txt.setFillColor(sf::Color::Black);
        }

    card::card (const card &model):
            cost(model.cost), power(model.power), health(model.health),
            attackFlag(model.attackFlag), selectFLag(model.selectFLag),
            card_sprite(model.card_sprite.getTexture()),
            hp_txt(model.hp_txt),
            pow_txt(model.pow_txt),
            cost_txt(model.cost_txt) {} // COPY constructor

card::~card() {
        sf::Texture blankT = sf::Texture();
        sf::Font blankF = sf::Font();
        // nu ma lasa sa pun pur si simplu Texture() in functie ughh
        card_sprite.setTexture(blankT);
        hp_txt.setFont(blankF);
        pow_txt.setFont(blankF);
        cost_txt.setFont(blankF);
    }

// GET/SETTERS

    int card::getCost() {
        return cost;
    }
    int card::getPower() {
        return power;
    }
    int card::getHealth() {
        return health;
    }
    void card::set_atkFlag(const bool val) {
        attackFlag = val;
    }
    bool card::check_atkFlag() {
        return attackFlag;
    }

    void card::attack(card &target) {
        target.health -= power;
        health -= target.power;
        // both cards damage each-other
        attackFlag = true;
    }

    int card::is_playable(int mana) {
        if (mana >= cost)
            return 1;
        return 0;
    }

//SFML
    void card::draw(sf::RenderWindow &window, const float x, const float y) {
        card_sprite.setPosition({x, y});
        sf::FloatRect bounds = card_sprite.getGlobalBounds();

        float new_x = bounds.position.x + bounds.size.x * 0.08f;
        float new_y = bounds.position.y + bounds.size.y * 0.01f;
        cost_txt.setPosition({new_x, new_y});
        new_x = bounds.position.x + bounds.size.x * 0.11f;
        new_y = bounds.position.y + bounds.size.y - bounds.size.y * 0.19f;
        pow_txt.setPosition({new_x, new_y});
        new_x = bounds.position.x + bounds.size.x - bounds.size.x * 0.16f;
        new_y = bounds.position.y + bounds.size.y - bounds.size.y * 0.19f;
        hp_txt.setPosition({new_x, new_y});

        window.draw(card_sprite);
        window.draw(hp_txt);
        window.draw(cost_txt);
        window.draw(pow_txt);
    }

void card::setScale(const float x, const float y) {
        card_sprite.setScale({x, y});
        hp_txt.setScale({x, y});
        pow_txt.setScale({x, y});
        cost_txt.setScale({x, y});
    }


// OPERATORS

    // card card::operator=(const card &model){
    //     cost = model.cost;
    //     power = model.power;
    //     health = model.health;
    //     attackFlag = model.attackFlag;
    //     card_sprite = model.card_sprite;
    //     hp_txt = model.hp_txt;
    //     pow_txt = model.pow_txt;
    //     cost_txt = model.cost_txt;
    //     return *this;
    // }
    std::ostream& operator<< (std::ostream &os, const card &card) {
        os << "c:"<< card.cost;
        os << " pwr:" << card.power;
        os << " hp:" << card.health;
        os << " flg:" << card.attackFlag;
        // os << " ";
        return os;
    }