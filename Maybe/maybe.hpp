
#include <iostream>
#include <assert.h>
#include "../Monad/monad.hpp"

#pragma once

namespace fun {

struct nothing {};

template<class T>
class maybe {
    bool state;
    T t;

public:
    maybe(void): state{false} {}
    maybe(nothing &&): state{false} {}
    maybe(T const &t): state{true}, t{t} {}
    maybe(T &&t): state{true}, t{std::forward<T>(t)} {}

    maybe(maybe const &) = delete;
    maybe &operator=(maybe const &) = delete;

    operator bool() const {return state;}

    T const &operator*() const { return t.get(); }
    T &operator*() { return t.get(); }
    T &get() { assert(state == true); return t; }
    T const &get() const { assert(state == true); return t; }

    friend std::ostream &operator<<(std::ostream &os, maybe const &m) {
        if (m)
            return os << m.get();
        return os << "Nothing";
    }

    //// monad specialization ////

    template<typename U>
    maybe<U> operator>>=(std::function<maybe<U>(T)> f) {
        if (*this) {
            return f(get());
        }
        return maybe<U>::failMonad();
    }
    template<typename U>
    maybe<U> operator>>=(maybe<U>(*f)(T)) {
        if (*this) {
            return f(get());
        }
        return maybe<U>::failMonad();
    }

    static maybe<T> retMonad(T t) {
        return {t};
    }

    static maybe<T> failMonad(std::string const & = "") {
        return {};
    }
};

}