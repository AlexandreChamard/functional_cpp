
#include "maybe.hpp"

using namespace fun;

struct I {
    int _i;

    operator int() const {return _i;}

    ~I() {std::cerr << "i detor" << std::endl;}
    I(): _i{} {std::cerr << "i ctor void" << std::endl;}
    I(int i): _i{i} {std::cerr << "i ctor int" << std::endl;}
    I(I const &i): _i{i._i} {std::cerr << "i ctor const&" << std::endl;}
    I(I &&i): _i{i._i} {std::cerr << "i ctor &&" << std::endl;}
    I&operator=(I const&i) {*this = i;std::cerr << "i = const &" << std::endl;}
    I&operator=(I&&i) {*this = i;std::cerr << "i = &&" << std::endl;}
};
std::ostream &operator<<(std::ostream &os, I const &i) { return os << i._i; }

static maybe<I> mult10(I const &i)
{
    return i * 10;
}

maybe<I> retEvenOnly(int const &i)
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
            maybe<I>(4) >>= monadBind(I const &x,
            mult10(x) >>= monadBind(I const &y,
            maybe<I>(2) >>= monadBind(I const &z,
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
        std::cout << "first try with Nothing : ";
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