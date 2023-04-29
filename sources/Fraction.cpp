#include <cmath>
#include <cstdlib>

#include "Fraction.hpp"
using namespace ariel;

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    if (a == 0)
        return 1;
    if (b == 0)
        return 1;

    if (a == b)
        return a;
    if (a > b)
        return gcd(a - b, b);
    return gcd(a, b - a);
}

Fraction::Fraction(int num, int denom)
{
    if (denom == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    else
    {
        if (denom < 0)
        {
            this->counter = -1 * num;
            this->denominator = -1 * denom;
        }
        else
        {
            this->counter = num;
            this->denominator = denom;
        }
    }
}
Fraction::Fraction(float num)
{
    int negative;
    if (num < 0)
    {
        num = abs(num);
        negative = 1;
    }
    int power = 1;
    while (num * power != floor(num) * power && power < 1000)
    {
        power *= 10;
    }
    int counter = num * power;
    int denominator = power;
    int commonDivisor = gcd(counter, denominator);
    if (negative == 1)
    {
        counter = -1 * counter;
    }
    this->counter = counter / commonDivisor;
    this->denominator = denominator / commonDivisor;
}
// plus operators
Fraction Fraction::operator+(Fraction &other) const
{
   
         
    long long num = (long long)this->counter *(long long) other.denominator + (long long)this->denominator * (long long)other.counter;
    long long denom =(long long) this->denominator * (long long)other.denominator;
     if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("");
        }

        if (num < std::numeric_limits<int>::min() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("");
        }
    int commonDivisor = gcd((int)num,(int) denom);
    return Fraction((int)num / commonDivisor, (int)denom / commonDivisor);
}
Fraction Fraction::operator+(float num) const
{
    Fraction second(num);
    return this->operator+(second);
}

Fraction &Fraction::operator++()
{
    counter += denominator;
    return *this;
}
Fraction Fraction::operator++(int num)
{
    Fraction res = *this;
    ++(*this);
    return res;
}

// minus operators
Fraction Fraction::operator-(Fraction &other) const
{
    long long num = (long long)this->counter *(long long) other.denominator - (long long)this->denominator *(long long) other.counter;
    long long denom = (long long)this->denominator * (long long)other.denominator;
         if (num /denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("to big");
        }

        if (num /denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("to small");
        }
    int commonDivisor = gcd((int)num,(int) denom);
    return Fraction((int)num / commonDivisor,(int) denom / commonDivisor);
}
Fraction Fraction::operator-(float num) const
{
    Fraction second(num);
    return this->operator-(second);
}

Fraction &Fraction::operator--()
{
    counter -= denominator;
    return *this;
}
Fraction Fraction::operator--(int num)
{
    Fraction res = *this;
    --(*this);
    return res;
}

// comparison operators
bool Fraction ::operator<(Fraction &other) const
{
    double first = (double)this->counter / this->denominator;
    double second = (double)other.getNumerator() / other.getDenominator();
    return first < second;
}
bool Fraction ::operator<(float num) const
{
    Fraction second(num);

    return this->operator<(second);
}

bool Fraction ::operator<=(Fraction &other) const
{
    return this->counter * other.getDenominator() <= other.getNumerator() * this->denominator;
}
bool Fraction ::operator<=(float num) const
{
    Fraction second(num);
    return this->operator<=(second);
}
bool Fraction ::operator>(Fraction &other) const
{
    double first = (double)this->counter / this->denominator;
    double second = (double)other.getNumerator() / other.getDenominator();
    return first > second;
}
bool Fraction ::operator>(float num) const
{
    Fraction second(num);

    return this->operator>(second);
}

bool Fraction ::operator>=(float num) const
{
    Fraction second(num);
    int numerator1 = this->counter * second.getDenominator();
    int numerator2 = second.getNumerator() * this->denominator;
    return numerator1 >= numerator2;
}
