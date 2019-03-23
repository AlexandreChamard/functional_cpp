
#include "monad.hpp"

#define f(bla) std::function(bla)

maybe<int> mult10(int i){return {i*10};}

int main()
{
    // {
    //     maybe<int> mi = retMonad<maybe>(42);

    //     std::cout << mi << std::endl;
    //     std::cout << (mi >>= retMonad<maybe>) << std::endl;
    // }
    // {
    //     maybe<int> mi;

    //     std::cout << mi << std::endl;
    //     std::cout << (mi >>= retMonad<maybe>) << std::endl;
    // }
    {
        auto res = [] {
            if (maybe<int> a = 4) {
                return [&](int x){
                    if (auto c = mult10(x))
                        return [&](int y){
                            maybe<int> c = 2;
                            if (c) {
                                return [&](int z){
                                    return retMonad<maybe>(y + z);
                                }(c.get());
                            }
                            return failMonad<maybe>();
                        }(c.get());
                        return failMonad<maybe>();
                }(a.get());
                return failMonad<maybe>();
            }
        }();
        std::cout << res << std::endl;
    }
    {
        auto res =
            maybe<int>(4) >>= f([&](int x){return
            mult10(x) >>= f([&](int y) {return
            maybe<int>(2) >>= f([&](int z){return
            retMonad<maybe>(y + z);
            });});});

        std::cout << res << std::endl;
    }
}
