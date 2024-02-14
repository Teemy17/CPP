#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Movie
{
    string title;
    vector<string> dates;
    vector<vector<int>> availableSeats;
};

struct Reservation
{
    string customerName;
    string movieTitle;
    string date;
    int round;
    int seatNumber;
};

void displaySchedule(const vector<Movie> &movies)
{
    cout << "Movie Schedule:" << endl;
    for (const Movie &movie : movies)
    {
        cout << "Movie: " << movie.title << endl;
        for (size_t i = 0; i < movie.dates.size(); ++i)
        {
            cout << "Date: " << movie.dates[i] << " ";
            cout << "Available rounds: ";
            for (size_t j = 0; j < movie.availableSeats[i].size(); ++j)
            {
                cout << (12 + j * 3) << ":00: " << movie.availableSeats[i][j] << " seats available";
                if (j < movie.availableSeats[i].size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

void makeReservation(vector<Movie> &movies)
{
    cout << "Select a movie:" << endl;
    for (size_t i = 0; i < movies.size(); ++i)
    {
        cout << i + 1 << ") " << movies[i].title << endl;
    }

    int movieIndex;
    cout << "Enter movie number: ";
    cin >> movieIndex;
    movieIndex--;

    if (cin.fail()) // Check if the input failed
    {
        cin.clear();                                         // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "Invalid input. Please enter a number." << endl;
        return;
    }

    if (movieIndex < 0 || movieIndex >= static_cast<int>(movies.size()))
    {
        cout << "Invalid movie number." << endl;
        return;
    }

    

    cout << "Select a date:" << endl;
    for (size_t i = 0; i < movies[movieIndex].dates.size(); ++i)
    {
        cout << i + 1 << ") " << movies[movieIndex].dates[i] << endl;
    }

    int dateIndex;
    cout << "Enter date number: ";
    cin >> dateIndex;
    dateIndex--;

    if (dateIndex < 0 || dateIndex >= static_cast<int>(movies[movieIndex].dates.size()))
    {
        cout << "Invalid date number." << endl;
        return;
    }

    cout << "Select a round:" << endl;
    for (size_t i = 0; i < movies[movieIndex].availableSeats[dateIndex].size(); ++i)
    {
        cout << i + 1 << ") Round " << i + 1 << " - " << movies[movieIndex].availableSeats[dateIndex][i] << " seats left" << endl;
    }

    int roundIndex;
    cout << "Enter round number: ";
    cin >> roundIndex;
    roundIndex--;

    if (roundIndex < 0 || roundIndex >= static_cast<int>(movies[movieIndex].availableSeats[dateIndex].size()))
    {
        cout << "Invalid round number." << endl;
        return;
    }

    cout << "Enter the number of seats to reserve: ";
    int numSeats;
    cin >> numSeats;

    if (numSeats <= 0 || numSeats > movies[movieIndex].availableSeats[dateIndex][roundIndex])
    {
        cout << "Invalid number of seats." << endl;
        return;
    }

    movies[movieIndex].availableSeats[dateIndex][roundIndex] -= numSeats;
    cout << "Successfully reserved " << numSeats << " seats for " << movies[movieIndex].title << " on "
         << movies[movieIndex].dates[dateIndex] << " for round " << roundIndex + 1 << "." << endl;
}

void saveToFile(const vector<Movie> &movies, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const auto &movie : movies)
    {
        file << movie.title << endl;
        for (size_t i = 0; i < movie.dates.size(); ++i)
        {
            file << movie.dates[i] << " ";
            for (size_t j = 0; j < movie.availableSeats[i].size(); ++j)
            {
                file << movie.availableSeats[i][j] << " ";
            }
            file << endl;
        }
        file << endl;
    }

    file.close();
    cout << "Data saved to " << filename << " successfully." << endl;
}

void loadFromFile(vector<Movie> &movies, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }

    movies.clear();

    string line;
    while (getline(file, line))
    {
        Movie movie;
        movie.title = line;
        while (getline(file, line) && !line.empty())
        {
            movie.dates.push_back(line.substr(0, 10));
            vector<int> seats;
            size_t pos = 11;
            while (pos < line.size())
            {
                int seat = stoi(line.substr(pos));
                seats.push_back(seat);
                pos = line.find(' ', pos) + 1;
            }
            movie.availableSeats.push_back(seats);
        }
        movies.push_back(movie);
    }

    file.close();
    cout << "Data loaded from " << filename << " successfully." << endl;
}
void cancelReservation(vector<Movie> &movies)
{
    cout << "Select a movie to cancel reservation:" << endl;
    for (size_t i = 0; i < movies.size(); ++i)
    {
        cout << i + 1 << ". " << movies[i].title << endl;
    }

    int movieIndex;
    cout << "Enter your choice: ";
    cin >> movieIndex;
    movieIndex--;

    if (cin.fail()) // Check if the input failed
    {
        cin.clear();                                         // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "Invalid input. Please enter a number." << endl;
        return;
    }

    if (movieIndex < 0 || movieIndex >= static_cast<int>(movies.size()))
    {
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    // Find the movie with the given index
    Movie &movie = movies[movieIndex];

    cout << "Select a date to cancel reservation:" << endl;
    for (size_t i = 0; i < movie.dates.size(); ++i)
    {
        cout << i + 1 << ". " << movie.dates[i] << endl;
    }

    int dateIndex;
    cout << "Enter your choice: ";
    cin >> dateIndex;
    dateIndex--;

    if (dateIndex < 0 || dateIndex >= static_cast<int>(movie.dates.size()))
    {
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    cout << "Select a round to cancel reservation:" << endl;
    for (size_t i = 0; i < movie.availableSeats[dateIndex].size(); ++i)
    {
        cout << i + 1 << ". Round " << i + 1 << " - " << movie.availableSeats[dateIndex][i] << " seats left" << endl;
    }

    int roundIndex;
    cout << "Enter your choice: ";
    cin >> roundIndex;
    roundIndex--;

    if (roundIndex < 0 || roundIndex >= static_cast<int>(movie.availableSeats[dateIndex].size()))
    {
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    int numSeats;
    cout << "Enter the number of seats to cancel: ";
    cin >> numSeats;

    if (numSeats <= 0 || numSeats > 10 - movie.availableSeats[dateIndex][roundIndex])
    {
        cout << "Invalid number of seats to cancel." << endl;
        return;
    }

    movie.availableSeats[dateIndex][roundIndex] += numSeats;
    cout << "Successfully canceled " << numSeats << " seats for " << movie.title << " on "
         << movie.dates[dateIndex] << " for round " << roundIndex + 1 << "." << endl;
}

int main()
{
    vector<Movie> movies = {
        {"Poor Things", {"2024-03-01", "2024-03-02", "2024-03-03"}, {{10, 10, 10, 10}, {10, 10, 10, 10}, {10, 10, 10, 10}}},
        {"Homroi", {"2024-03-01", "2024-03-02", "2024-03-03"}, {{10, 10, 10, 10}, {10, 10, 10, 10}, {10, 10, 10, 10}}},
        {"4KingsII", {"2024-03-01", "2024-03-02", "2024-03-03"}, {{10, 10, 10, 10}, {10, 10, 10, 10}, {10, 10, 10, 10}}}};
    string filename = "save.txt";
    loadFromFile(movies, filename);
    int choice;
    do
    {
        cout << "1. View Schedule" << endl;
        cout << "2. Make Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Save data" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) // Check if the input failed
        {
            cin.clear();                                         // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue; // Continue to the next iteration of the loop
        }

        switch (choice)
        {
        case 1:
            displaySchedule(movies);
            break;
        case 2:
            makeReservation(movies);
            break;
        case 3:
            cancelReservation(movies);
        case 4:
            saveToFile(movies, filename);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 5);



    return 0;
}