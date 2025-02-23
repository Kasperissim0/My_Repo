#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions
#include <cmath> // For mathematical calculations
#include <random>

using namespace std;

int GenerateRandomNumber (); // Define For Use in the Matrix Stucture

void ClearInputRead (); // Define For Use in the Matrix Stucture

void ShowTravelOptions (const int& CurrentIndex, const int& AmountOfNumbers); // Define For Use in the Matrix Stucture

struct Matrix { // Define the Martix Structure

  int ArrayAmount;
  int ArraySize;

  int **TheMatrix;
  int ***ForwardPointer;

  Matrix(const int& ArrayAmount, const int& ArraySize) : // Constructor
  
  ArrayAmount(ArrayAmount), ArraySize(ArraySize) // Initialize Variables 
  
  {

    TheMatrix = new int*[ArrayAmount];
    ForwardPointer = new int**[ArrayAmount];

    for (int i = 0; i < ArrayAmount; i++) {

      TheMatrix[i] = new int[ArraySize];
      ForwardPointer[i] = new int*[ArraySize];

    }

    for (int a = 0; a < ArrayAmount; a++) {

      for (int b = 0; b < ArraySize; b++) {

        TheMatrix[a][b] = GenerateRandomNumber(); // Set a random number to the current cell

        if (a == ArrayAmount - 1 && b == ArraySize - 1) { // Last Value doesn't point forward

          ForwardPointer[a][b] = nullptr;

        }

        else if (b == ArraySize - 1) { // Last Value of each array points to the beginning of the next one

          ForwardPointer[a][b] = &TheMatrix[a + 1][0];
          //cout << ForwardPointer[a][b] << endl; //! DEBUGGING

        }

        else { // Point to the next value

          ForwardPointer[a][b] = &TheMatrix[a][b + 1];
          //cout << ForwardPointer[a][b] << endl; //! DEBUGGING

        }

      }

    }

  }

  ~Matrix () { // Destructor ( Wipe All Data )

    for (int a = 0; a < ArrayAmount; a++) {

      delete[] TheMatrix[a];
      delete[] ForwardPointer[a];

    }

    delete[] TheMatrix;
    delete[] ForwardPointer;

  }

  void PrintOutMatrix (Matrix& SampleMatrix) { // Print All Arrays Of The Matrix

    system("clear");

    cout << endl;

    for (int a = 0; a < SampleMatrix.ArrayAmount; a ++) {

      cout << "The Content Of Array ";
      cout << right << setw(3) << a + 1;
      cout << " Is:   ";

      for (int b = 0; b < SampleMatrix.ArraySize; b++) {

        if (SampleMatrix.TheMatrix[a][b] == 19283) {

          cout << right << setw(2) << " " << ((b == SampleMatrix.ArraySize - 1) ? "." : ", ");

        } 

        else {

          cout << right << setw(2) << SampleMatrix.TheMatrix[a][b] << ((b == SampleMatrix.ArraySize - 1) ? "." : ", ");
        
        }

      }

      cout << '\n' << endl;

    }


  }

  void AddArraysTogether (Matrix& SampleMatrix) { // Add All Arrays Column by Column, then Row by Row

    int *TheLastSum = new int(0);
    int TempAmount = 0;
    int *TotalOfIndex = new int[SampleMatrix.ArrayAmount];

    PrintOutMatrix(SampleMatrix);

    cout << "\nThe Sum Of Each Array Is:   ";

    for (int a = 0; a < SampleMatrix.ArraySize; a++) {

      int LoopCounter = 0;

      for (int b = 0; b < SampleMatrix.ArrayAmount; b++) {

        ++LoopCounter;

        if (SampleMatrix.TheMatrix[b][a] == 19283) {

          TempAmount += 0;

        }

        else if (LoopCounter == SampleMatrix.ArrayAmount) { // When the last number in an array is reached

          TotalOfIndex[a] = TempAmount;
          TempAmount = 0;
          LoopCounter = 0;

          cout << right << setw(2) << TotalOfIndex[a] << ((a == SampleMatrix.ArraySize - 1) ? " = " : " + ");

        }

        else { // the default action

          TempAmount += SampleMatrix.TheMatrix[b][a];

        }

      }

    }

    for (int i = 0; i < SampleMatrix.ArraySize; i++) { // Calculate Final Sum

     *TheLastSum += TotalOfIndex[i];
      
    }

    cout << *TheLastSum << endl << '\n'; // Print the Final Sum (dereference the last pointer in the array)

    delete TheLastSum;
    delete[] TotalOfIndex;

  }

