
#include "either.hpp"

using namespace fun;

int main()
{
    either<std::string, int> e1 = {Right, 42};
    either<std::string, int> e2 = {Left, "this is an error"};

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;

    if (either<std::string, int> e3 = {Right, 42}) {
        std::cout << "what is the solution ? " << e3.get() << std::endl;
    }

    if (either<std::string, int> e3 = {Left, "I don't know"}) {
        std::cout << "what is the solution ? " << e3.get() << std::endl;
    }

    {
        auto res = either<std::string, int>{Right, 42} >>= monadBind(int const &a,
        {Right, a*2};
        );

        std::cout << res << std::endl;
    }
}