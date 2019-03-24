
#include <utility>
#include <iostream>
#include <functional>

#pragma once

#define monadBind(arg, core) std::function([&](arg){return core})

template<template<typename> typename Monad, typename T = int>
Monad<T> retMonad(T t)
{
    return Monad<T>::retMonad(std::forward<T>(t));
}

template<template<typename> typename Monad, typename T = int>
Monad<T> failMonad(std::string const &msg = "")
{
    return Monad<T>::failMonad(msg);
}

template<typename U, typename T, template<typename> typename Monad>
Monad<U> operator>>=(Monad<T> const &t, std::function<Monad<U>(T)> f)
{
    t.operator>>=(f);
}

template<typename U, typename T, template<typename> typename Monad>
Monad<U> operator>>=(Monad<T> const &t, Monad<U> (*f)(T))
{
    t.operator>>=(f);
}
