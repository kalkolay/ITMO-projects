#include <iostream>
#include "MyString.h"

using std::cout;
using std::endl;

int main()
{
    cout << "Hello, World!" << endl;
    const int MAX_SIZE = 1000;
    MyString str("app");
    MyString str1("lol");
    MyString str2("lol");
    MyString str3("lol");
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        str1.append(str);
        str.append("al");
        str2 = str;
        str3 = MyString(str2);
    }
    cout << "heh";

    return 0;
}