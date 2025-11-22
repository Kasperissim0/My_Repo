#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string formatNumber(int n) {
    string numberString = to_string(n);
    string reversedString = numberString;
    reverse(reversedString.begin(), reversedString.end());

    string result = "";
    for (char c : reversedString) {
        result += c;
        result += ' ';
    }
    result += "* ";
    for (char c : numberString) {
        result += c;
        result += ' ';
    }
    result.pop_back(); // Remove trailing space
    return result;
}

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;
    cout << formatNumber(number) << endl;
    return 0;
}
