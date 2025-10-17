#include <iostream>

using namespace std;

int main() {
    long long n;
    cout << "Enter a natural number n: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative number." << endl;
        return 1;
    }

    long long sum = n * (n + 1) / 2;

    cout << "The sum of all natural numbers up to " << n << " is: " << sum << endl;

    return 0;
}