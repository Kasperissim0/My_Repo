#include <iostream>

using namespace std;

// Function to calculate base^exponent without using cmath::pow
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) {
        res *= base;
    }
    return res;
}

int main() {
    int n;
    long long totalSum = 0;

    cout << "Enter a natural number n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive natural number." << endl;
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        totalSum += power(i, i);
    }

    cout << "The sum 1^1 + 2^2 + ... + n^n is: " << totalSum << endl;

    return 0;
}