#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string decimalToBinary(string dec) {
    long long n = stoll(dec);
    if (n == 0) return "0";
    string binaryString = "";
    while (n > 0) {
        binaryString = to_string(n % 2) + binaryString;
        n /= 2;
    }
    return binaryString;
}

string binaryToDecimal(string bin) {
    long long dec = 0;
    int power = 0;
    for (int i = bin.length() - 1; i >= 0; --i) {
        if (bin[i] == '1') {
            dec += (1LL << power);
        }
        power++;
    }
    return to_string(dec);
}

int main() {
    string decInput, binInput;
    cout << "Enter a decimal number to convert to binary: ";
    cin >> decInput;
    cout << "Binary: " << decimalToBinary(decInput) << endl;

    cout << "Enter a binary number to convert to decimal: ";
    cin >> binInput;
    cout << "Decimal: " << binaryToDecimal(binInput) << endl;

    return 0;
}
