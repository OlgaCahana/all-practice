#include <cstring>
#include <iostream>

#include "bitset.hpp"

using namespace std;
using namespace hrd22;

int main()
{
    BitSet<100> bs1;
    BitSet<100> bs2;
    BitSet<200> bs3;

    if(bs1 == bs2)
        std::cout << "Test passed" << endl;
    else
        std::cout << "Test failed" << endl;

    //Compilation error:
    // if(bs1 == bs3) 
    //     std::cout << "Test failed" << endl;

    bs1 &= bs2;
    if (bs1 == bs2)
        std::cout << "Test passed" << endl;

    bs1 |= bs2;
    if (bs1 == bs2)
        std::cout << "Test passed" << endl;

    /***************SetBit GetBit in public to run those tests***********/    

    // bs1.SetBit(true, 99);

    // if (bs1.GetBit(99) == true) 
    //     std::cout << "Test passed" << endl;
    // else 
    //     std::cout << "Test failed" << endl;

    // if (bs1.GetBit(0) == false) 
    //     std::cout << "Test passed" << endl;
    // else 
    //     std::cout << "Test failed" << endl;

/***************************************************************************/
    bs1[99] = true;

    if (bs1[99] == true) 
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;

    if (bs1[0] == false) 
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;

    std::cout << bs1 << endl;
    std::cout << bs1.CountSetBits() << endl;
    
    const BitSet<100> bs4(bs1);
    if (bs4[99] == true)
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;

    if (bs4[0] == false)
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;


    if(bs1 == (bs1 &= bs4))
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;

    if (bs2 == (bs1 ^=bs4))
        std::cout << "Test passed" << endl;
    else 
        std::cout << "Test failed" << endl;

    std::cout << bs1.CountSetBits() << endl;
    bs1[0] = true;
    bs1[99] = true;
    bs1[97] = true;
   // bs1[100] = true;

    std::cout << bs1.CountSetBits() << endl;



    return 0;
}