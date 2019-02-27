#ifndef MYPROJECT_LIB_RATIONAL_H
#define MYPROJECT_LIB_RATIONAL_H


class RationalNum
{
public:
    RationalNum();
    RationalNum(const int num, const int denom);

    void print() const;

    short compare(const RationalNum arg) const;
    short compare(int arg) const;

    RationalNum operator +(const RationalNum arg) const;
    RationalNum operator -(const RationalNum arg) const;
    RationalNum operator /(const RationalNum arg) const;
    RationalNum operator *(const RationalNum arg) const;

    RationalNum operator +(int arg) const;
    RationalNum operator -(int arg) const;
    RationalNum operator /(const int arg) const;
    RationalNum operator *(const int arg) const;
private:
    int numerator;
    int denominator;

    void setNum(const int num);
    void setDenom(const int denom);

    int getNum() const;
    int getDenom() const;

    void reduce();
};


#endif //MYPROJECT_LIB_RATIONAL_H
