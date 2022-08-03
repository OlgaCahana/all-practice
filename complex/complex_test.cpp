#include <cstring>
#include <iostream>

#include "complex.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    Complex c1(2,3);
    Complex c2(1,4);

    cout << c1;
    cout << c2;

    Complex c3 = c1 + c2;
    Complex c4 = c3 - c2;

    cout << c3;
    cout << c4;

    if(c4 == c1) cout << "test passed: c4 == c1 " << endl;

    Complex c5;
    cin >> c5;
    cout << c5;

    if(c5 != c1) cout << "test passed: c5 != c1" << endl;
        else cout << "test failed" << endl;

    c5 = c1;

    if(c5 == c1) cout << "test passe: c5 == c1" << endl;
        else cout << "test failed" << endl;

    c3 += c4;
    cout << c3;

    c3 -= c3;
    cout << c3;

    c2 *= c2;
    cout << c2;

    cout << c2 + 3;
    

    return 0;
}