
#pragma once

#include <iostream>
#include <assert.h>
#include "../Monad/monad.hpp"
#include "../Utils/storage.hpp"

namespace fun {

enum nothing_e {Nothing};

template<class T>
class maybe {
    bool state;
    storage<T> t;

public:
    maybe(nothing_e): state{false} {}
    maybe(T const &_t): state{true} {
        new (t.ptr_ref()) T{_t};
    }
    maybe(T &&_t): state{true} {
        new (t.ptr_ref()) T{std::forward<T>(_t)};
    }
    template<class ...Ts>
    maybe(Ts &&...ts): state{true} {
        new (t.ptr_ref()) T{std::forward<Ts>(ts)...};
    }

    ~maybe() {
        if (state == true) 
            t.ptr_ref()->~T();
    }

    maybe(maybe const &) = delete;
    maybe &operator=(maybe const &) = delete;
    maybe(maybe &&) = delete;
    maybe &operator=(maybe &&) = delete;

    operator bool() const { return state; }

    friend std::ostream &operator<<(std::ostream &os, maybe const &m) {
        if (m)
            return os << m.t.ref();
        return os << "Nothing";
    }

    //// monad specialization ////

    template<typename U>
    maybe<U> operator>>=(std::function<maybe<U>(T const &)> f) const {
        if (*this) {
            return f(t.ref());
        }
        return maybe<U>::failMonad();
    }
    template<typename U>
    maybe<U> operator>>=(maybe<U>(*f)(T const &)) const {
        if (*this) {
            return f(t.ref());
        }
        return maybe<U>::failMonad();
    }

    static maybe<T> retMonad(T t) {
        return {t};
    }

    static maybe<T> failMonad(std::string const & = "") {
        return Nothing;
    }
};

}