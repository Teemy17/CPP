#include <iostream>

using namespace std;

class Point {
private:
    int xCoordinate;
    int yCoordinate;

public:
    Point() : xCoordinate(0), yCoordinate(0) {}

    friend ostream& operator<<(ostream& os, const Point& point);
    friend istream& operator>>(istream& is, Point& point);
};

ostream& operator<<(ostream& os, const Point& point) {
    os << "(" << point.xCoordinate << ", " << point.yCoordinate << ")";
    return os;
}

istream& operator>>(istream& is, Point& point) {
    char ch;
    is >> point.xCoordinate;
    if (is.fail()) {
        is.setstate(ios::failbit);
        return is;
    }
    is >> point.yCoordinate;
    if (is.fail()) {
        is.setstate(ios::failbit);
        return is;
    }
    return is;
}

int main() {
    Point point;


    cout << "Enter a point (x, y): ";
    cin >> point;
    if (cin.fail()) {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        return 1;
    }

    cout << "Point entered: " << point << endl;

    return 0;
}
