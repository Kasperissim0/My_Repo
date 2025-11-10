#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addStrings(string num1, string num2) {
    string sum = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        int currentSum = digit1 + digit2 + carry;
        sum += to_string(currentSum % 10);
        carry = currentSum / 10;
    }
    reverse(sum.begin(), sum.end());
    return sum;
}

int main() {
    string num1, num2;
    cout << "Enter two large numbers to add:" << endl;
    cin >> num1 >> num2;
    cout << "Sum: " << addStrings(num1, num2) << endl;
    return 0;
}
