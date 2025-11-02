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

    if (n % 2 != 0) {
        cout << "Largest power of two that divides " << n << " is: 1" << endl;
    } else {
        int tempN = n;
        int largestPowerOfTwo = 1;
        while (tempN % 2 == 0) {
            tempN /= 2;
            largestPowerOfTwo *= 2;
        }
        cout << "Largest power of two that divides " << n << " is: " << largestPowerOfTwo << endl;
    }

    return 0;
}