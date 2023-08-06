#include <iostream>

#include "Math.h"

int main()
{
    math::Math math;
    std::cout << "1 + 2 = " << math.add(1, 2) << std::endl;
    return 0;
}