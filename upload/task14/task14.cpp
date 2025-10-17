#include <iostream>

using namespace std;

int main() {
    // Max 3 fundamental variables, max 4 multiplications.
    // Using Horner's method.
    // Variables: x (input), coeff (input), result (accumulator)
    double x, coeff, result;

    cout << "Enter the value of x: ";
    cin >> x;

    cout << "Enter the coefficient for x^4: ";
    cin >> coeff;
    result = coeff;

    cout << "Enter the coefficient for x^3: ";
    cin >> coeff;
    result = result * x + coeff; // 1st multiplication

    cout << "Enter the coefficient for x^2: ";
    cin >> coeff;
    result = result * x + coeff; // 2nd multiplication

    cout << "Enter the coefficient for x^1: ";
    cin >> coeff;
    result = result * x + coeff; // 3rd multiplication

    cout << "Enter the constant term (a0): ";
    cin >> coeff;
    result = result * x + coeff; // 4th multiplication

    cout << "The value of the polynomial at x = " << x << " is: " << result << endl;

    return 0;
}