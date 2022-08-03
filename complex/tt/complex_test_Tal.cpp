#include <iostream>

#include "complex.hpp"

using namespace std;

int main(void)
{
    using namespace ilrd;
    Complex c1(11, 10), c2(5), c3;

    cout << "Enter the value of object : " << endl;
    cin >> c3;
    cout << "First Complex : " << c1 << endl;
    cout << "Second Complex :" << c2 << endl;
    cout << "Third Complex :" << c3 << endl;

    // tests == !=
    std::cout << "c1 == c2: (expected 0) , result: " << (c1 == c2) << std::endl;
    std::cout << "c1 != c2: (expected 1) , result:" << (c1 != c2) << std::endl;
    std::cout << "c2 == c2: (expected 1) , result:" << (c2 == c2) << std::endl;
    std::cout << "c2 != c2: (expected 0) , result:" << (c2 != c2) << std::endl;

    std::cout << "c1 + c2: (expected (16, 10)) , result:" << (c1 + c2) << std::endl;
    std::cout << "c1 - c2: (expected (6, 10)) , result:" << (c1 - c2) << std::endl;

    std::cout << "c1 * c2: (expected (55, 50)) , result:" << (c1 * c2) << std::endl;
    std::cout << "c1 / c2: (expected (55, 2)) , result:" << (c1 / c2) << std::endl;

    c1 += c2;
    std::cout << "c1 + c2: (expected (16, 10)) , result:" << c1 << std::endl;

    c1 -= c2;
    std::cout << "c1 - c2: (expected (11, 10)) , result:" << c1 << std::endl;

    c1 *= c2;
    std::cout << "c1 * c2: (expected (55, 50)) , result:" << c1 << std::endl;

    (c1 /= c2);
    std::cout << "c1 / c2: (expected (275, 10)) , result:" << c1 << std::endl;

    return 0;
}