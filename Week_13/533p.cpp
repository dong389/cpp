#include <iostream>
using namespace std;

class TimeHMS {
    int hour, min, sec;
    // Helper function to normalize time
    void normalize() {
        int totalSec = sec + min * 60 + hour * 3600;
        if (totalSec < 0) totalSec = 0; // Prevent negative time
        hour = totalSec / 3600;
        totalSec %= 3600;
        min = totalSec / 60;
        sec = totalSec % 60;
    }

public:
    TimeHMS(int h=0, int m=0, int s=0) : hour(h), min(m), sec(s) {
        normalize();
    }

    // (1) Addition operator
    TimeHMS operator+(const TimeHMS& other) const {
        return TimeHMS(hour + other.hour, min + other.min, sec + other.sec);
    }

    // (2) Subtraction operator
    TimeHMS operator-(const TimeHMS& other) const {
        return TimeHMS(hour - other.hour, min - other.min, sec - other.sec);
    }

    // (3) Equality and inequality operators
    bool operator==(const TimeHMS& other) const {
        return hour == other.hour && min == other.min && sec == other.sec;
    }

    bool operator!=(const TimeHMS& other) const {
        return !(*this == other);
    }

    // (4) Pre-increment/decrement operators
    TimeHMS& operator++() { // pre-increment
        hour++;
        normalize();
        return *this;
    }

    TimeHMS& operator--() { // pre-decrement
        hour--;
        normalize();
        return *this;
    }

    // (5) Post-increment/decrement operators
    TimeHMS operator++(int) { // post-increment
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }

    TimeHMS operator--(int) { // post-decrement
        TimeHMS temp = *this;
        sec--;
        normalize();
        return temp;
    }

    // (6) Index operator
    int operator[](int index) const {
        switch(index) {
            case 0: return hour;
            case 1: return min;
            case 2: return sec;
            default: throw out_of_range("Invalid index");
        }
    }

    // (7) Conversion to int (total seconds)
    operator int() const {
        return hour * 3600 + min * 60 + sec;
    }

    // (8) Conversion to double (hours)
    operator double() const {
        return hour + min/60.0 + sec/3600.0;
    }

    // (9) Multiplication with integer
    friend TimeHMS operator*(int n, const TimeHMS& t) {
        return TimeHMS(t.hour * n, t.min * n, t.sec * n);
    }

    // (10) Stream operators
    friend istream& operator>>(istream& is, TimeHMS& t) {
        is >> t.hour >> t.min >> t.sec;
        t.normalize();
        return is;
    }

    friend ostream& operator<<(ostream& os, const TimeHMS& t) {
        os << t.hour << "h " << t.min << "m " << t.sec << "s";
        return os;
    }
};

// (11) Test program
int main() {
    TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3;

    // Test (1) Addition
    cout << "Test 1: Addition\n";
    t3 = t1 + t2;
    cout << t1 << " + " << t2 << " = " << t3 << endl;

    // Test (2) Subtraction
    cout << "\nTest 2: Subtraction\n";
    t3 = t2 - t1;
    cout << t2 << " - " << t1 << " = " << t3 << endl;

    // Test (3) Equality/Inequality
    cout << "\nTest 3: Equality\n";
    cout << t1 << " == " << t2 << ": " << (t1 == t2 ? "true" : "false") << endl;
    cout << t1 << " != " << t2 << ": " << (t1 != t2 ? "true" : "false") << endl;

    // Test (4) Pre-increment/decrement
    cout << "\nTest 4: Pre-increment/decrement\n";
    cout << "t1: " << t1 << endl;
    cout << "++t1: " << ++t1 << endl;
    cout << "--t1: " << --t1 << endl;

    // Test (5) Post-increment/decrement
    cout << "\nTest 5: Post-increment/decrement\n";
    cout << "t1: " << t1 << endl;
    cout << "t1++: " << t1++ << endl;
    cout << "After t1++: " << t1 << endl;
    cout << "t1--: " << t1-- << endl;
    cout << "After t1--: " << t1 << endl;

    // Test (6) Index operator
    cout << "\nTest 6: Index operator\n";
    cout << "t1[0] (hour): " << t1[0] << endl;
    cout << "t1[1] (min): " << t1[1] << endl;
    cout << "t1[2] (sec): " << t1[2] << endl;

    // Test (7) Int conversion
    cout << "\nTest 7: Int conversion\n";
    cout << "t1 in seconds: " << (int)t1 << endl;

    // Test (8) Double conversion
    cout << "\nTest 8: Double conversion\n";
    cout << "t1 in hours: " << (double)t1 << endl;

    // Test (9) Multiplication
    cout << "\nTest 9: Multiplication\n";
    t3 = 2 * t1;
    cout << "2 * " << t1 << " = " << t3 << endl;

    // Test (10) Input
    cout << "\nTest 10: Input\nEnter hour min sec: ";
    cin >> t3;
    cout << "You entered: " << t3 << endl;

    return 0;
}