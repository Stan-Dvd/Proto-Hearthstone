#include "game.hpp"
#include "card_factory.hpp"
#include "exceptions.hpp"


game::game() : p{nullptr, nullptr},
               turn_id(0),
               select_flag(false), selected_card(nullptr),
               Board(ResourceManager::Instance().getTexture(BOARD_TEXTURE)),
               turn_button(ResourceManager::Instance().getTexture(TURN_P1_T)),
               text_box({270.f, 100.f}),
               message(ResourceManager::Instance().getFont(FONT_DEFUALT))
{
    window.create(sf::VideoMode({1920, 1200}), "Proto-Hearthstone", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    //set board sprite scale
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = Board.getTexture().getSize();
    const float scale_x = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
    const float scale_y = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);
    Board.scale({scale_x, scale_y});

    //setup turn button
    turn_button.setPosition({
        static_cast<float>(window_size.x) * 0.76f,
        static_cast<float>(window_size.y) * 0.43f
    });
    turn_button.setScale({0.7f, 0.7f});

    //setup text box
    text_box.setPosition({
        static_cast<float>(window_size.x) * 0.02f,
        static_cast<float>(window_size.y) * 0.3f
    });
    text_box.setFillColor(sf::Color::Black);

    //setup text
    message.setPosition({
        static_cast<float>(window_size.x) * 0.03f,
        static_cast<float>(window_size.y) * 0.31f
    });
    message.setCharacterSize(TEXTBOX_FONT);
    message.setString("Current turn: P1");
}

game::~game() {
    std::cout << "DelGame\n";
    if (selected_card != nullptr) {
        delete selected_card;
    }
    delete p[0];
    delete p[1];
}


void game::init(playerBuilder *p1Builder, playerBuilder *p2Builder) {
    p1Builder->buildPlayer(1);
    p2Builder->buildPlayer(2);
    p[0] = p1Builder->getPlayer();
    p[1] = p2Builder->getPlayer();

    p[0]->setStartPos(window);
    p[1]->setStartPos(window);

    std::cout << "drawing first cards";
    for (int i = 0; i < 3; ++i) {
        // players start with 3 cards from their deck
        p[0]->drawFromDeck();
        p[1]->drawFromDeck();
    }
    p[1]->drawFromDeck();
    p[0]->startTurn();
}

//OLD init
void game::init(const CardTypes *card_pool1, const int *card_freq1, const int pool_size1,
                const CardTypes *card_pool2, const int *card_freq2, const int pool_size2) {
    p[0]->init(card_pool1, card_freq1, pool_size1, Hunters_Gift);
    p[1]->init(card_pool2, card_freq2, pool_size2, Eldritch_Blast);
    p[0]->setStartPos(window);
    p[1]->setStartPos(window);
    std::cout << "drawing first cards";
    for (int i=0; i<3; ++i) { // players start with 3 cards from their deck
        p[0]->drawFromDeck();
        p[1]->drawFromDeck();
    }
    p[1]->drawFromDeck();
    p[0]->startTurn();
}

void game::display() {
    window.clear();
    window.draw(Board);
    window.draw(turn_button);
    window.draw(text_box);
    window.draw(message);
    p[0]->drawPlayer(window);
    p[1]->drawPlayer(window);
    window.display();
}

void game::switchTurn() {
    p[turn_id]->endTurn();
    try {
        p[!turn_id]->startTurn();
    } catch (GameMessage &e) {
        std::cout << "from swTurn:\n" << e.what();
        message.setString(e.what());
    }
    turn_button.setTexture(ResourceManager::Instance().getTexture(!turn_id ? TURN_P2_T : TURN_P1_T));
    message.setString(!turn_id ? "Current turn: P2" : "Current turn: P1");
    turn_id = !turn_id;

    //RIP 14 linii de if-uri
}

void game::selectCard(const auto mouse_pos) {
    //player whose turn it is, selects a card
    selected_card = p[turn_id]->selectCard(mouse_pos);

    if (selected_card != nullptr) {
        select_flag = true;
        selected_card->set_selectFlag(true);
        message.setString("Selected Card!");
        selected_card->display(1);
    } else {
        message.setString("no card clicked!");
    }
}


void game::handle_click(const auto mouse_pos) {
    if (turn_button.getGlobalBounds().contains(mouse_pos)) // turn button is clicked
        switchTurn();
    else if (!select_flag) {
        //if no card is selected, select a card
        selectCard(mouse_pos);
    } else {
        // if a card is selected, handle click
        selected_card->set_selectFlag(false);
        select_flag = false;
        //whatever happens, deselect card. otherwise gets way too complicated
        try {
            selected_card->action(p, turn_id, mouse_pos);
            //card handles the click, ie
            //if something friendly or enemy needs to be selected, what happens on selection, etc

        } catch (GameMessage &e) {
            std::cout << "from action:\n" << e.what() << '\n';
            message.setString(e.what()); //display message on screen
        } //fara catch aici nu ruleaza ce e mai jos and that's really important

        selected_card = nullptr;
    }
}

void game::run() {
    while (window.isOpen()) {
        bool shouldExit = false;

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                const auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
                //need this to be float for bound checks
                try {
                    handle_click(mouse_pos);
                } catch (GameMessage &e) {
                    std::cout << "from run:\n" << e.what();
                    message.setString(e.what()); //display message on screen
                }
            } else if (event->is<sf::Event::KeyPressed>()) {
                const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }
        }
        if (shouldExit) {
            window.close();
            std::cout << "Fereastra a fost inchisa (shouldExit == true)\n";
            break;
        }

        this->display();
    }
}
