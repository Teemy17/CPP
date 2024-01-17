#include <iostream>
#include <string>
using namespace std;

class SimpleQuiz
{
private:
    string question;
    string choices[3];
    char CorrectAnswer;

public:
    SimpleQuiz(string q, string a, string b, string c, char correct) : question(q), CorrectAnswer(correct)
    {
        choices[0] = a;
        choices[1] = b;
        choices[2] = c;
    }

    void display(int question_number)
    {
        cout << "Question " << question_number << ": " << question << endl;
        cout << "a. " << choices[0] << endl;
        cout << "b. " << choices[1] << endl;
        cout << "c. " << choices[2] << endl;
    }

    bool check_answer(char answer)
    {
        return answer == CorrectAnswer;
    }
};

int main()
{
    SimpleQuiz questions[5] = {
        SimpleQuiz("What is the capital of France?", "Berlin", "Paris", "London", 'b'),
        SimpleQuiz("Which planet is known as the Red Planet?", "Mars", "Jupiter", "Saturn", 'a'),
        SimpleQuiz("What is the largest mammal?", "Elephant", "Blue Whale", "Giraffe", 'b'),
        SimpleQuiz("Who wrote 'Hamlet'?", "Mark Twain", "Charles Dickens", "William Shakespeare", 'c'),
        SimpleQuiz("What is the chemical symbol for water?", "H2O", "CO2", "O2", 'a')};

    int score = 0;
    int question_number = 1;

    while (question_number <= 5)
    {
        questions[question_number - 1].display(question_number);
        char answer;
        cout << "Enter your answer (a, b, c): ";
        cin >> answer;

        switch (answer)
        {
        case 'a':
        case 'b':
        case 'c':
            if (questions[question_number - 1].check_answer(answer))
            {
                cout << "Correct!" << endl;
                score++;
            }
            else
            {
                cout << "Wrong!" << endl;
            }
            question_number++;
            break;
        default:
            cout << "Invalid input" << endl;
        }
    }

    cout << "Your total score: " << score << "/5" << endl;

    return 0;
}
