
#include <iostream>
#include <assert.h>

namespace fun {

struct nothing {};

template<class T>
class maybe {
    bool b;
    T t;

public:
    maybe(void): b{false} {}
    maybe(nothing &&): b{false} {}
    maybe(T const &t): b{true}, t{t} {}
    maybe(T &&t): b{true}, t{std::forward<T>(t)} {}

    maybe(maybe const &) = delete;
    maybe &operator=(maybe const &) = delete;

    operator bool() const {return b;}

    T const &operator*() const { assert(b == true); return t; }
    T &operator*() { assert(b == true); return t; }
    T &get()  { assert(b == true); return t; }
    T const &get() const { assert(b == true); return t; }

    friend std::ostream &operator<<(std::ostream &os, maybe const &m) {
        if (m)
            return os << m.get();
        return os << "Nothing";
    }
};

}
