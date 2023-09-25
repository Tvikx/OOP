#include "beest_headee_ever.h"
#include <iostream>
#include <sstream>
#include <string>



using namespace std;



    Rational::Rational(){};
    Rational::Rational(int numerator, int denominator) {
        if (denominator == 0) {
            std::stringstream ss;
            ss << "Argument must not be zero";
            throw invalid_argument(ss.str());
        }

        num = numerator;
        denom = denominator; 
    }

    int Rational::Numerator() const
    {
        return this->num;
    }
    int Rational::Denominator() const
    {
        return this->denom;
    }



    Rational operator+(const Rational& a, const Rational& b) 
    {
        return Rational(a.num * b.denom + b.num * a.denom, a.denom * b.denom);
    }
    Rational operator*(const Rational& a, const Rational& b)
    {
        return Rational(a.num * b.num, a.denom * b.denom);
    }
    Rational operator/(const Rational& a, const Rational& b)
    {
        return Rational(a.num * b.denom, a.denom * b.num);
    }
    Rational operator-(const Rational& a, const Rational& b)
    {
        return Rational(a.num * b.denom - b.num * a.denom, a.denom * b.denom);
    }
    bool operator==(const Rational &a, const Rational &b)
    {
        if(a.num / a.denom == b.num / b.denom)
            return true;
        else
            return false;
    }
    ostream &operator<<(ostream &out,const Rational &a)
    {
        out << a.num << '/' << a.denom << endl;
        return out;
    }
    istream &operator>>(istream &in,  Rational &a)
    {
        in >> a.num;
        in.ignore(1);
        in >> a.denom;
        return in;
    }
