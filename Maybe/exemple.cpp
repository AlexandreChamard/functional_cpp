
#include "maybe.hpp"

using fun::maybe;
using fun::nothing;

maybe<int> retEvenOnly(int i)
{
    if (i % 2 == 0)
        return i;
    return nothing{};
}

int main()
{
    if (auto a = retEvenOnly(12))
        std::cout << a << std::endl;
    std::cout << retEvenOnly(13) << std::endl;
}