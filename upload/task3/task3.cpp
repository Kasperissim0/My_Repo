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

  int reversedNumber = digit3 * 100 + digit2 * 10 + digit1;

  cout << "The reversed number is: " << reversed_number << endl;

  return 0;
}
