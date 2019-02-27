#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <iostream>

template<class T>
class Array
{
public:
    explicit Array(size_t size = 0);
    Array(const Array& a);
    Array(Array&& a);

    Array& operator =(const Array& a);
    Array& operator =(Array&& a);

    size_t size() const;

    T& operator [](size_t i);
    const T& operator [](size_t i) const;

    ~Array();
private:
    size_t mSize;
    T*     mData;
};

#endif //ARRAY_ARRAY_H
