#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double number;

    cout << "Integer Checker" << endl;
    cout << "Enter a number: ";
    cin >> number;

    // A number is an integer if it is equal to itself when the fractional part is removed.
    // floor(number) gives the greatest integer less than or equal to the number.
    // For example, floor(3.7) is 3.0, floor(5.0) is 5.0, floor(-2.3) is -3.0
    // So, we can check if the number is equal to its floor value.
    if (number == floor(number)) {
        cout << "The number " << number << " is an integer." << endl;
    } else {
        cout << "The number " << number << " is not an integer." << endl;
    }

    return 0;
}
