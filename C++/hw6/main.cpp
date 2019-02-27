#include "MyIntegerSet.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    MyIntegerSet set1(5);
    set1 += 6;
    MyIntegerSet set2(2);
    set2 += 4;

    MyIntegerSet set3 = set1 * set2;
    cout << set3;

    set3 += set2;
    cout << set3;

    set3 -= set3;
    cout << set3;

    set3++;
    ++set3;
    set3++;
    cout << set3;

    set3--;
    cout << set3;

    set3+=6;
    set3+=8;
    set3+=18;
    cout << set3;

    set3++;
    set3++;
    cout << set3;

    set3--;
    cout << set3;

    set3^=set2;
    cout << set3;

    return 0;
}