#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << "Almost perfect numbers in the range 0 to 10^7:" << endl;

    for (int n = 1; n <= 10000000; ++n) {
        int sumOfDivisors = 1; // Start with 1 as a divisor for all n > 1
        if (n > 1) {
            int limit = sqrt(n);
            for (int i = 2; i <= limit; ++i) {
                if (n % i == 0) {
                    sumOfDivisors += i;
                    if (i * i != n) {
                        sumOfDivisors += n / i;
                    }
                }
            }
        }

        if (sumOfDivisors == n - 1) {
            cout << n << endl;
        }
    }

    return 0;
}