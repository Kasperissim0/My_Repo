#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

int main() {
    double p, q, discriminant;

    cout << "Enter coefficients p and q for the quadratic equation x^2 + px + q = 0: ";
    cin >> p >> q;

    discriminant = p * p - 4 * q;

    if (discriminant >= 0) {
        double x1 = (-p + sqrt(discriminant)) / 2;
        double x2 = (-p - sqrt(discriminant)) / 2;
        cout << "Real roots: x1 = " << x1 << ", x2 = " << x2 << endl;
    } else {
        // Complex solutions
        complex<double> x1 = (-p + sqrt(complex<double>(discriminant))) / 2.0;
        complex<double> x2 = (-p - sqrt(complex<double>(discriminant))) / 2.0;
        cout << "Complex roots: x1 = " << x1 << ", x2 = " << x2 << endl;
    }

    return 0;
}