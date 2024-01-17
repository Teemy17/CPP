#include <iostream>
#include <ctime>
using namespace std;

void q2();
int findMax(const int arr[], int size);

int main()
{
    q2();
    return 0;
}

void q2()
{
    int n[10];
    cout << "Generated 10 random integers between 1 and 100:" << endl;
    srand(time(0) * time(0));
    for (int i = 0; i < 10; i++)
    {
        n[i] = rand() % 100 + 1;
        cout << n[i] << " ";
    }
    int max = findMax(n, 10);
    cout << endl
         << "The largest element in the array is: " << max << endl;
}

int findMax(const int arr[], int size)
{
    if (size == 1)
    {
        return arr[0];
    }
    else
    {
        int max = findMax(arr, size - 1);
        if (max > arr[size - 1])
        {
            return max;
        }
        else
        {
            return arr[size - 1];
        }
    }
}
