#include "MyIntegerSet.h"
#include <sstream>

using std::endl;

MyIntegerSet::MyIntegerSet(const MyIntegerSet& other)
{
    mData = other.mData;
}

MyIntegerSet& MyIntegerSet::operator +=(const MyIntegerSet& other)
{
    for (auto i : other.mData)
        mData.emplace(i);
    return *this;
}

MyIntegerSet& MyIntegerSet::operator -=(const MyIntegerSet& other)
{
    if (*this == other)
        mData.clear();
    else
        for (auto i : other.mData)
            if (mData.find(i) != mData.end())
                mData.erase(i);
    return *this;

}

MyIntegerSet& MyIntegerSet::operator *=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            result.emplace(a * b);
    mData = result;
    return *this;
}

MyIntegerSet& MyIntegerSet::operator /=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            if (b != 0)
                result.emplace(a / b);
    mData = result;
    return *this;
}

MyIntegerSet& MyIntegerSet::operator %=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            result.emplace(a % b);
    mData = result;
    return *this;
}

MyIntegerSet MyIntegerSet::operator +(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result += other;
    return result;
}

MyIntegerSet MyIntegerSet::operator -(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result -= other;
    return result;
}

MyIntegerSet MyIntegerSet::operator +() const
{
    return *this;
}

MyIntegerSet MyIntegerSet::operator -() const
{
    MyIntegerSet result;
    for (int a : mData)
        result += (-a);
    return result;

}

MyIntegerSet& MyIntegerSet::operator +=(int arg)
{
    mData.emplace(arg);
    return *this;
}

MyIntegerSet MyIntegerSet::operator *(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result *= other;
    return result;
}

MyIntegerSet MyIntegerSet::operator /(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result /= other;
    return result;
}

MyIntegerSet MyIntegerSet::operator %(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result %= other;
    return result;
}

MyIntegerSet& MyIntegerSet::operator |=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            result.emplace(a | b);
    mData = result;
    return *this;
}

MyIntegerSet& MyIntegerSet::operator ^=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            result.emplace(a ^ b);
    mData = result;
    return *this;
}

MyIntegerSet& MyIntegerSet::operator &=(const MyIntegerSet& other)
{
    set<int> result;
    for (int a : mData)
        for (int b : other.mData)
            result.emplace(a & b);
    mData = result;
    return *this;
}

MyIntegerSet MyIntegerSet::operator |(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result |= other;
    return result;
}

MyIntegerSet MyIntegerSet::operator ^(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result ^= other;
    return result;
}

MyIntegerSet MyIntegerSet::operator &(const MyIntegerSet& other)
{
    MyIntegerSet result = *this;
    result &= other;
    return result;
}

std::ostream& operator <<(std::ostream& out, const MyIntegerSet& arg)
{
    out << "Set contains " << arg.mData.size() << " elements:\n";
    out << "    ";
    for (int a : arg.mData)
        out << a << " ";
    out << endl;
    return out;
}

std::istream& operator >>(std::istream& in, MyIntegerSet& arg)
{
    int a;
    in >> a;
    arg += a;
    return in;
}

MyIntegerSet& MyIntegerSet::operator ++()
{
    int result = 0;
    for (int i : mData)
        result+=i;
    mData.emplace(result);
    return *this;
}

const MyIntegerSet MyIntegerSet::operator ++(int)
{
    MyIntegerSet result = *this;
    ++(*this);
    return result;
}

MyIntegerSet& MyIntegerSet::operator --()
{
    if (!mData.empty())
    {
        int biggest = *mData.end();
        mData.erase(biggest);
    }
    return *this;
}

const MyIntegerSet MyIntegerSet::operator --(int)
{
    MyIntegerSet result = *this;
    --(*this);
    return result;
}

bool MyIntegerSet::operator <(const MyIntegerSet& rhs) const
{
    return mData < rhs.mData;
}

bool MyIntegerSet::operator >(const MyIntegerSet& rhs) const
{
    return rhs < *this;
}

bool MyIntegerSet::operator <=(const MyIntegerSet& rhs) const
{
    return !(rhs < *this);
}

bool MyIntegerSet::operator >=(const MyIntegerSet& rhs) const
{
    return !(*this < rhs);
}

bool MyIntegerSet::operator !=(const MyIntegerSet& rhs) const
{
    return !(rhs == *this);
}

bool MyIntegerSet::operator ==(const MyIntegerSet& arg) const
{
    if (mData.size() != arg.mData.size())
        return false;
    for (int a : mData)
        if (arg.mData.find(a) == arg.mData.end())
            return false;
    return true;
}

MyIntegerSet& MyIntegerSet::operator <<=(int arg)
{
    set<int> result;
    for (int i : mData)
        result.emplace(i << arg);
    mData = result;
    return *this;
}

MyIntegerSet& MyIntegerSet::operator >>=(int arg)
{
    set<int> result;
    for (int i : mData)
        result.emplace(i >> arg);
    mData = result;
    return *this;
}

MyIntegerSet MyIntegerSet::operator <<(int arg)
{
    MyIntegerSet result = *this;
    result <<= arg;
    return result;
}

MyIntegerSet MyIntegerSet::operator >>(int arg)
{
    MyIntegerSet result = *this;
    result >>= arg;
    return result;
}

int MyIntegerSet::operator [](size_t idx) const
{
    if (idx >= mData.size())
        return -1;
    return 0;
}

MyIntegerSet& MyIntegerSet::operator -=(int arg)
{
    if (mData.find(arg) != mData.end())
        mData.erase(arg);
    return *this;
}

MyIntegerSet::operator std::string() const
{
    std::stringstream str;
    str << "Set contains " << mData.size() << "elements:\n";
    str << "    ";
    for (int a : mData)
        str << a << " ";
    str << endl;
    std::string result;
    str >> result;
    return result;
}

const MyIntegerSet MyIntegerSet::operator,(MyIntegerSet& v2)
{
    MyIntegerSet res;
    res = *this;
    return res;
}

MyIntegerSet::MyIntegerSet(int arg)
{
    mData.emplace(arg);
}

MyIntegerSet::MyIntegerSet() = default;

MyIntegerSet& MyIntegerSet::operator =(const MyIntegerSet& other) = default;