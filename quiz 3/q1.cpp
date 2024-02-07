#include <iostream>

class Complex
{
public:
    double real, imag, real_2;
    Complex(double real = 0.0, double imag = 0.0, double real_2) : real(real), imag(imag), real_2(real_2) {}
    // Member function for operator overloading
    // Overloads the + operator to add two complex numbers.
    // It takes a const reference to another Complex object and returns a new Complex object representing the sum.
    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag, real_2 + other.real_2);
    }
    // Friend function for output formatting (optional)
    // that overloads the << operator to allow printing of Complex objects to output streams
    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << "[" << c.real << ", " << c.imag << c.real_2 << "]";
        return os;
    }
};

int main()
{
    Complex c1(2, 3);
    Complex c2(4, 5);
    Complex c3 = c1 + c2;                   // Using overloaded + operator
    std::cout << "c1: " << c1 << std::endl; // Printing using friend function
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    return 0;
}