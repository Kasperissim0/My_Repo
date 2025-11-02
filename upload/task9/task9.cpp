#include <iostream>
#include <limits>

using namespace std;

int main() {
    double number;
    double max = -numeric_limits<double>::infinity();
    double min = numeric_limits<double>::infinity();
    double sum = 0;
    int count = 0;

    cout << "Enter double values (Ctrl+D or Ctrl+Z to end input):" << endl;

    while (cin >> number) {
        if (number > max) {
            max = number;
        }
        if (number < min) {
            min = number;
        }
        sum += number;
        count++;
    }

    if (count > 0) {
        double mean = sum / count;
        cout << "\nMaximum: " << max << endl;
        cout << "Minimum: " << min << endl;
        cout << "Mean: " << mean << endl;
    } else {
        cout << "\nNo numbers were entered." << endl;
    }

    return 0;
}
