
#include "game.hpp"



game::game() :
    p1(1), p2(2), turn_id(1), select_id(0),
    select_flag(false), selected_card(nullptr),
    Board(ResourceManager::Instance().getTexture(BOARD_TEXTURE)),
    turn_button(ResourceManager::Instance().getTexture(TURN_P1_T)),
    text_box({270.f, 100.f}),
    text(ResourceManager::Instance().getFont(FONT_DEFUALT))
{
    window.create(sf::VideoMode({1920, 1200}), "Proto-Hearthstone", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    //set board sprite scale
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = Board.getTexture().getSize();
    const float scale_x = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
    const float scale_y = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);
    Board.scale({scale_x, scale_y});

    turn_button.setPosition({static_cast<float>(window_size.x) * 0.76f,
                        static_cast<float>(window_size.y) * 0.43f});
    turn_button.setScale({0.7f, 0.7f});

    text_box.setPosition({ static_cast<float>(window_size.x) * 0.02f,
                            static_cast<float>(window_size.y) * 0.3f});
    text_box.setFillColor(sf::Color::Black);

    text.setPosition({static_cast<float>(window_size.x) * 0.03f,
                        static_cast<float>(window_size.y) * 0.31f});
    text.setCharacterSize(TEXTBOX_FONT);
    text.setString("Current turn: P1");

    p1.setStartPos(window);
    p2.setStartPos(window);
    p1.startTurn();
}

void game::init(const card *card_pool1, const int *card_freq1, const int pool_size1,
                const card *card_pool2, const int *card_freq2, const int pool_size2) {
    p1.deck_init(card_pool1, card_freq1, pool_size1);
    p2.deck_init(card_pool2, card_freq2, pool_size2);
    for (int i=0; i<3; ++i) {
        p1.drawFromDeck();
        p2.drawFromDeck();
    }
}

void game::display() {
    window.clear();
    window.draw(Board);
    window.draw(turn_button);
    window.draw(text_box);
    window.draw(text);
    p1.drawPlayer(window);
    p2.drawPlayer(window);
    window.display();
}

void game::switchTurn() {
    if (turn_id == 1) {
        turn_id = 2;
        p1.endTurn();
        p2.startTurn();
        turn_button.setTexture(ResourceManager::Instance().getTexture(TURN_P2_T));
        text.setString("Current turn: P2");
    }
    else {
        turn_id = 1;
        p2.endTurn();
        p1.startTurn();
        turn_button.setTexture(ResourceManager::Instance().getTexture(TURN_P1_T));
        text.setString("Current turn: P1");
    }
}

void game::selectCard(const auto mouse_pos) {
    if (turn_id == 1) {
        selected_card = p1.selectCard(mouse_pos);
        select_id = 1;
    }
    else if (turn_id == 2) {
        selected_card = p2.selectCard(mouse_pos);
        select_id = 2;
    }

    if (selected_card != nullptr) {
        select_flag = true;
        selected_card->set_selectFlag(true);
        text.setString("Selected Card!");
        std::cout << *selected_card << '\n';
    }
    else {
        text.setString("no card clicked!");
    }
}

void game::handle_select(const auto mouse_pos) {
    selected_card->set_selectFlag(false); //orice se intampla, nu mai e selectata dupa

    if (selected_card->check_deployFlag() == false) {
        //if selected card is in a hand
        if (select_id == 1) {
            if (p1.getBoardBounds().contains(mouse_pos)) {
                p1.playCard(selected_card);
            }
        }
        else {
            if (p2.getBoardBounds().contains(mouse_pos)) {
                p2.playCard(selected_card);
            }
        }
    }
    else {
        //if selected card is on a board
        card *target;
        //TODO: eventual fa cu exceptii in loc de nullptr
        if (select_id == 1) {
            target = p2.selectCard(mouse_pos);
            if (target != nullptr)
                p1.atkMinion(p2, selected_card, target);
            else if (p2.selectPlayer(mouse_pos))
                p1.atkPlayer(p2, selected_card);
        }
        else {
            target = p1.selectCard(mouse_pos);
            if (target != nullptr)
                p2.atkMinion(p1, selected_card, target);
            else if (p1.selectPlayer(mouse_pos))
                p2.atkPlayer(p1, selected_card);
        }
    }
}


void game::handle_click(const auto mouse_pos) {
    if (turn_button.getGlobalBounds().contains(mouse_pos))
        switchTurn();
    else if (!select_flag) {
        selectCard(mouse_pos);
    }
    else { // exista o carte selectata, vezi ce faci cu ea
        handle_select(mouse_pos);
        select_flag = false;
        selected_card = nullptr;
        select_id = 0;
    }
}

void game::run() {
    while(window.isOpen()) {
        bool shouldExit = false;

        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::MouseButtonPressed>() &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ){
                const auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
                handle_click(mouse_pos);
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        this->display();
    }
}

void game::demo() {
    for (int i=0; i < 3; ++i) {
        p1.drawFromDeck();
        p2.drawFromDeck();
    }
    p1.startTurn();
    p1.playCard(0U);
    p1.endTurn();

    p2.startTurn();
    p2.playCard(0U);
    p2.endTurn();

    p1.startTurn();
    p1.atkPlayer(p2, 0U);
    p1.playCard(0U);
    p1.playCard(1);
    p1.endTurn();
    p1.startTurn();
    p1.playCard(0U);
    p1.playCard(0U);
    p1.playCard(0U);
    p1.endTurn();
    p1.startTurn();
    p1.playCard(0U);


    std::cout << p1 << '\n';
}


