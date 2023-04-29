
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
      // constructor to fraction with 2 integar
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
      Fraction operator+(Fraction &other) const;
      Fraction operator+(float num) const;
      friend Fraction operator+(const Fraction &first, const Fraction &second)
      {

         int newNumerator = first.getNumerator() * second.getDenominator() + second.getNumerator() *first.getDenominator();
         int newDenominator =first.getDenominator() * second.getDenominator();
           int gcd = __gcd(newNumerator,newDenominator);
         return Fraction(newNumerator / gcd, newDenominator / gcd);
      }

      Fraction operator++(int num); // postfix
      Fraction &operator++();       // prefix

      // minus operators
      Fraction operator-(Fraction &other) const;
      Fraction operator-(float num) const;
      friend Fraction operator-(const Fraction &first, const Fraction &second)
      {

         int newNumerator = first.getNumerator() * second.getDenominator() - second.getNumerator() * first.getDenominator();
         int newDenominator = first.getDenominator() * second.getDenominator();

         int gcd = __gcd(newNumerator, newDenominator);
         return Fraction(newNumerator / gcd, newDenominator / gcd);
      }

      Fraction operator--(int num); // postfix
      Fraction &operator--();       // prefix

      // multipication operators
      friend Fraction operator*(const Fraction &first, const Fraction &second)
      {
        
         long long  newNumerator = (long long )first.getNumerator() * (long long )second.getNumerator();
         long long  newDenominator = (long long )first.getDenominator() * (long long )second.getDenominator();
          if (newNumerator /newDenominator>std::numeric_limits<int>::max()) {
               
               throw std::overflow_error("to big");
        }

        if (newNumerator /newDenominator<std::numeric_limits<int>::min()) {
            throw std::overflow_error("to small");
        }

         int gcd = __gcd((int)newNumerator,(int) newDenominator);
         return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
      }
 
      // divide operators
      friend Fraction operator/(const Fraction &first, const Fraction &second)
      {
         int max= std::numeric_limits<int>::max();

         if (second.getNumerator() == 0)
         {
            throw std::runtime_error("division by zero");
         }
         long long  newNumerator = (long long )first.getNumerator() * (long long )second.getDenominator();
         long long  newDenominator = (long long )first.getDenominator() * (long long )second.getNumerator();
            if (newNumerator /newDenominator>std::numeric_limits<int>::max()) {
               
               throw std::overflow_error("to big");
        }

        if (newNumerator /newDenominator<std::numeric_limits<int>::min()) {
            throw std::overflow_error("to small");
        }
         int gcd = __gcd((int)newNumerator,(int) newDenominator);
         return Fraction((int)newNumerator / gcd, (int)newDenominator / gcd);
      }

      // comparison operators
      bool operator>(Fraction &other) const;
      bool operator>(float num) const;

      friend bool operator>(const Fraction &first, const Fraction &second)
      {
         return (first.getNumerator() * second.getDenominator()) > (second.getNumerator() * first.getDenominator());
      }

      bool operator>=(float num) const;
      friend bool operator>=(const Fraction &first, const Fraction &second)
      {
         int numerator1 = first.getNumerator() * second.getDenominator();
         int numerator2 = second.getNumerator() * first.getDenominator();
         return numerator1 >= numerator2;
      }
      friend bool operator>=(float num, const Fraction &second)
      {
         Fraction first(num);
         int numerator1 = first.getNumerator() * second.getDenominator();
         int numerator2 = second.getNumerator() * first.getDenominator();
         return numerator1 >= numerator2;
      }

      bool operator<(Fraction &other) const;
      bool operator<(float num) const;
      friend bool operator<(const Fraction &first, const Fraction &second)
      {
         int num1 = first.getNumerator() * second.getDenominator();
         int num2 = second.getNumerator() * first.getDenominator();
         return num1 < num2;
      }

      bool operator<=(Fraction &other) const;
      bool operator<=(float num) const;
      friend bool operator<=(const Fraction &first, const Fraction &second)
      {
         return first.getNumerator() * second.getDenominator() <= second.getNumerator() * first.getDenominator();
      }
      friend bool operator<=(float num, const Fraction &second)
      {
         Fraction first(num);
         return first.getNumerator() * second.getDenominator() <= second.getNumerator() * first.getDenominator();
      }

      friend bool operator==(const Fraction &first, const Fraction &second)
      {
           const float digit = 1000;
            int firstnum = (int)(((float)first.getNumerator()/ (float)first.getDenominator()) * digit);
            int secondnum = (int)(((float)second.getNumerator() / (float)second.getDenominator()) * digit);
            return firstnum == secondnum;

      }

      friend bool operator!=(const Fraction &first, const Fraction &second)
      {
         return !(first == second);
      }

      friend ostream &operator<<(ostream &output, const Fraction &other)
      {
         int gcd = __gcd(abs(other.counter), abs(other.denominator));
         if (other.denominator < 0)
         {
            output << -1 * other.counter / gcd << '/' << -1 * other.denominator / gcd;
         }
         else
         {
            output << other.counter / gcd << '/' << other.denominator / gcd;
         }
         return output;
      }

      friend istream &operator>>(istream &input, Fraction &other)
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
   };
}
#endif