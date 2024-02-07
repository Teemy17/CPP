#include <algorithm>
#include <iostream>
#include <vector>

struct Poly
{
    int coefficient;
    int exponents;
};

class Polynomial
{
public:
    Polynomial() = default;
    ~Polynomial() = default;

    Polynomial(int coef, int expo) : polynomials()
    {
        Poly poly = {coef, expo};
        polynomials.push_back(poly);
    }

    Polynomial operator+(const Polynomial &other) const
    {
        Polynomial result = *this; // Make a copy of the current polynomial
        for (const auto &p : other.polynomials)
        {
            result.setPoly(p.coefficient, p.exponents); // Add terms from the other polynomial
        }
        return result;
    }

    Polynomial operator-(const Polynomial &other) const
    {
        Polynomial result = *this; // Make a copy of the current polynomial
        for (const auto &p : other.polynomials)
        {
            result.setPoly(-p.coefficient, p.exponents); // Subtract terms from the other polynomial
        }
        return result;
    }

    Polynomial operator*(const Polynomial &other) const
    {
        Polynomial result;
        for (const auto &p1 : polynomials)
        {
            for (const auto &p2 : other.polynomials)
            {
                result.setPoly(p1.coefficient * p2.coefficient, p1.exponents + p2.exponents);
            }
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &p)
    {
        if (p.polynomials.empty())
        {
            os << "0";
        }
        else
        {
            for (size_t i = 0; i < p.polynomials.size(); ++i)
            {
                os << p.polynomials[i].coefficient << "x^" << p.polynomials[i].exponents;
                if (i != p.polynomials.size() - 1)
                {
                    os << " + ";
                }
            }
        }
        return os;
    }

    void setPoly(int coe, int exp)
    {
        Poly poly = {coe, exp};
        polynomials.push_back(poly);
        std::sort(
            polynomials.begin(), polynomials.end(),
            [](const Poly &a, const Poly &b)
            { return a.exponents > b.exponents; }); // Added return statement
    }

    private:
        std::vector<Poly> polynomials;
};

int main()
{
    Polynomial p1;
    p1.setPoly(2, 3);
    p1.setPoly(4, 1);

    Polynomial p2;
    p2.setPoly(3, 2);
    p2.setPoly(5, 0);

    std::cout << "Polynomial p1: " << p1 << std::endl;
    std::cout << "Polynomial p2: " << p2 << std::endl;
    std::cout << "Polynomial p3: (p1 + p2): " << p1 + p2 << std::endl;
    std::cout << "Polynomial p4: (p1 - p2): " << p1 - p2 << std::endl;
    std::cout << "Polynomial p5: (p1 * p2): " << p1 * p2 << std::endl;
}