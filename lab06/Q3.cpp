#include <iostream>
using namespace std;
int mystery(int, int);
int main()
{
    int x = 0;
    int y = 0;
    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "The result is " << mystery(x, y) << endl;
    return 0;
}
int mystery(int a, int b)
{
    if (b == 0)
    { // Base case
        return 0;
    }
    else if (b < 0)
    {
        return -a + mystery(a, b + 1);
    }
    else
    { // Recursion step
        return a + mystery(a, b - 1);
    }
}