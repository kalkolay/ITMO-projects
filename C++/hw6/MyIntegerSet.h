#ifndef HW6_MYINTEGERSET_H
#define HW6_MYINTEGERSET_H


#pragma once


#include <iostream>
#include <set>

using std::set;

class MyIntegerSet
{
public:

    MyIntegerSet(const MyIntegerSet& other);
    explicit MyIntegerSet(int);
    MyIntegerSet();

    MyIntegerSet& operator =(const MyIntegerSet& other);

    MyIntegerSet& operator +=(const MyIntegerSet& other);
    MyIntegerSet& operator +=(int);
    MyIntegerSet& operator -=(const MyIntegerSet& other);
    MyIntegerSet& operator -=(int);
    MyIntegerSet& operator *=(const MyIntegerSet& other);
    MyIntegerSet& operator /=(const MyIntegerSet& other);
    MyIntegerSet& operator %=(const MyIntegerSet& other);
    MyIntegerSet operator +(const MyIntegerSet& other);
    MyIntegerSet operator -(const MyIntegerSet& other);
    MyIntegerSet operator +() const;
    MyIntegerSet operator -() const;
    MyIntegerSet operator *(const MyIntegerSet& other);
    MyIntegerSet operator /(const MyIntegerSet& other);
    MyIntegerSet operator %(const MyIntegerSet& other);

    MyIntegerSet& operator |=(const MyIntegerSet& other);
    MyIntegerSet& operator ^=(const MyIntegerSet& other);
    MyIntegerSet& operator &=(const MyIntegerSet& other);
    MyIntegerSet operator |(const MyIntegerSet& other);
    MyIntegerSet operator ^(const MyIntegerSet& other);
    MyIntegerSet operator &(const MyIntegerSet& other);

    friend std::ostream& operator <<(std::ostream& out, const MyIntegerSet& arg);
    friend std::istream& operator >>(std::istream& in, MyIntegerSet& arg);

    MyIntegerSet &operator ++();
    const MyIntegerSet operator ++(int);  //postfix
    MyIntegerSet &operator --();
    const MyIntegerSet operator --(int);  //postfix

    bool operator <(const MyIntegerSet& rhs) const;
    bool operator >(const MyIntegerSet& rhs) const;
    bool operator <=(const MyIntegerSet& rhs) const;
    bool operator >=(const MyIntegerSet& rhs) const;

    bool operator !=(const MyIntegerSet& rhs) const;
    bool operator ==(const MyIntegerSet& rhs) const;

    MyIntegerSet& operator <<=(int);
    MyIntegerSet& operator >>=(int);
    MyIntegerSet operator <<(int);
    MyIntegerSet operator >>(int);

    int operator [](size_t) const;

    explicit operator std::string() const;

    const MyIntegerSet operator,(MyIntegerSet& v2);

private:
    set<int> mData;
};


#endif //HW6_MYINTEGERSET_H
