
#include <utility>
#include <iostream>
#include <functional>

#define monadBind(arg, core) std::function([&](arg){return core})

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

template<typename U, typename T, template<typename> typename Monad>
Monad<U> operator>>=(Monad<T> t, Monad<U> (*f)(T))
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

};

template<class T>
std::ostream &operator<<(std::ostream &os, maybe<T> m)
{
    if (m)
        return os << m.get();
    return os << "Nothing";
}