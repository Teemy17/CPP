#include <iostream>
#include <string>
using namespace std;

class TempConverter
{
private:
    double t;

public:
    double fahr_to_cels(double t)
    {
        return (t - 32) * 5 / 9;
    }

    double cels_to_fahr(double t)
    {
        return (t * 9 / 5) + 32;
    }
};

int main()
{
    while (true)
    {
        cout << "Please enter a temperature: ";
        double t;
        cin >> t;
        if (cin.fail())
        {
            cout << "Invalid input!" << endl;
            break;
        }

        cout << "Convert to celsius or fahrenheit (F or C): ";
        string unit;
        cin >> unit;

        TempConverter tc;
        if (unit == "F" || unit == "f")
        {
            cout << t << " Celsius is " << tc.cels_to_fahr(t) << " Fahrenheit" << endl;
        }
        else if (unit == "C" || unit == "c")
        {
            cout << t << " Fahrenheit is " << tc.fahr_to_cels(t) << " Celsius" << endl;
        }
        else
        {
            cout << "Invalid unit!" << endl;
        }

        cout << "Do you want to continue? (Y/N): ";
        string cont;
        cin >> cont;
        if (cont == "N" || cont == "n")
        {
            break;
        }
        else if (cont == "Y" || cont == "y")
        {
            continue;
        }
        else
        {
            cout << "Invalid input!" << endl;
            break;
        }
    }
}
