#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions

using namespace std;

int main () {

  const int SmallestNumber = 1;
  int BiggestNumber;
  int TempNumber = SmallestNumber;
  int FirstNumber;
  int LastNumber;

  int AmountOfArrays;
  int SizeOfEachArray;

  bool ConfirmedArrayAmount = false;
  bool ConfiremedArraySize = false;

  system("clear");

  while (!ConfirmedArrayAmount) { // Get Amount of Arrays

    cout << "Insert the Amount of Arrays :" << endl;
    cin >> AmountOfArrays;
    system("clear"); 

    if (cin.fail() || AmountOfArrays <= 0) { // Validate First Input

      system("clear"); 
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      this_thread::sleep_for(chrono::seconds(1));
      system("clear"); 
      continue;

    }

    ConfirmedArrayAmount = true; // break the while loop

  }

  while (!ConfiremedArraySize) { // Get Size of Arrays

    cout << "Insert the Size of Arrays :" << endl;
    cin >> SizeOfEachArray;
    system("clear");

    if (cin.fail() || SizeOfEachArray <= 0) { // Validate Second Input

      system("clear"); 
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      this_thread::sleep_for(chrono::seconds(1));
      system("clear"); 
      continue;

    }

    ConfiremedArraySize = true; // break the while loop

  }

  int array[AmountOfArrays][SizeOfEachArray];
  BiggestNumber = AmountOfArrays * SizeOfEachArray;

  for (int a = 0; a < AmountOfArrays; a++) { // Print out Array Contents

    cout << " The Content of Array Number " << a + 1 << " Is: ";

    for (int b = 0; b < SizeOfEachArray; b++) {

      array[a][b] = TempNumber++;
      cout << array[a][b] << ((b != SizeOfEachArray - 1) ? ", " : ".");

    }

    cout << endl; // New line after each array

  }

  FirstNumber = array[0][0];
  LastNumber = array[AmountOfArrays - 1][SizeOfEachArray - 1];

  cout << "\nResult: " << '\n' << endl;

  if (FirstNumber == SmallestNumber && LastNumber == BiggestNumber) { // Everything went well

    cout << setw(30) << right << "Success\n" << endl;
    cout << "The First Number = The Smallest Number: " << FirstNumber << " = " << SmallestNumber << "." << '\n' << endl
         << "The Last Number = The Biggest Number:  "<< LastNumber << " = " << BiggestNumber << "." << '\n' << endl;

  }

  else { // Something went wrong

    cout << setw(30) << right << "Failure\n" << endl;
    cout << "The First Number ≠ The Smallest Number: " << FirstNumber << " ≠ " << SmallestNumber << "." << '\n' << endl
         << "The Last Number ≠ The Biggest Number:  "<< LastNumber << " ≠ " << BiggestNumber << "." << '\n' << endl;

  }
  
  this_thread::sleep_for(chrono::seconds(10));
  system("clear"); 
  return 0;
    

}
