#include <iostream>
#include <string>

using namespace std;

bool intTest(int n, char c) {
    string numberString = to_string(n);
    for (char digit : numberString) {
        if (digit == c) {
            return true;
        }
    }
    return false;
}

int main() {
    int number;
    char digit;
    cout << "Enter an integer and a digit to search for: ";
    cin >> number >> digit;

    if (intTest(number, digit)) {
        cout << "The digit '" << digit << "' was found in " << number << "." << endl;
    } else {
        cout << "The digit '" << digit << "' was not found in " << number << "." << endl;
    }

    return 0;
}
