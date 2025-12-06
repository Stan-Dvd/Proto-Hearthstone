#include "card.hpp"

#include "minion.hpp"
#include "player.hpp"
#include <cmath>

card::card(const int cost, std::string texture):
                    cost(cost), selectFlag(false),
                    card_sprite(ResourceManager::Instance().getTexture(texture)),
                    cost_txt(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                    flavor_txt(ResourceManager::Instance().getFont(FONT_DEFUALT))
{
    // pow_txt.setFillColor(sf::Color::Black);
    cost_txt.setString(std::to_string(cost));
    cost_txt.setCharacterSize(FONT_SIZE);
    // cost_txt.setFillColor(sf::Color::Black);
}

    card::card (const card &model):
            cost(model.cost), selectFlag(model.selectFlag),
            card_sprite(model.card_sprite.getTexture()),
            cost_txt(model.cost_txt), flavor_txt(model.cost_txt) {
        // std::cout << "card copied";
} // COPY constructor

card::~card() {
        sf::Texture blankT = sf::Texture();
        sf::Font blankF = sf::Font();
        // nu ma lasa sa pun pur si simplu Texture() in functie ughh
        card_sprite.setTexture(blankT);
        cost_txt.setFont(blankF);
    }

// GET/SETTERS

int card::getCost() {
    return cost;
}

sf::FloatRect card::getGlobalBounds() {
    return card_sprite.getGlobalBounds();
}

bool card::check_selectFlag() {
    return selectFlag;
}

void card::set_selectFlag(const bool val) {
    selectFlag = val;
}

int card::is_playable(int mana) {
    if (mana >= cost)
        return 1;
    return 0;
}

//SFML

// NVI
void card::draw(sf::RenderWindow &window, const float x, const float y) {
    card_sprite.setPosition({x, y});
    sf::FloatRect bounds = card_sprite.getGlobalBounds();

    float new_x = bounds.position.x + bounds.size.x * 0.08f;
    float new_y = bounds.position.y + bounds.size.y * 0.01f;
    cost_txt.setPosition({new_x, new_y});

    window.draw(card_sprite);
    window.draw(cost_txt);

    draw_details(window);
}

//NVI
void card::setScale(const float x, const float y) {
        card_sprite.setScale({x, y});
        cost_txt.setScale({x, y});
        setDetailscale(x, y);
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
// std::ostream& operator<< (std::ostream &os, const card &card) {
//     os << "c:"<< card.cost;
//     os << " Sflg:" << card.selectFLag;
//     // os << " ";
//     return os;
// }

void card::display(const bool &endl) {
    std::cout << "C:" << cost;
    displayDetails();
    std::cout << " Sf:" << selectFlag;
    if (endl)
        std::cout << '\n';
}
