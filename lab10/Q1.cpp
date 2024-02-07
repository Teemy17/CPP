#include <iostream>

class Fraction
{
private:
    int numerator;
    int denominator;

    static int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    void simplify()
    {
        int common = gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;
    }

public:
    Fraction(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator)
    {
        simplify();
    }

    Fraction operator+(const Fraction &other) const
    {
        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator-(const Fraction &other) const
    {
        return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator*(const Fraction &other) const
    {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction &other) const
    {
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    bool operator==(const Fraction &other) const
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator>(const Fraction &other) const
    {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator<(const Fraction &other) const
    {
        return numerator * other.denominator < other.numerator * denominator;
    }

    friend std::ostream &operator<<(std::ostream &os, const Fraction &f)
    {
        if (f.numerator < 0 || f.denominator < 0)
        {
            os << "-";
            os << std::abs(f.numerator) << "/" << std::abs(f.denominator);
        }
        else
        {
            os << f.numerator << "/" << f.denominator;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Fraction &f)
    {
        char slash;
        is >> f.numerator >> slash >> f.denominator;
        f.simplify();
        return is;
    }
};

int main()
{
    Fraction f1, f2;
    std::cout << "Enter fraction 1 (numerator and denominator): ";
    std::cin >> f1;
    std::cout << "Enter fraction 2 (numerator and denominator): ";
    std::cin >> f2;

    std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
    std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
    std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
    std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;

    if (f1 == f2) std::cout << "f1 is equal to f2" << std::endl;
    if (f1 > f2) std::cout << "f1 is greater than f2" << std::endl;   
    if (f1 < f2) std::cout << "f1 is less than f2" << std::endl;

    return 0;

}
