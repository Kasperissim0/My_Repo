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

  int AmountOfArrayBlocks;
  int AmountOfArrays;
  int SizeOfEachArray;

  bool ConfirmedBlockAmount = false;
  bool ConfirmedArrayAmount = false;
  bool ConfiremedArraySize = false;

  system("clear");

  while (!ConfirmedBlockAmount) { // Get Amount of Blocks

    cout << "Insert the Amount of Blocks :" << endl;
    cin >> AmountOfArrayBlocks;
    system("clear"); 

    if (cin.fail() || AmountOfArrayBlocks <= 0) { // Validate First Input

      system("clear"); 
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      this_thread::sleep_for(chrono::seconds(1));
      system("clear"); 
      continue;

    }

    ConfirmedBlockAmount = true; // break the while loop

  }

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

  int array[AmountOfArrayBlocks][AmountOfArrays][SizeOfEachArray];
  BiggestNumber = AmountOfArrayBlocks * AmountOfArrays * SizeOfEachArray;

  for (int a = 0; a < AmountOfArrayBlocks; a++) { // Print Out Array Contents

    cout << " \nThe Content of Block Number " << a + 1 << " Is: \n\n";

    for (int b = 0; b < AmountOfArrays; b++) {

      cout << " - The Content of Array Number " << b + 1 << " Is: ";

      for (int c = 0; c < SizeOfEachArray; c++) {

        array[a][b][c] = TempNumber++;
        cout << array[a][b][c] << ((c != SizeOfEachArray - 1) ? ", " : ".");

      }

      cout << endl; // New line after each array

    }

  }

  FirstNumber = array[0][0][0];
  LastNumber = array[AmountOfArrayBlocks - 1][AmountOfArrays - 1][SizeOfEachArray - 1];

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
  
  while (1) { // Exit The Programm

    int UCQuit;

    cout << "\nPress 1 If You Want To Quit" << endl;
    cin >> UCQuit;

    if (UCQuit != 1 || cin.fail()) {

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      continue;

    }

    system("clear"); 
    return 0;

  }
    

}
