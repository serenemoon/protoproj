#include "Number.h"
#include <iostream>

namespace Number {
int Add(int x, int y)
{
    std::cout << "Using Non-Template int Add(int, int)" << std::endl;
    return x + y;
}
} /* Number  */ 
