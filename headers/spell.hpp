#ifndef SPELL_HPP
#define SPELL_HPP

#include "card.hpp"

class spell : public card {
private:
    sf::Text name_txt;

public:
    spell(const int cost, std::string name = "Placeholder", std::string description = "Placeholder",
             std::string texture = PLACEHOLDER_SPELL_TEXTURE);
    spell(const spell& model);

    void action(player *p, bool owner, sf::Vector2f) override = 0;

    void setDetailscale(const float x, const float y) override;
    void draw_details(sf::RenderWindow &window) override;
    void displayDetails() override;

    card* clone() override = 0;

};

#endif //SPELL_HPP
