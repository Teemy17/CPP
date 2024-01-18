#include <iostream>
#include <cstring>
#include <string>
using namespace std;

bool mystery1(char *, const char *, size_t max_size);
bool mystery2(char *, const char *);
// mystery1 concatenates the strings by appending string s2 to the end of string s1.

int main()
{
    char string1[80];
    char string2[80];
    cout << "Enter two strings: ";
    cin >> string1 >> string2;

    if (mystery2(string1, string2))
    {
        cout << "Found a substring\n";
    }
    else
    {
        cout << "No substring\n";
    }

    if (mystery1(string1, string2, sizeof(string1)))
    {
        cout << string1 << endl;
    }

    return 0;

} // end main

bool mystery1(char *s1, const char *s2, size_t max_size)
{
    size_t s1_length = strlen(s1);
    size_t s2_length = strlen(s2);

    if (s1_length + s2_length >= max_size)
    {
        cout << "Error: Concatenation would overflow buffer\n";
        return false;
    }

    while (*s1 != '\0')
        ++s1;
    for (; (*s1 = *s2); ++s1, ++s2)
        ;

    return true;
}

bool mystery2(char *s1, const char *s2)
{
    return strstr(s1, s2) != nullptr;
}
