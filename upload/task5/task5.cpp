#include <iostream>

using namespace std;

int main() {
    double celsius;
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;

    double fahrenheit = celsius * 9.0 / 5.0 + 32;

    cout << celsius << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit." << endl;

    return 0;
}