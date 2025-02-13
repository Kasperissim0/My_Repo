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

int GenerateRandomNumber ();

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

        
        cout << right << setw(2) << SampleMatrix.TheMatrix[a][b] << ((b == SampleMatrix.ArraySize - 1) ? "." : ", ");

      }

      cout << '\n' << endl;

    }


  }

  void AddArraysTogether (Matrix& SampleMatrix) { // Add All Arrayst Column by Column, then Row by Row

    int *TheLastSum = new int(0);
    int TempPrice = 0;
    int *TotalOfIndex = new int[SampleMatrix.ArrayAmount];

    PrintOutMatrix(SampleMatrix);

    cout << "\nThe Sum Of Each Array Is:   ";

    for (int a = 0; a < SampleMatrix.ArraySize; a++) {

      int LoopCounter = 0;

      for (int b = 0; b < SampleMatrix.ArrayAmount; b++) {

        ++LoopCounter;
        TempPrice += SampleMatrix.TheMatrix[b][a];

        if (LoopCounter == SampleMatrix.ArrayAmount) { 

          TotalOfIndex[a] = TempPrice;
          TempPrice = 0;
          LoopCounter = 0;

          cout << right << setw(2) << TotalOfIndex[a] << ((a == SampleMatrix.ArraySize - 1) ? " = " : " + ");

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


};

int GenerateRandomNumber() { // To fill the arrays

  int RandomNumber;

  random_device number;
  mt19937 GenerateNumber (number());
  uniform_int_distribution<int> DistributeNumbers(0, 99);

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

  MatrixInstance.AddArraysTogether(MatrixInstance); // Uste the Add Arrays Method

  /*
  
    0.[ ] Array Multiplication

    1.[ ] Adding Elements
    2.[ ] Removing Elements
    3.[ ] Add Matrix Traversal
    4.[ ] Acessing Elements
    5.[ ] Modifing Elements
    
    */

  return 0;  
}
