
#include "maybe.hpp"

using namespace fun;

static maybe<int> retEvenOnly(int i)
{
    if (i % 2 == 0)
        return i;
    return nothing{};
}

static maybe<int> mult10(int i)
{
    return {i * 10};
}

int main()
{
    if (auto a = retEvenOnly(12))
        std::cout << a << std::endl;
    std::cout << retEvenOnly(13) << std::endl;

    { // try to bind Just 42 //
        maybe<int> mi = retMonad<maybe>(42);

        std::cout << mi << std::endl;
        std::cout << (mi >>= retMonad<maybe, int>) << std::endl;
    }
    { // try to bind Nothing //
        maybe<int> mi;

        std::cout << mi << std::endl;
        std::cout << (mi >>= retMonad<maybe, int>) << std::endl;
    }
    { // compute 42 with monadic form //
        auto res =
            maybe<int>(4) >>= monadBind(int x,
            mult10(x) >>= monadBind(int y,
            maybe<int>(2) >>= monadBind(int z,
            retMonad<maybe>(y + z);
            );););

        std::cout << res << std::endl;
    }
}