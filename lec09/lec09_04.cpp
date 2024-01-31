#include <iostream>
class Vector
{
private:
    double x, y, z; // Private data members
public:
    // Constructor to initialize the vector
    Vector(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}
    
    // Member function returning a reference to a private member
    double &getX() { return x; }
    
    // Member function returning a pointer to a private member
    double *getYPtr() { return &y; }

    // Const member function for read-only access to a private member
    const double &getZ() const { return z; }
};
int main()
{
    Vector vec(1.0, 2.0, 3.0);
    
    // Modify x directly through its reference
    double &xRef = vec.getX();
    xRef = 4.0;
    
    // Access y using a pointer
    double *yPtr = vec.getYPtr();
    *yPtr = 5.0;
    
    // Read z through a const reference (cannot modify z)
    const double &zRef = vec.getZ();
    std::cout << "Vector: (" << vec.getX() << ", " << *vec.getYPtr() << ", " << zRef
              << ")" << std::endl;
};