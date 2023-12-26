#include <iostream>
using namespace std;

//2.1
// int main() 
// {
//     cout << "Enter a number of size: ";
//     int n;
//     cin >> n;
//     for(int i = 1; i <= n; ++i) {
//         for(int j = 1; j <= i; ++j) {
//             cout << "*";
//         }
//         cout << "\n";
//     }
//     return 0;
// }

//2.2
int main()
{
    cout << "Enter a number of size: ";
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i; ++j) {
            cout << "*";
        }
        cout << endl;
    }

    for(int i = n - 1; i >= 1; --i) {
        for(int j = 1; j <= i; ++j) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}