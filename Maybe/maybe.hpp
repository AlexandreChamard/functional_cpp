
#pragma once

#include <iostream>
#include <assert.h>
#include "../Monad/monad.hpp"
#include "../Utils/storage.hpp"

namespace fun {

struct nothing {};

template<class T>
class maybe {
    bool state;
    storage<T> t;

public:
    maybe(void): state{false} {}
    maybe(nothing): state{false} {}
    maybe(T const &_t): state{true} { new (t.ptr_ref()) T{_t}; }
    maybe(T &&_t): state{true} { new (t.ptr_ref()) T{std::forward<T>(_t)}; }

    ~maybe() { if (state) t.ptr_ref()->~T(); }

    maybe(maybe const &) = delete;
    maybe &operator=(maybe const &) = delete;

    operator bool() const { return state; }

    T const &operator*() const { return t.get(); }
    T &operator*() { return t.get(); }
    T &get() { assert(state == true); return t.ref(); }
    T const &get() const { assert(state == true); return t.ref(); }

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