#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <set>
#include <map>


using namespace std;

int NOD(int a, int b)
{
    while (a > 0 && b > 0) {
        if (a > b) {
            a %= b;
        }
        else {
            b %= a;
        }
    }
    return a + b;
}

int NOK(int a, int b)
{
    return (a * b) / (NOD(a, b));
}

class Rational {
public:
    Rational() 
    {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        ReduceFraction(numerator, denominator);
        this->numerator = numerator;
        this->denominator = denominator;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    void ReduceFraction(int& numerator, int& denominator)const
    {
        if (numerator == 0) {
            numerator = 0;
            denominator = 1;
        }
        else {
            if (denominator < 0) {
                denominator *= (-1);
                numerator *= (-1);
            }
            int nod = NOD(abs(numerator), abs(denominator));
            numerator /= nod;
            denominator /= nod;
        }
    }

    int numerator;
    int denominator;
};


Rational CommonNumeratorAndDenominator(const Rational& lhs, const Rational& rhs, const char& sign)
{
    int lhsFactor = 1, rhsFactor = 1;
    int nok = lhs.Denominator();
    if (lhs.Denominator() != rhs.Denominator()) {
        nok = NOK(lhs.Denominator(), rhs.Denominator());
        lhsFactor = nok / lhs.Denominator(), rhsFactor = nok / rhs.Denominator();
    }

    if (sign == '+') return { (lhs.Numerator() * lhsFactor) + (rhs.Numerator() * rhsFactor), nok };

    if (sign == '-') return { (lhs.Numerator() * lhsFactor) - (rhs.Numerator() * rhsFactor), nok};
    
    return { 0,0 };
}

ostream& operator<<(ostream& s, const Rational& fraction)
{
    s << fraction.Numerator() << "/" << fraction.Denominator();
    return s;
}

istream& operator>>(istream& s, Rational& fraction)
{
    if (!s.eof()) {
        int num = NULL, denom = NULL;
        char sign = NULL;
        s >> num;
        s >> sign;
        s >> denom;
        if (sign == '/' && num != NULL && denom != NULL) {
            fraction = { num, denom };
        }
    }
    return s;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
        return true;
    }
    return false;
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
    return ((double)(lhs.Numerator() / (double)lhs.Denominator()) > ((double)rhs.Numerator() / (double)rhs.Denominator()));
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    return (((double)lhs.Numerator() / (double)lhs.Denominator()) < ((double)rhs.Numerator() / (double)rhs.Denominator()));
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return CommonNumeratorAndDenominator(lhs, rhs, '+');
};

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return CommonNumeratorAndDenominator(lhs, rhs, '-');
};

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
}