#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long binomial(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

string expandBinomial(int n) {
    if (n == 0) return "1";
    string result = "";
    for (int k = 0; k <= n; ++k) {
        long long coeff = binomial(n, k);
        if (coeff > 0) {
            if (!result.empty()) {
                result += "+";
            }
            if (coeff > 1) {
                result += to_string(coeff);
            }
            if (n - k > 0) {
                result += "a";
                if (n - k > 1) {
                    result += "^" + to_string(n - k);
                }
            }
            if (k > 0) {
                result += "b";
                if (k > 1) {
                    result += "^" + to_string(k);
                }
            }
        }
    }
    return result;
}

int main() {
    int n;
    cout << "Enter the power for (a+b)^n: ";
    cin >> n;
    cout << expandBinomial(n) << endl;
    return 0;
}
