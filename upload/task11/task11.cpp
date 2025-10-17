#include <iostream>

using namespace std;

int main() {
    double v1, v2, v3, v4, v5;
    cout << "Enter five measured values, separated by spaces: ";
    cin >> v1 >> v2 >> v3 >> v4 >> v5;

    double sum = v1 + v2 + v3 + v4 + v5;
    double mean = sum / 5.0;

    cout << "The mean value is: " << mean << endl;

    return 0;
}