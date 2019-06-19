
#include "either.hpp"

using namespace fun;

struct I {
    int i;
    int p;
    static inline int pp = 0;
    I(): i{}, p{pp++} {std::cout << "ctor void I" << p << std::endl;}
    I(int i): i{i}, p{pp++} {std::cout << "ctor I" << p << std::endl;}
    ~I(){std::cout << "delete I" << p << std::endl;}
    I(I const &ii): i{ii.i}, p{pp++} {std::cout << "const &I" << p << std::endl;}
    I(I &&ii): i{ii.i}, p{pp++} {std::cout << "&& I" << p << std::endl;}
};

std::ostream &operator<<(std::ostream &os, I const &i)
{
    return os << i.i;
}


int main()
{
    either<std::string, I> e1 = {Right{}, 42};
    either<std::string, I> e2 = {Left{}, "error"};
    either<std::string, int> e3 = {Right{}, 42};

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;
}