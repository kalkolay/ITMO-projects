#ifndef HW5_MYSTRING_H
#define HW5_MYSTRING_H


#include <ostream>

class MyString
{
public:
    explicit MyString(const char*);
    MyString(char, int);
    MyString(const MyString&);

    virtual ~MyString();

    MyString& append(const MyString&);
    MyString& append(const char*);

    MyString& operator =(const MyString&);

    friend std::ostream& operator <<(std::ostream& os, const MyString& string);

private:
    char* mData;
    int mSize;
};


#endif //HW5_MYSTRING_H
