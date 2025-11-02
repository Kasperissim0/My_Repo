#include <iostream>
#include <string>

using namespace std;

void printDigit(int digit) {
    switch (digit) {
        case 0: cout << "zero"; break;
        case 1: cout << "one"; break;
        case 2: cout << "two"; break;
        case 3: cout << "three"; break;
        case 4: cout << "four"; break;
        case 5: cout << "five"; break;
        case 6: cout << "six"; break;
        case 7: cout << "seven"; break;
        case 8: cout << "eight"; break;
        case 9: cout << "nine"; break;
    }
}

int main() {
    int fourDigitNumber;

    cout << "Enter a four-digit integer: ";
    cin >> fourDigitNumber;

    if (fourDigitNumber < 1000 || fourDigitNumber > 9999) {
        cout << "Please enter a valid four-digit number." << endl;
        return 1;
    }

    int digit1 = fourDigitNumber / 1000;
    int digit2 = (fourDigitNumber / 100) % 10;
    int digit3 = (fourDigitNumber / 10) % 10;
    int digit4 = fourDigitNumber % 10;

    printDigit(digit1);
    cout << "-";
    printDigit(digit2);
    cout << "-";
    printDigit(digit3);
    cout << "-";
    printDigit(digit4);
    cout << endl;

    return 0;
}