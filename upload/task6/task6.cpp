#include <iostream>

using namespace std;

int main() {
    double a, b, c, x;

    cout << "Calculate ax^2 + bx + c using Horner's method." << endl;
    cout << "Enter coefficient a: ";
    cin >> a;
    cout << "Enter coefficient b: ";
    cin >> b;
    cout << "Enter coefficient c: ";
    cin >> c;
    cout << "Enter value for x: ";
    cin >> x;

    // Horner's method: (a*x + b)*x + c
    double result = (a * x + b) * x + c;

    cout << "The result of (" << a << " * " << x << "^2) + (" << b << " * " << x << ") + " << c << " is: " << result << endl;

    return 0;
}
