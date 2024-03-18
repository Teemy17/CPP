#include <iostream>
#include <vector>
#include <algorithm> // For sorting (median calculation)
#include <cmath>     // For sqrt and pow (standard deviation)
#include <iomanip>   // For setprecision (output formatting)

using namespace std;

int main() {
    vector<double> numbers;
    double input;

    // Get input from the user
    cout << "Enter a sequence of numbers (enter any non-number to stop): ";
    while (cin >> input) {
        numbers.push_back(input);
    }

    // Calculate mean
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    double mean = sum / numbers.size();

    // Calculate median
    sort(numbers.begin(), numbers.end());
    double median = numbers.size() % 2 == 0
                        ? (numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2]) / 2.0
                        : numbers[numbers.size() / 2];

    // Calculate standard deviation
    double squared_deviations_sum = 0.0;
    for (double num : numbers) {
        squared_deviations_sum += pow(num - mean, 2);
    }
    double standard_deviation = sqrt(squared_deviations_sum / numbers.size());

    // Find minimum and maximum
    double minimum = *min_element(numbers.begin(), numbers.end());
    double maximum = *max_element(numbers.begin(), numbers.end());

    // Display results with two digits of precision
    cout << fixed << setprecision(2); 
    cout << "\nMean: " << mean << endl;
    cout << "Median: " << median << endl;
    cout << "Standard Deviation: " << standard_deviation << endl;
    cout << "Minimum: " << minimum << endl;
    cout << "Maximum: " << maximum << endl;

    return 0;
}

