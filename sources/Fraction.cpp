#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Fraction.hpp"
using namespace ariel;


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
            if (denom == std::numeric_limits<int>::max() && num == std::numeric_limits<int>::max())
            {
                this->counter = 1;
                this->denominator = 1;
            }
            else
            {
                this->counter = num;
                this->denominator = denom;
            }
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
    int commonDivisor = __gcd(counter, denominator);
    if (negative == 1)
    {
        counter = -1 * counter;
    }
    this->counter = counter / commonDivisor;
    this->denominator = denominator / commonDivisor;
}
// plus operators
Fraction ariel::operator+(const Fraction &first, const Fraction &second)
{

    long long newNumerator = (long long)first.getNumerator() * (long long)second.getDenominator() + (long long)second.getNumerator() * (long long)first.getDenominator();
    long long newDenominator = (long long)first.getDenominator() * (long long)second.getDenominator();
    if (newNumerator > std::numeric_limits<int>::max() ||
        newNumerator < std::numeric_limits<int>::min() ||
        newDenominator > std::numeric_limits<int>::max() ||
        newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow detected");
    }
    int gcd = __gcd((int)newNumerator, (int)newDenominator);
    return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
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
Fraction ariel::operator-(const Fraction &first, const Fraction &second)
{
    long long newNumerator = (long long)first.getNumerator() * (long long)second.getDenominator() - (long long)second.getNumerator() * (long long)first.getDenominator();
    long long newDenominator = (long long)first.getDenominator() * (long long)second.getDenominator();
    if (newNumerator > std::numeric_limits<int>::max() ||
        newNumerator < std::numeric_limits<int>::min() ||
        newDenominator > std::numeric_limits<int>::max() ||
        newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow detected");
    }
    int gcd = __gcd((int)newNumerator, (int)newDenominator);
    return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
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

// multipication operators
Fraction ariel::operator*(const Fraction &first, const Fraction &second)
{

    long long newNumerator = (long long)first.getNumerator() * (long long)second.getNumerator();
    long long newDenominator = (long long)first.getDenominator() * (long long)second.getDenominator();
    if (newNumerator > std::numeric_limits<int>::max() ||
        newNumerator < std::numeric_limits<int>::min() ||
        newDenominator > std::numeric_limits<int>::max() ||
        newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow detected");
    }
    int gcd = __gcd((int)newNumerator, (int)newDenominator);
    return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
}

// divide operators
Fraction ariel::operator/(const Fraction &first, const Fraction &second)
{
    int max = std::numeric_limits<int>::max();

    if (second.getNumerator() == 0)
    {
        throw std::runtime_error("division by zero");
    }
    long long newNumerator = (long long)first.getNumerator() * (long long)second.getDenominator();
    long long newDenominator = (long long)first.getDenominator() * (long long)second.getNumerator();
    if (newNumerator > std::numeric_limits<int>::max() ||
        newNumerator < std::numeric_limits<int>::min() ||
        newDenominator > std::numeric_limits<int>::max() ||
        newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow detected");
    }
    int gcd = __gcd((int)newNumerator, (int)newDenominator);
    return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
}
// comparison operators

bool ariel::operator>(const Fraction &first, const Fraction &second)
{
    return (first.getNumerator() * second.getDenominator()) > (second.getNumerator() * first.getDenominator());
}

bool ariel::operator>=(const Fraction &first, const Fraction &second)
{
    int numerator1 = first.getNumerator() * second.getDenominator();
    int numerator2 = second.getNumerator() * first.getDenominator();
    return numerator1 >= numerator2;
}

bool ariel::operator<(const Fraction &first, const Fraction &second)
{
    int num1 = first.getNumerator() * second.getDenominator();
    int num2 = second.getNumerator() * first.getDenominator();
    return num1 < num2;
}
bool ariel::operator<=(const Fraction &first, const Fraction &second)
{
    return first.getNumerator() * second.getDenominator() <= second.getNumerator() * first.getDenominator();
}
bool ariel::operator==(const Fraction &first, const Fraction &second)
{
    const float digit = 1000;
    int firstnum = (int)(((float)first.getNumerator() / (float)first.getDenominator()) * digit);
    int secondnum = (int)(((float)second.getNumerator() / (float)second.getDenominator()) * digit);
    return firstnum == secondnum;
}
bool ariel::operator!=(const Fraction &first, const Fraction &second)
{
    return !(first == second);
}

// output and input  operators

std::ostream &ariel::operator<<(std::ostream &output, const Fraction &other)
{
    int gcd = __gcd(abs(other.counter), abs(other.denominator));
    if (other.denominator < 0)
    {
        output << -1 * other.getNumerator() / gcd << '/' << -1 * other.getDenominator() / gcd;
    }
    else
    {
        output << other.getNumerator() / gcd << '/' << other.getDenominator() / gcd;
    }
    return output;
}
std::istream &ariel::operator>>(std::istream &input, Fraction &other)
{
    int counter = 0;
    int denominator = 0;
    input >> counter >> denominator;

    if (denominator == 0)
    {
        throw std::runtime_error("division by zero");
    }

    other = Fraction(counter, denominator);

    return input;
}
