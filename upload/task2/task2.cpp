#include <iostream>

using namespace std;

int main() {
  int number;
  cout << "Enter a three-digit number: ";
  cin >> number;

  if (number < 100 || number > 999) {
    cout << "The number is not a three-digit number." << endl;
    return 1;
  }

  int digit1 = number / 100;
  int digit2 = (number / 10) % 10;
  int digit3 = number % 10;
  int sum = digit1 + digit2 + digit3;

  cout << "The sum of the digits is " << sum << endl;

  if (sum % 3 == 0) {
    cout << number << " is divisible by 3." << endl;
  } else {
    cout << number << " is not divisible by 3." << endl;
  }

  return 0;
}
