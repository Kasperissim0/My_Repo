#include <iostream>

using namespace std;

int mult(int m, int n) {
    if (n == 0) {
        return 0;
    }
    if (n < 0) {
        return -mult(m, -n);
    }
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result += m;
    }
    return result;
}

long long power(int m, unsigned int n) {
    if (n == 0) {
        return 1;
    }
    long long result = 1;
    for (unsigned int i = 0; i < n; ++i) {
        result = mult(result, m);
    }
    return result;
}

int main() {
    int m, n;
    cout << "Enter two integers for multiplication: ";
    cin >> m >> n;
    cout << "Product: " << mult(m, n) << endl;

    cout << "Enter base and exponent for power calculation: ";
    cin >> m >> n;
    cout << "Power: " << power(m, n) << endl;

    return 0;
}
