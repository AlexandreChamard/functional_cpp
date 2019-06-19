
#pragma once

#include "../Utils/storage.hpp"
#include "../Monad/monad.hpp"
#include "assert.h"

namespace fun {

struct Right {};

struct Left {};

template<class L, class R>
class either {

    bool state;
    union {
        storage<L> l;
        storage<R> r;
    };

public:
    either(Left, L const &_l): state{false} { new (l.ptr_ref()) L{_l}; }
    either(Left, L &&_l): state{false} { new (l.ptr_ref()) L{std::forward<L>(_l)}; }
    either(Right, R const &_r): state{true} { new (r.ptr_ref()) R{_r}; }
    either(Right, R &&_r): state{true} { new (r.ptr_ref()) R{std::forward<R>(_r)}; }
    ~either() {
        if (state)
            r.ptr_ref()->~R();
        else
            l.ptr_ref()->~L();
    }

    either(void) = delete;
    either(either const &) = delete;
    either &operator=(either const &) = delete;

    operator bool() const {return state;}

    R &get() { assert(state == true); return r.ref(); }
    R const &get() const { assert(state == true); return r.ref(); }

    friend std::ostream &operator<<(std::ostream &os, either const &e) {
        if (e)
            return std::cout << "Right " << e.r.ref();
        return std::cout << "Left " << e.l.ref();
    }

    //// monad specialization ////

    // template<class L, class R>
    // either<L, R> operator>>=(std::function<either<L, R>(Right)> f) {
    //     if (*this) {
    //         return f(get());
    //     }
    //     return maybe<U>::failMonad();
    // }
    // template<typename U>
    // maybe<U> operator>>=(maybe<U>(*f)(T)) {
    //     if (*this) {
    //         return f(get());
    //     }
    //     return maybe<U>::failMonad();
    // }

    // static maybe<T> retMonad(T t) {
    //     return {t};
    // }

    // static maybe<T> failMonad(std::string const & = "") {
    //     return {};
    // }

};

}