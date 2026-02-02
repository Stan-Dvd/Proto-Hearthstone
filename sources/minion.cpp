#include "minion.hpp"
#include "player.hpp"
#include <cmath>

minion::minion(int cost, int pow, int hp, std::string texture):
                    card(cost, texture),
                    power(pow), health(hp),
                    attackFlag(false), deployFlag(false),
                    hp_txt(ResourceManager::Instance().getFont(FONT_DEFUALT)),
                    pow_txt(ResourceManager::Instance().getFont(FONT_DEFUALT))
{
    hp_txt.setString(std::to_string(health));
    hp_txt.setCharacterSize(FONT_SIZE);
    // hp_txt.setFillColor(sf::Color::Black);
    pow_txt.setString(std::to_string(power));
    pow_txt.setCharacterSize(FONT_SIZE);
    // pow_txt.setFillColor(sf::Color::Black);
    // cost_txt.setFillColor(sf::Color::Black);
}

minion::minion(const minion &model): card(model),
                                     power(model.power), health(model.health),
                                     attackFlag(model.attackFlag), deployFlag(model.deployFlag),
                                     hp_txt(model.hp_txt),
                                     pow_txt(model.pow_txt) {
    // std::cout << "card copied";
} // COPY constructor

minion::~minion() {
    sf::Texture blankT = sf::Texture();
    sf::Font blankF = sf::Font();
    // nu ma lasa sa pun pur si simplu Texture() in functie ughh
    hp_txt.setFont(blankF);
    pow_txt.setFont(blankF);
}

// GET/SETTERS

int minion::getPower() const{
    return power;
}
int minion::getHealth() const{
    return health;
}

bool minion::check_atkFlag() const{
    return attackFlag;
}
bool minion::check_deployFlag() const{
    return deployFlag;
}

void minion::set_atkFlag(const bool val) {
    attackFlag = val;
}

void minion::set_deployFlag(const bool val) {
    deployFlag = val;
}

void minion::buff(const int val) {
    power += val;
}

void minion::heal(const int val) {
    health += val;
}

void minion::takeDMG(const int val) {
    health -= val;
}

void minion::action(player **p, const bool owner, const sf::Vector2f mouse_pos) {

    //whatever happens, deselect card. otherwise gets way too complicated
    //set_selectFlag(false); this happens in game now

    if (deployFlag == false) {
        // minion is in hand. deploy minion?
        if (p[owner]->getBoardBounds().contains(mouse_pos)) {
            p[owner]->deployMinion(this); //can throw mana exc
            return;
        }
        throw target_exception("friendly board");
    }

    //minion is on board. attack?
    if (attackFlag == true) {
        std::cout << "minion has already attacked / is not ready\n";
        throw ready_exception();
    }

    minion *target = p[!owner]->selectBoard(mouse_pos);
    if (target != nullptr) {
        // if target is enemy minion
        attackFlag = true;
        attack(target);
        p[0]->checkBoard();
        p[1]->checkBoard();
        std::cout << "minion of player " << !owner << " attacked\n";
        return;
    }
    if (p[!owner]->selectPlayer(mouse_pos)) {
        attackFlag = true;
        p[!owner]->takeDMG(power);
        std::cout << "player " << !owner << " attacked\n";
        return;
    }
    throw target_exception("Enemy minion \nor player");
}


void minion::attack(minion *target) {
    target->health -= power;
    health -= target->power;
    // both cards damage each-other
}

//SFML

void minion::draw_details(sf::RenderWindow &window) {
    sf::FloatRect bounds = card_sprite.getGlobalBounds();

    float new_x = bounds.position.x + bounds.size.x * 0.11f;
    float new_y = bounds.position.y + bounds.size.y - bounds.size.y * 0.19f;
    pow_txt.setPosition({new_x, new_y});
    pow_txt.setString(std::to_string(power));
    new_x = bounds.position.x + bounds.size.x - bounds.size.x * 0.16f;
    new_y = bounds.position.y + bounds.size.y - bounds.size.y * 0.19f;
    hp_txt.setPosition({new_x, new_y});
    hp_txt.setString(std::to_string(health));

    window.draw(hp_txt);
    window.draw(pow_txt);
}


void minion::setDetailscale(const float x, const float y) {
        hp_txt.setScale({x, y});
        pow_txt.setScale({x, y});
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

void minion::displayDetails() {
    std::cout << " POW:" << power << " HP:" << health;
    std::cout << " Af:" << attackFlag << " Df:" << deployFlag;
}

card *minion::clone() {
    return new minion(*this);
}

