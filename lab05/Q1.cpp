#include <iostream>
#include <string>
using namespace std;

class Heartratemonitor
{
private:
    string firstname;
    string lastname;
    int birthyear;
    int birthmonth;
    int birthday;
    const int currentYear = 2023;
    const int currentMonth = 12;
    const int currentDay = 28;

public:
    Heartratemonitor(string firstname, string lastname, int birthyear, int birthmonth, int birthday)
    {
        this->firstname = firstname;
        this->lastname = lastname;
        this->birthday = birthday;
        this->birthmonth = birthmonth;
        this->birthyear = birthyear;

        if (!isValidDate())
        {
            cerr << "Invalid birthdate. Please try again!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    bool isValidDate()
    {
        return birthyear >= 0 && birthmonth >= 1 && birthmonth <= 12 && birthday >= 1 && birthday <= 31;
    }

    string get_firstname()
    {
        return firstname;
    }

    string get_lastname()
    {
        return lastname;
    }

    int get_birthyear()
    {
        return birthyear;
    }

    int get_birthmonth()
    {
        return birthmonth;
    }

    int get_birthday()
    {
        return birthday;
    }

    int get_age()
    {   
        int age = currentYear - birthyear - ((currentMonth < birthmonth || (currentMonth == birthmonth && currentDay < birthday)) ? 1 : 0);
        return age;
    }

    int get_maxheartrate()
    {
        int maxheartrate = 220 - get_age();
        return maxheartrate;
    }

    void get_targetheartrate()
    {
        int targetheartrate = get_maxheartrate() * 0.5;
        int targetheartrate2 = get_maxheartrate() * 0.85;
        cout << "Your target heart rate is " << targetheartrate << " - " << targetheartrate2 << " beats per minute." << endl;
    }
};

int main()
{
    string firstname;
    string lastname;
    int birthyear;
    int birthmonth;
    int birthday;

    cout << "Enter your first name: ";
    cin >> firstname;
    cout << "Enter your last name: ";
    cin >> lastname;
    cout << "Enter your birth year: ";
    cin >> birthyear;
    cout << "Enter your birth month: ";
    cin >> birthmonth;
    cout << "Enter your birth day: ";
    cin >> birthday;

    Heartratemonitor heartratemonitor(firstname, lastname, birthyear, birthmonth, birthday);

    cout << "Hello, " << heartratemonitor.get_age() << " years old"
         << " " << heartratemonitor.get_firstname() << " " << heartratemonitor.get_lastname() << "." << endl;
    cout << "Your maximum heart rate is " << heartratemonitor.get_maxheartrate() << " beats per minute." << endl;
    heartratemonitor.get_targetheartrate();

    return 0;
}
