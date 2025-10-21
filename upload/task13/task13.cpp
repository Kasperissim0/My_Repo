#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double x;

    cout << "Rounding Expression" << endl;
    cout << "Enter a positive number to round: ";
    cin >> x;

    if (x < 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }

    // The expression to round a positive number x correctly (round up from 0.5 and down below)
    // is floor(x + 0.5).
    double roundedX = floor(x + 0.5);

    cout << fixed << setprecision(1);
    cout << "Original number: " << x << endl;
    cout << "Rounded number: " << roundedX << endl;

    return 0;
}
