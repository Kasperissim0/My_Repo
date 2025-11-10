#include <iostream>
#include <numeric> // For std::gcd in C++17, but we'll write our own for the exercise

using namespace std;

int greatestCommonDivisor(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int numerator, denominator;
    cout << "Enter the numerator and denominator of a fraction: ";
    cin >> numerator >> denominator;

    if (denominator == 0) {
        cerr << "Error: Denominator cannot be zero." << endl;
        return 1;
    }

    int commonDivisor = greatestCommonDivisor(numerator, denominator);
    cout << "Reduced fraction: " << numerator / commonDivisor << "/" << denominator / commonDivisor << endl;

    return 0;
}