  void MultiplyArrays (Matrix& SampleMatrix) { // Multiply All Arrays Column by Column, then Row by Row

    int64_t *FinalNumber = new int64_t(1);
    int TempAmount = 1;
    int *TotalOfIndex = new int[SampleMatrix.ArrayAmount];

    PrintOutMatrix(SampleMatrix);

    cout << "\nThe Multiples Of Each Array Are: ";

    for (int a = 0; a < SampleMatrix.ArraySize; a++) {

      int LoopCounter = 0;

      for (int b = 0; b < SampleMatrix.ArrayAmount; b++) {

        ++LoopCounter;

        if (SampleMatrix.TheMatrix[b][a] == 19283) {

          TempAmount *= 1;

        }

        else if (LoopCounter == SampleMatrix.ArrayAmount) { // When the last number in an array is reached

          TotalOfIndex[a] = TempAmount;
          TempAmount = 1;
          LoopCounter = 0;

          cout << right << setw(2) << TotalOfIndex[a] << ((a == SampleMatrix.ArraySize - 1) ? " = " : " * ");

        }

        else { // the default action

          TempAmount *= SampleMatrix.TheMatrix[b][a];

        }

      }

    }

    for (int i = 0; i < SampleMatrix.ArraySize; i++) { // Calculate Final Multiple

     *FinalNumber *= TotalOfIndex[i];
      
    }

    cout << *FinalNumber << endl << '\n'; // Print the Final Multiple (dereference the last pointer in the array)

    delete FinalNumber;
    delete[] TotalOfIndex;

  }

  void RemoveElement (Matrix& SampleMatrix) { // Return a Modified Matrix ( remove a number ) 

    int UCArray;
    int UCIndex;

    PrintOutMatrix(SampleMatrix);
    
    cout << "Choose an Array:\n" << endl;

    for (int i = 0; i < SampleMatrix.ArrayAmount; i++) { // Choose an Array

      int number = i + 1;

      cout << "For Array Number " << number;
      
      cout << right << setw(8) << "     Press " << number << endl;

    }

    cout << endl;

    cin >> UCArray;
    UCArray -= 1; // Adjust for 0 indexing

    if (UCArray < 0 || UCArray > SampleMatrix.ArrayAmount || cin.fail()) { // Errors

      ClearInputRead();

    }

    cout << "Your Chosen Array: ";

    for (int i = 0; i < SampleMatrix.ArraySize; i++) { // Print the Chosen Array

      if (SampleMatrix.TheMatrix[UCArray][i] == 19283) { // Print A Blank Instead Of  Normal Numbers, when needed

        cout << " ";

      }

      else { // Print Normal Numbers

        cout << SampleMatrix.TheMatrix[UCArray][i] << " ";

      }

    }

    cout << "\nChoose A Number:   ";

    for (int i = 1; i <= SampleMatrix.ArraySize; i++) {  // Print An Index Below The Numbers

      cout << i << "  ";

    }

    cout << '\n' << endl;

    cin >> UCIndex;
    UCIndex -= 1; // Adjust for 0 indexing

    if (UCIndex < 0 || UCIndex > SampleMatrix.ArraySize || cin.fail()) { // Errors

      ClearInputRead();

    }

    SampleMatrix.TheMatrix[UCArray][UCIndex] = 19283; // Special Number to Replace With A Blank

    cout << "Value at Array " << (UCArray + 1) << ", Index " << (UCIndex + 1) << " has been erased." << endl;

  }
  
