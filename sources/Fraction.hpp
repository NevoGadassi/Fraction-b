
#pragma once
#ifndef Fraction_HPP
#define Fraction_HPP

#include <limits>
#include <cstdlib>
#include <algorithm> // For __gcd; taken from the internet
#include <vector>
#include <iostream>
using namespace std;

namespace ariel
{

   class Fraction
   {
   private:
      int counter = 0;
      int denominator = 1;

   public:
      // constructor's
      Fraction()
      {
      }
      Fraction(int num, int denom);
      Fraction(float num);
      int getNumerator() const
      {
         return this->counter;
      }
      int getDenominator() const
      {
         return this->denominator;
      }
      // plus operators
      friend Fraction operator+(const Fraction &first, const Fraction &second);
      Fraction operator++(int num); // postfix
      Fraction &operator++();       // prefix

      // minus operators
      friend Fraction operator-(const Fraction &first, const Fraction &second);
      Fraction operator--(int num); // postfix
      Fraction &operator--();       // prefix

      // multipication operators
      friend Fraction operator*(const Fraction &first, const Fraction &second);

      // divide operators
      friend Fraction operator/(const Fraction &first, const Fraction &second);

      // comparison operators
      friend bool operator>(const Fraction &first, const Fraction &second);
      friend bool operator>=(const Fraction &first, const Fraction &second);
      friend bool operator<(const Fraction &first, const Fraction &second);
      friend bool operator<=(const Fraction &first, const Fraction &second);
      friend bool operator==(const Fraction &first, const Fraction &second);
      friend bool operator!=(const Fraction &first, const Fraction &second);

      // output and input  operators
      friend ostream &operator<<(ostream &output, const Fraction &other);
      friend istream &operator>>(istream &input, Fraction &other);
   };
}
#endif
