#include <iostream>
#include <vector>
#include <list>
#include "Number.h"
#include "Sdo.h"
#include "TypeName.h"

int g_q = 1;

using DP = Sdo::DataPairs<0x24,0x35,0x46,0x57,0x68,0x79,0x8A>;
void Test() {
    g_q = DP::ValueOfKey(g_q);
}

int main(int argc, char *argv[])
{
    int a[3];
    std::cout << "Hello World!" << std::endl;
    std::cout << Number::Add(3, 4) << std::endl;

    print_t(std::vector<int>);
    print_t(std::list<int>);
    print_t(decltype((a)));
    print_t(decltype(a));
    print_v(std::list<int>{});
    print_v(std::string{});

    Test();
    return 0;
}
