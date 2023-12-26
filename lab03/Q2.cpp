#include <iostream>
#include <string>
using namespace std;

class GuessNumberGame {
    private:
        int secret_number;
        int guess_attemps;

    public:
        GuessNumberGame() {
            srand(time(0));
            secret_number = 1 + (rand() % 100);
            guess_attemps = 0;
        }

        void guess(int guess_number) {
            guess_attemps++;
            
            if (guess_number > secret_number) {
                cout << "Too high! Try again"<< endl;
            } else if (guess_number < secret_number) {
                cout << "Too low! Try again" << endl;
            } else {
                cout << "Congratulations! You win.";
                exit(0);
            }

            if (guess_attemps == 10) {
                cout << "You lose!" << endl;
                exit(0);
            }
        }    
};

int main() {
    GuessNumberGame gng;
    while (true) {
        cout << "Guess the number (between 0 and 100): ";
        int guess_number;
        cin >> guess_number;
        if (guess_number < 0 || guess_number > 100) {
            cout << "Invalid input!" << endl;
            break;
        } else if (cin.fail()) {
            cout << "Invalid input!" << endl;
            break;
        }
        gng.guess(guess_number);
    }
    return 0;
}
