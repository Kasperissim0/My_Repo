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

int GetRandomNumber(const int MinNumber = 1, const int MaxNumer = 999999999, const bool ReturnPrime = false) {

  random_device RandomSeed;
  mt19937 GenerateNumber(RandomSeed());
  uniform_int_distribution<> DistributionRange(MinNumber, MaxNumer);
  int OriginalNumber = DistributionRange(GenerateNumber);

  if (ReturnPrime) { // If Prime

    bool NumberIsPrime = true;

    if (OriginalNumber < 2) NumberIsPrime = false; // Not Prime

    for (int i = 2; i <= sqrt(OriginalNumber); i++) { // Check All Possibilities

      if (OriginalNumber % i == 0) { // Not Prime
          NumberIsPrime = false; 
          break;
      }

    }

    return NumberIsPrime ? OriginalNumber : GetRandomNumber(MinNumber, MaxNumer, true); // Prime OR Run Again
  }

  else {

    return OriginalNumber; // Normal Number

  }
}

void DisplayData() {



}



int main () {
  
  system("clear");

  const int ArraySize = GetRandomNumber(1, 100);
  int array[ArraySize];


  return 0;
}