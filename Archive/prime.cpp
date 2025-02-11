#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions
#include <cmath> // For mathematical calculations

using namespace std;

struct NumberData { // Define Structure

  bool NumberIsPrime;
  bool NumberIsONE;
  vector<int> factors;

};

int CalculateRoot (int& TestedNumber) { // Change this to your own formula

  return sqrt(TestedNumber);

}
NumberData FindNumberProperties (int& TestedNumber) { // Calculate If The Number Is Prime + it's Factors

  int RootOfTheNumber = CalculateRoot(TestedNumber);
  NumberData NumberProperties;
  NumberProperties.NumberIsPrime = true;

  if (TestedNumber == 1) { // Exception 

    NumberProperties.NumberIsPrime = false;
    NumberProperties.NumberIsONE = true;
    return NumberProperties;

  }

  for (int a = 2; a <= RootOfTheNumber; a++) { // Check Every Number Bigger Than 1, but Smaller Than the Number's Root

    if (TestedNumber % a == 0) { // If it is divisible add it to the factor list, and deduce the number is not prim

      NumberProperties.NumberIsPrime = false;
      NumberProperties.factors.push_back(a);

    }

  }

  return NumberProperties;

}


int main () {

  NumberData properties;

  int number;
  bool NumberConfirmed = false;

  while(!NumberConfirmed) { // Get Number From User

    system("clear");
    cout << "Insert A Number: ";
    cin >> number;

    if (number <= 0 || cin.fail()) {

      system("clear");
      cin.clear();
      cin.ignore(numeric_limits<int>::max(), '\n');
      cin.clear();
      cout << "Invalid Input" << endl;
      this_thread::sleep_for(chrono::seconds(2));
      continue;

    }

    NumberConfirmed = true;

  }


  system("clear");
  properties = FindNumberProperties(number);


  if (properties.NumberIsPrime) { // The Number Is Prime

    cout << "The Number " << number << " Is Prime" << endl;
    this_thread::sleep_for(chrono::seconds(3));

  }

  else if (properties.NumberIsONE) { // Exception

  cout << "Interestingly Enough 1 is Neither Prime nor Composite\n" << endl;
  cout << right << setw(20) << " ¯" << "\\" << " _(ツ)_ /¯ " << '\n' << endl;
  this_thread::sleep_for(chrono::seconds(3));

}

  else { // Number Is Not Prime + Show Factors

    cout << "The Number " << number << " Is NOT Prime\n" << endl
         << "It Is Divisible By: ";
    
    for (int a = 0; a < properties.factors.size(); a++) {

      // Checks if this is the last loop, if so prints . instead of ,
      cout << properties.factors[a] << ((a == properties.factors.size() - 1) ? "." : ", "); 

    }

    cout << '\n' << '\n' << endl;

  }

  return 0;  
}
