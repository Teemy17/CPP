#include <iostream>
#include <vector>
using namespace std;

void lshift(std::vector<int>& vec, int n) {
    if (n >= vec.size()) {
        vec.clear(); 
    } else {
        vec.erase(vec.begin(), vec.begin() + n); 
    }
}

void rshift(std::vector<int>& vec, int n) {
    vec.erase(vec.begin(), vec.begin() + vec.size() - n); 
    vec.insert(vec.begin(), n, 0);
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Original sequence: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    lshift(vec, 3);
    cout << "After lshift by 2: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    vec = {1, 2, 3, 4, 5};

    rshift(vec, 4);
    cout << "After rshift by 3: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}



