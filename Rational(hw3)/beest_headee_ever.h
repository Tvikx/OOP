#include <iostream>
#include <sstream>
#include <string>



using namespace std;

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);
    int Numerator() const;
    int Denominator() const;
    friend Rational operator+(const Rational& a, const Rational& b);
    friend Rational operator*(const Rational& a, const Rational& b);
    friend Rational operator/(const Rational& a, const Rational& b);
    friend Rational operator-(const Rational& a, const Rational& b);
    friend bool operator==(const Rational &a, const Rational &b);
    friend ostream &operator<<(ostream &out,const Rational &a);
    friend istream &operator>>(istream &in,  Rational &a);

private:
    int num, denom;
};


