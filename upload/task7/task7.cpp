#include <iostream>

using namespace std;

int main() {
    long long n0;

    cout << "Enter a positive starting value (n0): ";
    cin >> n0;

    if (n0 <= 0) {
        cout << "Please enter a positive starting value." << endl;
        return 1;
    }

    long long currentN = n0;
    int steps = 0;

    cout << "Sequence: " << currentN;

    while (currentN != 1) {
        if (currentN % 2 == 0) {
            currentN /= 2;
        } else {
            currentN = 3 * currentN + 1;
        }
        cout << " -> " << currentN;
        steps++;

        // Added a safeguard for extremely long sequences or if the conjecture fails
        if (steps > 10000) {
            cout << "\nSequence exceeded 10000 steps, stopping to prevent infinite loop." << endl;
            return 0;
        }
    }

    cout << "\nReached 1 in " << steps << " steps." << endl;

    return 0;
}
