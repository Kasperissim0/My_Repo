#include <SFML/Graphics.hpp> // For Graphics
#include <chrono>            // For time manipulation + delaying actions
#include <cmath>             // For mathematical calculations
#include <cstdlib>           // For clearing the terminal
#include <iomanip>           // For formatting output nicely
#include <iostream>          // For output and input
#include <limits>            // For clearing the input buffer
#include <random>            // For generating random numbers
#include <string>            // For strings
#include <thread>            // For time manipulation + delaying actions
#include <vector>            // For vectors only

using namespace std;

int getRandomAmount (int min, int max) {
  // define
}

int main () {
  int amountOfCoinTypes = getRandomAmount ();
  int coinTypes = [amountOfCoinTypes];
  int amountToPay = getRandomAmount ();

  return 0;
}

// the point here is to have a random amount of coin denominations (1, 3, 6, 12) and a random price to pay 134_+_++
// and the the task is to figure out the smallest amount of coins to pay (e.g. 3-12, 5-6...)

// ok, let's do this with a given problem:

int amountOfCoinTypes = 4;
int coinTypes = [ 2, 3, 9, 14 ];
int amountToPay = 53323;

// so the steps are
// 1. amountToPay / largest of coinTypes
// push amount into a hash list
// 2. amountToPay %= largest of coinTypes
// 3. if amountToPay < largest of coinTypes
// repeat ⬆️
// get one smaller + repeat ⬆️