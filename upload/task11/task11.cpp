#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double number;

    cout << "Integer Checker" << endl;
    cout << "Enter a number: ";
    cin >> number;

    // A number is an integer if it is equal to itself when the fractional part is removed.
    if (number == floor(number)) {
        cout << "The number " << number << " is an integer." << endl;
    } else {
        cout << "The number " << number << " is not an integer." << endl;
    }

    return 0;
}
