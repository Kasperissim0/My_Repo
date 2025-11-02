#include <iostream>

using namespace std;

int main() {
    int n;

    cout << "Enter a natural number: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive natural number." << endl;
        return 1;
    }

    int sumOfDivisors = 0;
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            sumOfDivisors += i;
        }
    }

    cout << n << " is a ";
    if (sumOfDivisors == n) cout <<     "perfect";
    else if (sumOfDivisors < n) cout << "deficient"; 
    else cout <<                        "abundant";
    cout << " number." << endl;

    return 0;
}