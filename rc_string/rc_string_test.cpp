#include <cstring>
#include <iostream>

#include "rc_string.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    RCString s1("Hey");
    cout << s1.Length() << endl;
    cout << s1.Cstr() << endl;

    RCString s2(s1);
    cout << s2.Length() << endl;
    cout << s2 << endl;

    RCString s3("Hello");
    cout << s3.Length() << endl;
    cout << s3 << endl;

    if(s3 < s2) cout << "s3 < s2" << endl;
    if(s2 > s3) cout << "s2 > s3" << endl;

    s3 = s2;
    cout << s3.Length() << endl;
    cout << s3.Cstr() << endl;

    if(s3 == s2) cout << "s3 == s2" << endl;
    if(s3 == "Hey") cout << "s3 == Hey" << endl;
    if("Hey" == s2) cout << "Hey == s2" << endl;
   // s2[2] = 'k';
    cout << s2 << endl;

    RCString a1 = "aa";
    RCString a2("bb");
    RCString a3("cc");

    (a1 = a2) = a3;

    cout << a1 << a2 << a3 << endl;

    int i = s2[0];
    cout << i << endl;

    cout << "end" << endl;

    return 0;
}