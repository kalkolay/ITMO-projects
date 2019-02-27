#ifndef HW7_ARRAY_H
#define HW7_ARRAY_H

#include <iostream>

template <class T>
class Array
{
public:
    explicit Array(size_t size, const T& value);
    explicit Array(size_t size);
    Array();
    Array(const Array& arg);

    Array& operator =(const Array& arg);

    const size_t size() const;

    T& operator [](const size_t ind);
    const T& operator [](const size_t ind) const;

    void clean();
    ~Array();
private:
    size_t mSize = 0;
    T* mArray;
};

template<typename T, typename F>
const T minimum(const Array<T>& arg, const F cmp);

template <typename T>
void flatten(const Array <Array<T>>& arg, std::ostream& out);

template <typename T>
void flatten(const Array<T>& arg, std::ostream& out);

#endif //HW7_ARRAY_H
