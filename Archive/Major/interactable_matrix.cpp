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

void ClearInputRead () { // For Speed

  cin.clear();
  cin.ignore(numeric_limits<int>::max(), '\n');
  cin.clear();

}

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

        if (b == ArraySize - 1 && a != ArrayAmount - 1) { // Last Cell in an Array Points to the Next Array

          ForwardPointer[a][b] = &TheMatrix[a + 1][0];

        }

        else if (a == ArrayAmount - 1 && b == ArraySize - 1) { // Last Value doesn't point forward

          ForwardPointer[a][b] = nullptr;

        }

        else { // Point to the next value

          ForwardPointer[a][b] = &TheMatrix[a][b + 1];

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

      cout << SampleMatrix.TheMatrix[UCArray][i] << " ";

    }

    cout << "\nChoose A Number:   ";

    for (int i = 1; i <= SampleMatrix.ArraySize; i++) { 

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

      cout << SampleMatrix.TheMatrix[UCArray][i] << " ";

    }

    cout << "\nChoose A Number:   ";

    for (int i = 1; i <= SampleMatrix.ArraySize; i++) { 

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

  

};

int GenerateRandomNumber() { // To fill the arrays

  int RandomNumber;

  random_device number;
  mt19937 GenerateNumber (number());
  uniform_int_distribution<int> DistributeNumbers(1, 99);

  RandomNumber = DistributeNumbers(GenerateNumber);

  return RandomNumber;

}

int main () {

 system("clear");

  int ArrayAmount;
  int ArraySize;

  cout << "Insert Amount Of Arrays: " << endl;
  cin >> ArrayAmount;

  cout << "\nInsert Size Of Arrays: " << endl;
  cin >> ArraySize;

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
    cout << "6. Exit\n\n";
    cout << "\nChoose an option: ";

    cin >> UCAction;

    if (UCAction < 0 || UCAction > 7|| cin.fail()) { // Catch Invalid Inputs

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

      default:
      break;

    }

    if (UCAction == 6) break;

    continue;

  }

  /*
  
    0.[x] Array Multiplication

    1.[x] Adding Elements
    2.[x] Removing Elements
    3.[x] Acessing Elements
    4.[x] Modifing Elements
    
    */

  return 0;  
}
