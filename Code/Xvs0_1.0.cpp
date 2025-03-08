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

using namespace std;

struct PlayBoard {

  string StoredSigns[3][3]; // Here X and O will be stored, and checked
  string TheCompleteBoard; // The Complete Board with the Actual Signs

  PlayBoard() { // Standard Constructor

    for (int a = 0; a < 3; a++) { // Assign Default Values to the Saved Signs

      for (int b = 0; b < 3; b++) {

        StoredSigns[a][b] = " ";
 
      }

    }

  }

  void UpdateBoard() { // Reconstruct The Board, Updating the Saved Signs

    string NavigationNumbers = "       A       B       C \n";
    string StandardLine = "   _________________________\n";
    string BoardTop = "1. |   " + StoredSigns[0][0] + "   |   " + StoredSigns[0][1] + "   |   " + StoredSigns[0][2] + "   |\n";
    string BoardMiddle = "2. |   " + StoredSigns[1][0] + "   |   " + StoredSigns[1][1] + "   |   " + StoredSigns[1][2] + "   |\n";
    string BoardBottom = "3. |   " + StoredSigns[2][0] + "   |   " + StoredSigns[2][1] + "   |   " + StoredSigns[2][2] + "   |\n";
    string LineWithPipes = "   |_______|_______|_______|\n";
    string StandardPipes = "   |       |       |       |\n";

    TheCompleteBoard = NavigationNumbers + StandardLine + StandardPipes
                             + BoardTop + LineWithPipes + StandardPipes + BoardMiddle
                             + LineWithPipes + StandardPipes + BoardBottom + LineWithPipes;

  } 

  void DisplayBoard() { // Print Out Board

    StoredSigns[0][0] = "X"; //! Checking If the Validation Works
    StoredSigns[0][1] = "X"; //! Checking If the Validation Works
    StoredSigns[0][2] = "O"; //! Checking If the Validation Works
    StoredSigns[2][0] = "O"; //! Checking If the Validation Works
    StoredSigns[1][1] = "O"; //! Checking If the Validation Works
    StoredSigns[1][0] = "X"; //! Checking If the Validation Works

    UpdateBoard(); // Gets the latest version of the board to avoid problems

    cout << TheCompleteBoard << endl;

  }

  bool CheckDiagonalWin() {

    string DiagonalCheckLR = StoredSigns[0][0] + StoredSigns[1][1] + StoredSigns[2][2];
    string DiagonalCheckRL = StoredSigns[0][2] + StoredSigns[1][1] + StoredSigns[2][0];

    if (DiagonalCheckLR == "XXX" || DiagonalCheckLR == "OOO" || DiagonalCheckRL == "XXX" || DiagonalCheckRL == "OOO") { // If there is a win, return true

      return true;

    }

    else {

      return false;

    }

  }

  bool CheckForWin() {

    bool WonDiagonally = false;
    bool WonHorizontaly = false;
    bool WonVertically = false;

    string TempStorageHorizontal;
    string TempStorageVertical;

    WonDiagonally = CheckDiagonalWin();

    if (WonDiagonally == true) { // If there is a win, return true and end function

      return true;

    }

    else { // Else Check For Other Wins

      for (int a = 0; a < 3; a++) {

        TempStorageHorizontal = StoredSigns[a][0] + StoredSigns[a][1] + StoredSigns[a][2];
        TempStorageVertical = StoredSigns[0][a] + StoredSigns[1][a] + StoredSigns[2][a];

        if (TempStorageHorizontal == "XXX" || TempStorageHorizontal == "OOO" || TempStorageVertical == "XXX" || TempStorageVertical == "OOO") {

          return true; // If there if ther is a win on any axes return true ( win )

        }

      }

      return false; // If there are no wins on no axes return false ( no win )
    
    }

  }

};

int main () {

  system("clear");

  PlayBoard BoardInstance;
  bool Win = false;

  BoardInstance.DisplayBoard();

  Win = BoardInstance.CheckForWin();

  cout << ((Win == true) ? "Yipee" : "Next Move") << endl;
  

  return 0;

}