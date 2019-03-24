
#pragma once

#include <utility>
#include <iostream>
#include <functional>

namespace fun {

#define monadBind(arg, core) std::function([&](arg){return core})

template<template<class> class Monad, class ...Ts>
Monad<Ts...> retMonad(Ts ...ts)
{
    return Monad<Ts...>::retMonad(std::forward<Ts>(ts)...);
}

// template<template<class> class Monad, class ...Ts>
// Monad<Ts...> failMonad(std::string const &msg = "")
// {
//     return Monad<Ts...>::failMonad(msg);
// }

template<class U, class Monad, class T>
U operator>>=(Monad const &t, std::function<U (T)> f)
{
    t.operator>>=(f);
}

template<class U, class Monad, class T>
U operator>>=(Monad const &t, U (*f)(T))
{
    t.operator>>=(f);
}

}