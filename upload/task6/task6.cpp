#include <iostream>

using namespace std;

int main() {
    double lowerLimit, upperLimit;

    cout << "Enter the lower limit of the interval: ";
    cin >> lowerLimit;
    cout << "Enter the upper limit of the interval: ";
    cin >> upperLimit;

    if (lowerLimit > upperLimit) {
        double temp = lowerLimit;
        lowerLimit = upperLimit;
        upperLimit = temp;
        cout << "Interval limits swapped to ensure lowerLimit <= upperLimit." << endl;
    }

    int smallerCount = 0;
    int inIntervalCount = 0;
    int largerCount = 0;
    double number;

    cout << "Enter numbers (Ctrl+D or Ctrl+Z to end input):" << endl;
    while (cin >> number) {
        if (number < lowerLimit) {
            smallerCount++;
        } else if (number > upperLimit) {
            largerCount++;
        } else {
            inIntervalCount++;
        }
    }

    cout << "\nResults:" << endl;
    cout << "Numbers smaller than " << lowerLimit << ": " << smallerCount << endl;
    cout << "Numbers within [" << lowerLimit << ", " << upperLimit << "]: " << inIntervalCount << endl;
    cout << "Numbers larger than " << upperLimit << ": " << largerCount << endl;

    return 0;
}
