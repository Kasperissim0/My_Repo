#include <iostream>

using namespace std;

int main() {
    int n;

    cout << "Enter a natural number n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive natural number." << endl;
        return 1;
    }

    cout << "\nAddition modulo " << n << ":" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (i + j) % n << " ";
        }
        cout << endl;
    }

    cout << "\nMultiplication modulo " << n << ":" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (i * j) % n << " ";
        }
        cout << endl;
    }

    return 0;
}
