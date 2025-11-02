#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string numberStr;

    cout << "Enter an integer: ";
    cin >> numberStr;

    int inversionCount = 0;
    for (size_t i = 0; i < numberStr.length(); ++i) {
        for (size_t j = i + 1; j < numberStr.length(); ++j) {
            if (numberStr[i] > numberStr[j]) {
                inversionCount++;
            }
        }
    }

    cout << "Number of inversions: " << inversionCount << endl;

    return 0;
}