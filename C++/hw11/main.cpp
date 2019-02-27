#include "BadFromStringException.h"
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;

template<class T>
T from_string(const string& arg)
{
    std::istringstream stringStream(arg);

    if (typeid(T).name() != typeid(string).name())
        stringStream >> std::noskipws;

    T result;
    stringStream >> result;

    if (stringStream.fail() || (stringStream.get() && !stringStream.eof()))
    {
        string errMessage;
        errMessage = R"(Error converting from "string" to ")" + string(typeid(T).name()) + "\"";
        throw BadFromStringException(errMessage);
    }

    return result;
}

int main()
{
    cout << "__________PARSINGS__________\n";
    try
    {
        string s1("123");
        cout << "Expected: " << "123, " << "actual: " << from_string<int>(s1) << endl;
        cout << "Expected: " << "123.5, " << "actual: " << from_string<double>(s1) + 0.5 << endl;
        cout << "Expected: " << "123, " << "actual: " << from_string<string>(s1) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }

    try
    {
        string s1("12.3");
        cout << "Expected: " << "12.3, " << "actual: " << from_string<double>(s1) << endl;
        cout << "Expected: " << "12.3, " << "actual: " << from_string<string>(s1) << endl;
        cout << "Expected: " << "error(to int), " << "actual: " << from_string<int>(s1) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }

    try
    {
        string s1("abc");
        cout << "Expected: " << "abc, " << "actual: " << from_string<string>(s1) << endl;
        cout << "Expected: " << "error(to double), " << "actual: " << from_string<double>(s1) << endl;
        cout << "Expected: " << "error(to int), " << "actual: " << from_string<int>(s1) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }
    cout << endl ;

    cout << "__________WHITESPACES__________\n";
    try
    {
        string s(" abc");
        cout << "Expected: " << "error(to double), " << "actual: " << from_string<double>(s) << endl;
    }
    catch (BadFromStringException& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        string s("12.0 ");
        cout << "Expected: " << "error(to double), " << "actual: " << from_string<double>(s) << endl;
    }
    catch (BadFromStringException& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        string s(" 12 ");
        cout << "Expected: " << "error(to int), " << "actual: " << from_string<int>(s) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }

    try
    {
        string s(" 13.6");
        cout << "Expected: " << "error(to double), " << "actual: " << from_string<double>(s) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }

    try
    {
        string s(" 1");
        cout << "Expected: " << "error(to int), " << "actual: " << from_string<int>(s) << endl;
    }
    catch (BadFromStringException& e)
    {
        cout << e.what() << '\n';
    }

    return 0;
}