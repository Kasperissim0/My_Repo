#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int m, n;
  cout << "Enter a number (m): ";
  cin >> m;
  cout << "Enter the digit position (n, from the right): ";
  cin >> n;

  if (n <= 0) {
    cout << "Invalid digit position." << endl;
    return 1;
  }

  int divisor = pow(10, n - 1);
  if (m < divisor && n > 1) {
      cout << "The number " << m << " does not have a " << n << "th digit." << endl;
      return 0;
  }
  
  int digit = (m / divisor) % 10;

  cout << "The " << n << "th digit of " << m << " is " << digit << endl;

  return 0;
}
