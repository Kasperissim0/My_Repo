#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// From task 15
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

string multiplyStrings(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";
    if (num1 == "1") return num2;
    if (num2 == "1") return num1;

    string result = "0";
    for (int i = num2.length() - 1; i >= 0; --i) {
        int digit2 = num2[i] - '0';
        string partialProduct = "";
        int carry = 0;
        for (int j = num1.length() - 1; j >= 0; --j) {
            int digit1 = num1[j] - '0';
            int product = digit1 * digit2 + carry;
            partialProduct = to_string(product % 10) + partialProduct;
            carry = product / 10;
        }
        if (carry > 0) {
            partialProduct = to_string(carry) + partialProduct;
        }
        for (int k = 0; k < num2.length() - 1 - i; ++k) {
            partialProduct += "0";
        }
        result = addStrings(result, partialProduct);
    }
    return result;
}

int main() {
    string num1, num2;
    cout << "Enter two large numbers to multiply:" << endl;
    cin >> num1 >> num2;
    cout << "Product: " << multiplyStrings(num1, num2) << endl;
    return 0;
}