  void AddElement (Matrix& SampleMatrix) { // Return a Modified Matrix ( add a number )

    int UCArray;
    int UCIndex;
    int UCNumber;

    PrintOutMatrix(SampleMatrix);
    
    cout << "Choose an Array:\n" << endl;

    for (int i = 0; i < SampleMatrix.ArrayAmount; i++) { // Choose an Array

      int number = i + 1;

      cout << "For Array Number " << number;
      
      cout << right << setw(8) << "     Press " << number << endl;

    }

    cout << endl;

    cin >> UCArray;
    UCArray -= 1; // Adjust for 0 indexing

    if (UCArray < 0 || UCArray > SampleMatrix.ArrayAmount || cin.fail()) { // Errors

      ClearInputRead();

    }

    cout << "Your Chosen Array: ";

    for (int i = 0; i < SampleMatrix.ArraySize; i++) { // Print the Chosen Array

      if (SampleMatrix.TheMatrix[UCArray][i] == 19283) { // Print A Blank Instead Of  Normal Numbers, when needed

        cout << " ";

      }

      else { // Print Normal Numbers

        cout << SampleMatrix.TheMatrix[UCArray][i] << " ";

      }

    }

    cout << "\nChoose A Number:   ";

    for (int i = 1; i <= SampleMatrix.ArraySize; i++) {  // Print An Index Below The Numbers

      cout << i << "  ";

    }

    cout << '\n' << endl;

    cin >> UCIndex;
    UCIndex -= 1; // Adjust for 0 indexing

    if (UCIndex < 0 || UCIndex > SampleMatrix.ArraySize || cin.fail()) { // Errors

      ClearInputRead();

    }

    cout << "\n Insert The New Number: " << endl;
    cin >> UCNumber;
    
    SampleMatrix.TheMatrix[UCArray][UCIndex] = UCNumber; // Special Number to Replace With A Blank

    system("clear");

    cout << "\nValue at Array " << (UCArray + 1) << ", Index " << (UCIndex + 1) << " is now " << UCNumber << endl;


  }

  void LinearTraverse (Matrix& SampleMartix) { // Traverse The Matrix

    bool WantToLeave = false;
    string CurrentPath;

    int CurrentIndex = 1;
    int *AdjustedIndex = new int(0);
    int AmountOfNumbers = SampleMartix.ArrayAmount * SampleMartix.ArraySize;
    int **CurrentPointer = new int*[AmountOfNumbers]();

    int UserChoice;
    int FirstNumber = SampleMartix.TheMatrix[0][0];

    CurrentPointer[*AdjustedIndex] = SampleMartix.ForwardPointer[*AdjustedIndex][*AdjustedIndex]; // The First + Current Pointer ( to the 2nd number)
    CurrentPath = to_string(FirstNumber);
    
    while(!WantToLeave) {

      ShowTravelOptions(CurrentIndex, AmountOfNumbers); // Print the menu

      cout << "\nCurrent path: \n\n" << CurrentPath << endl << endl; // Print the full path

      cin >> UserChoice; // Get User Choice

      if ((UserChoice <= 0 || UserChoice > 3 || cin.fail()) || (UserChoice == 1 && CurrentIndex == 1) || (UserChoice == 2 && CurrentIndex == AmountOfNumbers)) { // Handle Invalid Inputs

        system("clear");

        this_thread::sleep_for(chrono::seconds(1));
        cout << "Invalid Input" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        ClearInputRead();
        continue;

      }

      else if (UserChoice == 1 && CurrentIndex > 1) { // Go BACKWARDS

        system("clear");

        size_t LastArrowLocation = CurrentPath.rfind(" -> ");

        if (LastArrowLocation != string::npos) { // find the last arrow and erase
        
          CurrentPath.erase(LastArrowLocation, numeric_limits<int>::max()); // delete everything after the last arrow

        }

        CurrentIndex--;
        --(*AdjustedIndex);
        continue;

      }

      else if (UserChoice == 2) { // Go FORWARDS
        
        system("clear");

        int CurrentArrayPosition = *AdjustedIndex / SampleMartix.ArraySize; // Use the General Index divided by Array Size and rounded down to find correct Array.
        int CurrentIndexPosition = *AdjustedIndex % SampleMartix.ArraySize; // Use the General Index modulated by Array Size to find the correct Index.

        CurrentPointer[*AdjustedIndex] = SampleMartix.ForwardPointer[CurrentArrayPosition][CurrentIndexPosition]; // Set Next Pointer to the next Value
    
        //cout << "CurrentPointer[" << *AdjustedIndex << "]: " << CurrentPointer[*AdjustedIndex] << endl; //! DEBUGGING
    
        if (CurrentPointer[*AdjustedIndex] != nullptr) { // check for validity //! DEBUGGING

          if (*CurrentPointer[*AdjustedIndex] == 19283) { // Special Number For deleted numbers

            CurrentPath += " ->  "; // Add a blank instead of a number

          }
          
          else {

            CurrentPath += " -> " + to_string(*CurrentPointer[*AdjustedIndex]); // Append the new value to the string

          }

          CurrentIndex++;
          ++(*AdjustedIndex);
          
        } 
        
        else { //! DEBUGGING

          cout << "There Has Been An Error" << endl;
          this_thread::sleep_for(chrono::seconds(5));
          WantToLeave = true;
          break;

        }

        continue;

      }

      else if (UserChoice == 3) { // Free Memory + Leave

        system("clear");

        delete[] CurrentPointer;
        delete AdjustedIndex;

        WantToLeave = true;
        break;

        }

    }

  }

};

