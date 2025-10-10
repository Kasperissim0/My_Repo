#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions
#include <cmath> // For mathematical calculations
#include <random> // For generating random numbers
#include <SFML/Graphics.hpp> // For Graphics

using namespace std;

int main () {
  int factorialAmount = 20;
  int64_t tempFactorial = 1;

  system("clear");

  for (int i = 1; i <= factorialAmount; i++) {
    tempFactorial *= i;
    cout << endl << "Factorial for " << i << "! - " << tempFactorial << endl;
  }
  
  return 0;

}