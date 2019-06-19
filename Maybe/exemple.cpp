
#include "maybe.hpp"

using namespace fun;

static maybe<int> mult10(int const &i)
{
    return i * 10;
}

maybe<int> retEvenOnly(int const &i)
{
    if (i % 2 == 0)
        return i;
    return Nothing;
}

template<class T>
void print_maybe(maybe<T> const &mt)
{
    std::cout << mt << std::endl;
}

int main()
{
    std::cout << "FIRST" << std::endl;
    if (auto a = retEvenOnly(12))
        std::cout << a << std::endl;
    std::cout << "SECOND" << std::endl;
    std::cout << retEvenOnly(13) << std::endl;

    auto res =
            maybe<int>(4) >>= monadBind(int const &x,
            mult10(x) >>= monadBind(int const &y,
            maybe<int>(0.3) >>= monadBind(int const &z,
            retMonad<maybe>(y + z);
            );););

    std::cout << res << std::endl;

    { // bad way to use monad, but it's work
        maybe<std::string> mi = "bonjour";
        maybe<std::string> mii = Nothing;

        auto f = std::function([](std::string const &s)->maybe<std::string> {
            std::cout << "it's printing \"" << s << '"' << std::endl;
            return "";
        });
        std::cout << "first try with string : ";
        mi >>= f;
        std::cout << "second try with Nothing : ";
        mii >>= f;
        std::cout << std::endl;
    }

    {
        std::string str = "test";
        maybe<std::string> mi = str;
        maybe<std::string> mii = std::move(str);

        std::vector<maybe<std::string>> vm;

        vm.push_back(std::move(mi));
        vm.push_back(std::move(mii));

        std::cout << "str = " << str << std::endl;
        std::cout << "mi = " << mi << std::endl;
        std::cout << "mii = " << mii << std::endl;

        for (auto &e : vm)
            std::cout << "vec = " << e << std::endl;
    }

}