
#include <utility>
#include <iostream>
#include <functional>

// struct monad {
//     template<class T>
//     void ret();

//     template<class T, class U, class Tt>
//     U bind(T const &t, U (*)(Tt const &)) {
//         if (t.fail())
//     }

// };

template<template<typename> typename Monad, typename T = int>
Monad<T> retMonad(T t)
{
    return {t};
}

template<template<typename> typename Monad, typename T = int>
Monad<T> failMonad()
{
    return {};
}

template<typename U, typename T, template<typename> typename Monad>
Monad<U> operator>>=(Monad<T> t, std::function<Monad<U>(T)> f)
{
    if (t) {
        return f(t.get());
    }
    return failMonad<Monad>();
}

template<class T>
class maybe {
    bool    state;
    T       t;

public:
    operator bool() const {return state;}

    maybe(void): state{false} {}
    maybe(T const &t): state{true}, t{t} {}
    maybe(T &&t): state{true}, t{std::forward<T>(t)} {}

    T const &get(void) const {return t;};
    T &get(void) {return t;};

    template<class U>
    maybe<U> bind(maybe<U> (*f)(T const &)) {
        if (t) {
            return f(t);
        }
        return {};
    }
};

template<class T>
std::ostream &operator<<(std::ostream &os, maybe<T> m)
{
    if (m)
        return os << m.get();
    return os << "Nothing";
}