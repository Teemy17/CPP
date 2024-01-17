#include <iostream>
#include <ctime>
using namespace std;

void q3();
void reverseString(string &s);

int main()
{
    q3();
    return 0;
}

void q3()
{
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    reverseString(s);
}

void reverseString(string &s)
{
    if (s.length() == 1)
    {
        cout << s << endl;
    }
    else if (s.length() == 0)
    {
        cout << endl;
    }
    else
    {
        cout << s[s.length() - 1];
        s = s.substr(0, s.length() - 1);
        reverseString(s);
    }
}