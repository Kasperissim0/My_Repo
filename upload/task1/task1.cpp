#include <iostream>

using namespace std;

int main() {
    double num1, num2, num3;

    cout << "Enter three double numbers: ";
    cin >> num1 >> num2 >> num3;

    // Sort without logical operators
    if (num1 > num2) {
        double temp = num1;
        num1 = num2;
        num2 = temp;
    }
    if (num2 > num3) {
        double temp = num2;
        num2 = num3;
        num3 = temp;
    }
    if (num1 > num2) {
        double temp = num1;
        num1 = num2;
        num2 = temp;
    }

    cout << "Sorted numbers: " << num1 << ", " << num2 << ", " << num3 << endl;

    return 0;
}