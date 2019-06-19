
#pragma once

#include "../Utils/storage.hpp"
#include "../Monad/monad.hpp"
#include "assert.h"

namespace fun {

enum ctor_either_right_e {Right};
enum ctor_either_left_e {Left};

template<class L, class R>
class either {

    bool empty = false;
    bool state;
    union {
        storage<L> l;
        storage<R> r;
    };

public:
    either(ctor_either_left_e, L const &_l): state{false} { new (l.ptr_ref()) L{_l}; }
    either(ctor_either_right_e, R const &_r): state{true} { new (r.ptr_ref()) R{_r}; }
    template<class ...Ts>
    either(ctor_either_left_e, Ts &&...ts): state{false} { new (l.ptr_ref()) L{std::forward<Ts>(ts)...}; }
    template<class ...Ts>
    either(ctor_either_right_e, Ts &&...ts): state{true} { new (r.ptr_ref()) R{std::forward<Ts>(ts)...}; }
    ~either() {
        if (empty == false) {
            if (state)
                r.ptr_ref()->~R();
            else
                l.ptr_ref()->~L();
        }
    }

    either(either &&e): empty{e.empty}, state{e.state} {
        assert(empty == false); // need to throw
        e.empty = true;
        if (state) {
            r.ref() = std::move(e.r.ref());
        } else {
            l.ref() = std::move(e.l.ref());
        }
    }

    either(either const &) = delete;
    either &operator=(either const &) = delete;

    operator bool() const {return state;}

    R &get() { assert(state == true); return r.ref(); } // deprecated
    R const &get() const { assert(state == true); return r.ref(); } // deprecated

    friend std::ostream &operator<<(std::ostream &os, either const &e) {
        if (e.empty == false) {
            if (e)
                return os << "Right " << e.r.ref();
            return os << "Left " << e.l.ref();
        } else {
            // need to throw
            return os << "<error : operator<< on empty either>" << std::endl;
        }
    }

    //// monad specialization ////

    template<class LL, class RR>
    either<LL, RR> operator>>=(std::function<either<LL, RR>(R const &)> const &f) const {
        if (*this) {
            return f(get());
        }
        return either<LL, RR>::failMonad();
    }

    template<class LL, class RR>
    either<LL, RR> operator>>=(either<LL, RR>(*f)(R const &)) const {
        if (*this) {
            return f(get());
        }
        return either<LL, RR>::failMonad();
    }

    static either<L, R> retMonad(R const &r) {
        return {Right, r};
    }
    template<class ...Ts>
    static either<L, R> retMonad(Ts &&...ts) {
        return {Right, std::forward<Ts>(ts)...};
    }

    static either<L, R> failMonad(L const &l = L{}) {
        return {Left, l};
    }
    template<class ...Ts>
    static either<L, R> failMonad(Ts &&...ts) {
        return {Left, std::forward<Ts>(ts)...};
    }

};

}