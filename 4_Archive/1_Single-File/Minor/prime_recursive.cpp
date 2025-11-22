#include <iostream> // For output and input

using namespace std;

bool IsPrime (int64_t number, int64_t divisor = 2) {

  if (number <= 1) return false; // hard code 0 and 1 as not prime

  if (number == 2) return true; // hard code 2 as prime

  if (number % divisor == 0) return false; // fully divisible => composite

  if (divisor == number - 1) return true; // all numbers checked => prime

  return IsPrime(number, divisor + 1); // recursion

}

int main () {

  int64_t number; // big ass number

  system("clear");

  cin >> number;

  cout << number << " Is" << ((IsPrime(number)) ? " " : " NOT ") << "Prime" << endl;
  
  return 0;

}