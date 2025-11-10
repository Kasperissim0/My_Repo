#include <iostream>

using namespace std;

long long factorial(int n) {
    if (n < 0) return -1; // Or throw an exception
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long long binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n, k;
    cout << "Enter n and k for binomial coefficient (n choose k): ";
    cin >> n >> k;
    long long result = binomialCoefficient(n, k);
    cout << "Result: " << result << endl;
    return 0;
}
