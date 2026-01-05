#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton {
public:
    Singleton(Singleton const &) = delete;
    Singleton& operator=(Singleton const &) = delete;
    static T& Instance()
    {
        static T instance;
        return instance;
    }
protected: // pentru a putea fi accesate de clasa derivata
    Singleton() = default;
    ~Singleton() = default;
};


#endif //SINGLETON_HPP
