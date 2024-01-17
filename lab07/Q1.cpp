#include <iostream>
#include <ctime>
#include <array>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

class Polling
{
public:
    void collectRating();
    void displayResults();
    Polling();

private:
    std::array<std::string, 5> dishes;
    std::array<std::array<int, 10>, 5> responses;
};

int main()
{
    Polling p;
    p.collectRating();
    p.displayResults();
    return 0;
}

Polling::Polling()
{
    dishes = {
        "Pad Thai",
        "Som Tam",
        "Mango Sticky Rice",
        "Tom Yum Goong",
        "Green Curry"};
    responses = {0};
}

void Polling::collectRating()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Poll " << i + 1 << ":" << endl;
        for (int j = 0; j < 5; j++)
        {
            int scale = 0;
            cout << "Rate " << dishes[j] << " on a scale of 1 to 10: ";
            cin >> scale;
            while (true)
            {
                if (std::cin.fail())
                {
                    std::cin.clear();                                                   // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    std::cout << "Invalid input. Please enter a number between 1 and 10: ";
                    std::cin >> scale;
                }
                else if (scale > 0 && scale < 11)
                {
                    responses[j][scale - 1] += 1;
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter a number between 1 and 10: ";
                    cin >> scale;
                }
            }
        }
    }
    cout << endl;
}

void Polling::displayResults()
{
    array<int, 5> score;
    cout << "Survey Results" << endl
         << std::left << setw(20) << "Dish \t\t\t\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t Average" << endl;
    for (int i = 0; i < 5; i++)
    {
        double total_rate = 0;
        cout << left << setw(20) << dishes[i] << "\t\t";
        for (int j = 0; j < 10; j++)
        {
            total_rate += responses[i][j] * (j + 1);
            cout << responses[i][j] << "\t";
        }
        score[i] = total_rate;
        total_rate /= 5;
        cout << fixed << setprecision(2) << total_rate << endl;
    }
    int max = 0;
    int min = 0;
    for (int k = 0; k < 5; k++)
    {
        if (score[k] > score[max])
        {
            max = k;
        }
        if (score[k] < score[min])
        {
            min = k;
        }
    }
    cout << "Highest rated dish: " << dishes[max] << " Score: " << score[max] << endl;
    cout << "Lowest rated dish: " << dishes[min] << " Score: " << score[min] << endl;
}