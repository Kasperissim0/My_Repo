#include <iostream>

using namespace std;

int main() {
    int num1, num2;

    cout << "Factor Checker" << endl;
    cout << "Enter the first whole number: ";
    cin >> num1;
    cout << "Enter the second whole number: ";
    cin >> num2;

    if (num2 == 0) {
        cout << "Cannot check for factor with zero." << endl;
        return 1;
    }

    if (num1 % num2 == 0) {
        cout << num2 << " divides " << num1 << "." << endl;
    } else {
        cout << num2 << " does not divide " << num1 << "." << endl;
    }

    return 0;
}
