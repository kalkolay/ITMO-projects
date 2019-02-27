#include "MyString.h"

MyString::MyString(const char* inStr)
{
    mSize = 0;
    while (inStr[mSize] != '\0')
        mSize++;
    mData = new char[mSize + 1];
    for (int i = 0; i < mSize + 1; ++i)
        mData[i] = inStr[i];
}

MyString::MyString(char c, int length)
{
    mSize = length;
    mData = new char[mSize + 1];
    for (int i = 0; i < mSize; ++i)
        mData[i] = c;
    mData[mSize] = '\0';
}

std::ostream& operator <<(std::ostream& os, const MyString& string)
{
    os << string.mData;
    return os;
}

MyString::~MyString()
{
    delete[] mData;
}

MyString& MyString::append(const MyString& app)
{
    char* buffer = new char[mSize + app.mSize + 1];
    for (int i = 0; i < mSize; ++i)
        buffer[i] = mData[i];
    for (int j = 0; j < app.mSize + 1; ++j)
        buffer[mSize + j] = app.mData[j];
    delete[] mData;
    mData = buffer;
    mSize += app.mSize;
    return *this;
}

MyString::MyString(const MyString& original)
{
    mSize = original.mSize;
    mData = new char[mSize + 1];
    for (int i = 0; i < mSize + 1; ++i)
        mData[i] = original.mData[i];
}

MyString& MyString::operator =(const MyString& original)
{
    mSize = original.mSize;
    delete[] mData;
    mData = new char[mSize + 1];
    for (int i = 0; i < mSize + 1; ++i)
        mData[i] = original.mData[i];
    return *this;
}

MyString& MyString::append(const char* app)
{
    MyString myString(app);
    return append(myString);
}