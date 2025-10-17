#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x, a4, a3, a2, a1, a0;

    cout << "Enter the value of x: ";
    cin >> x;
    cout << "Enter the coefficient for x^4: ";
    cin >> a4;
    cout << "Enter the coefficient for x^3: ";
    cin >> a3;
    cout << "Enter the coefficient for x^2: ";
    cin >> a2;
    cout << "Enter the coefficient for x^1: ";
    cin >> a1;
    cout << "Enter the constant term (a0): ";
    cin >> a0;

    double result = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;

    cout << "The value of the polynomial at x = " << x << " is: " << result << endl;

    return 0;
}