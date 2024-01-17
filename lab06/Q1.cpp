#include <iostream>
#include <string>
#include <limits>
using namespace std;

void find_smallest_integer()
{
    int n;
    cout << "Enter the number of integers: ";
    cin >> n;
    if (n <= 0)
    {
        cout << "Invalid input" << endl;
        return;
    }
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter integer #" << i + 1 << ": ";
        cin >> arr[i];
        if (cin.fail())
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
    }
    int smallest = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            smallest = arr[i];
        }
    }
    cout << "The smallest integer is " << smallest << endl;
}

int main()
{
    find_smallest_integer();
    return 0;
}