#include "spell.hpp"

spell::spell(const int cost, std::string name, std::string description, std::string texture):
                card(cost, texture),
                name_txt(ResourceManager::Instance().getFont(FONT_DEFUALT))
{
    name_txt.setString(name);
    name_txt.setCharacterSize(FONT_SIZE * NAME_SCALE);
    flavor_txt.setString(description);
}

spell::spell(const spell &model) : card(model), name_txt(model.name_txt){};


void spell::setDetailscale(const float x, const float y) {
    name_txt.setScale({x, y});
}

void spell::draw_details(sf::RenderWindow &window) {
    sf::FloatRect bounds = card_sprite.getGlobalBounds();

    float new_x = bounds.position.x + bounds.size.x * 0.2f;
    float new_y = bounds.position.y + bounds.size.y * 0.465f;
    name_txt.setPosition({new_x, new_y});

    window.draw(name_txt);
}

void spell::displayDetails() {
    std::cout << " Spell name: " << name_txt.getString().toAnsiString();
}


