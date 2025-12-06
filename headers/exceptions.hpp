#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class GameMessage : public std::exception {
private:
    std::string text;
public:
    GameMessage(const std::string &text) { this->text = text; }
    ~GameMessage() = default;
    const char* what() const noexcept override { return text.c_str(); }
};

class ready_exception : public GameMessage {
public:
    ready_exception()
        :GameMessage("Minion not ready \nor has already attacked"){};
};

class mana_exception : public GameMessage {
public:
    mana_exception(const int dif)
        :GameMessage("Not enough mana! \nNeed " + std::to_string(dif) + " more!"){};
};

class target_exception : public GameMessage {
public:
    target_exception(const std::string &target)
        :GameMessage("Select " + target + "!"){};
};

class overflow_exception : public GameMessage { //hand/board full
public:
    overflow_exception(const std::string &object):
        GameMessage(object + " full!"){};
};

class empty_exception : public GameMessage {//deck empty dar hai sa fie general ig?
public:
    empty_exception(const std::string &object = "Deck")
        :GameMessage(object + " empty!"){};
};



#endif EXCEPTIONS_HPP
