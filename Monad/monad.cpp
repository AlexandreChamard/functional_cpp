
#include "monad.hpp"

maybe<int> mult10(int i){return {i*10};}

int main()
{
    { /* try to bind Just 42 */
        maybe<int> mi = retMonad<maybe>(42);

        std::cout << mi << std::endl;
        std::cout << (mi >>= retMonad<maybe>) << std::endl;
    }
    { /* try to bind Nothing */
        maybe<int> mi;

        std::cout << mi << std::endl;
        std::cout << (mi >>= retMonad<maybe>) << std::endl;
    }
    { /* compute 42 with monadic form */
        auto res =
            maybe<int>(4) >>= monadBind(int x,
            mult10(x) >>= monadBind(int y,
            maybe<int>(2) >>= monadBind(int z,
            retMonad<maybe>(y + z);
            );););

        std::cout << res << std::endl;
    }
    { /* heavier way to to compute 42 with monadic form */
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
}
