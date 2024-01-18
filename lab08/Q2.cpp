#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

pair<int, int> mystery3(const char *s)
{
    unsigned int length = 0;
    unsigned int vowelCount = 0;

    for (; *s != '\0'; ++s)
    {
        ++length;
        if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u' ||
            *s == 'A' || *s == 'E' || *s == 'I' || *s == 'O' || *s == 'U')
        {
            ++vowelCount;
        }
    }

    return make_pair(length, vowelCount);
}

void reverseString(char *s)
{
    int length = strlen(s);
    if (length == 1)
    {
        cout << s << endl;
    }
    else if (length == 0)
    {
        cout << endl;
    }
    else
    {
        cout << s[length - 1];
        s[length - 1] = '\0';
        reverseString(s);
    }
}

int main()
{
    const int MAX_SIZE = 80;
    char string1[MAX_SIZE];

    cout << "Enter a string: ";

    cin.getline(string1, MAX_SIZE + 1);

    if (cin.fail())
    {
        cout << "Error: Input string too long\n";
        return 1;
    }

    pair<int, int> result = mystery3(string1);
    cout << "Length of the string: " << result.first << endl;
    cout << "Number of vowels: " << result.second << endl;

    reverseString(string1);

    return 0;
}