int GenerateRandomNumber() { // To fill the arrays

  int RandomNumber;

  random_device number;
  mt19937 GenerateNumber (number());
  uniform_int_distribution<int> DistributeNumbers(1, 99);

  RandomNumber = DistributeNumbers(GenerateNumber);

  return RandomNumber;

}

void ClearInputRead () { // For Speedy and Clean Code

  cin.clear();
  cin.ignore(numeric_limits<int>::max(), '\n');
  cin.clear();

}

void ShowTravelOptions (const int& CurrentIndex, const int& AmountOfNumbers) { // For Showing The Correct Menu

  system("clear");

  if (CurrentIndex == 1) { // The First Number Menu 
    
    cout << "Press 2 To Move Forwards\n" 
        << "Press 3 To Quit\n" << endl;

  }

  else if (CurrentIndex == AmountOfNumbers) { // The Last Number Menu
    
    cout << "Press 1 To Move Backwards\n"
        << "Press 3 To Quit\n" << endl;

  }

  else { // The Middle Numbers Menu

  cout << "Press 1 To Move Backwards\n" 
      << "Press 2 To Move Forwards\n" 
      << "Press 3 To Quit\n" << endl;

}


}


int main () {

 system("clear");

  int ArrayAmount;
  int ArraySize;

  while (true) { // Get Valid Array Amount

    system("clear");

    cout << "Insert Amount Of Arrays: " << endl;
    cin >> ArrayAmount;

    if (ArrayAmount <= 0 || cin.fail()) { // Handle Errors + Invalid Inputs

      ClearInputRead();
      continue;

    }

    else { // When A Valid Input Is Entered Exit The Loop

      break;

    }

  }
  
  while (true) { // Get Valid Array Size

    system("clear");

    cout << "Insert Amount Of Arrays: " << endl << ArrayAmount; // Maintain The Same Input View

    cout << "\nInsert Size Of Arrays: " << endl;
    cin >> ArraySize;

    if (ArraySize <= 0 || cin.fail()) { // Handle Errors + Invalid Inputs

      ClearInputRead();
      continue;

    }

    else { // When A Valid Input Is Entered Exit The Loop

      break;

    }

  }    
  
  Matrix MatrixInstance(ArrayAmount, ArraySize); // Create a "Matrix" Object

  while (true) {

    int UCAction = 0;

    system("clear");

    cout << "Matrix Operations Menu:\n\n\n";
    cout << "1. Print Matrix\n\n";
    cout << "2. Add Arrays Together\n\n";
    cout << "3. Multiply Arrays\n\n";
    cout << "4. Remove an Element\n\n";
    cout << "5. Add an Element\n\n";
    cout << "6. Traverse The Matrix\n\n";
    cout << "7. Exit\n\n";
    cout << "\nChoose an option: ";

    cin >> UCAction;

    if (UCAction < 0 || UCAction > 8|| cin.fail()) { // Catch Invalid Inputs

      ClearInputRead();
      continue;

    }

    switch (UCAction) { // Martix Interaction Possibilities

      case 1:
      MatrixInstance.PrintOutMatrix(MatrixInstance);
      this_thread::sleep_for(chrono::seconds(4));
      break;

      case 2:
      MatrixInstance.AddArraysTogether(MatrixInstance);
      this_thread::sleep_for(chrono::seconds(6));
      break;

      case 3:
      MatrixInstance.MultiplyArrays(MatrixInstance);
      this_thread::sleep_for(chrono::seconds(6));
      break;

      case 4:
      MatrixInstance.RemoveElement(MatrixInstance);
      this_thread::sleep_for(chrono::seconds(2));
      break;

      case 5:
      MatrixInstance.AddElement(MatrixInstance);
      this_thread::sleep_for(chrono::seconds(2));
      break;

      case 6:
      MatrixInstance.LinearTraverse(MatrixInstance);
      break;

      default:
      break;

    }

    if (UCAction == 7) break;

    continue;

  }

  return 0;  
}
