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

int GetRandomNumber();

struct PlayBoard {

  string StoredTempCurrentSigns[3][3]; // Here X and O will be stored, and checked
  string TheCompleteBoard; // The Complete Board with the Actual TempCurrentSigns
  char VictoriousSide;
  bool VictoryAchieved = false;

  PlayBoard() { // Standard Constructor

    for (int a = 0; a < 3; a++) { // assign  Default Values to the Saved sign

      for (int b = 0; b < 3; b++) {

        StoredTempCurrentSigns[a][b] = " ";
 
      }

    }

  }

  void UpdateBoard() { // Reconstruct The Board, Updating the Saved TempCurrentSigns

    string NavigationNumbers = "       A       B       C \n";
    string StandardLine = "   _________________________\n";
    string BoardTop = "1. |   " + StoredTempCurrentSigns[0][0] + "   |   " + StoredTempCurrentSigns[0][1] + "   |   " + StoredTempCurrentSigns[0][2] + "   |\n";
    string BoardMiddle = "2. |   " + StoredTempCurrentSigns[1][0] + "   |   " + StoredTempCurrentSigns[1][1] + "   |   " + StoredTempCurrentSigns[1][2] + "   |\n";
    string BoardBottom = "3. |   " + StoredTempCurrentSigns[2][0] + "   |   " + StoredTempCurrentSigns[2][1] + "   |   " + StoredTempCurrentSigns[2][2] + "   |\n";
    string LineWithPipes = "   |_______|_______|_______|\n";
    string StandardPipes = "   |       |       |       |\n";

    TheCompleteBoard = NavigationNumbers + StandardLine + StandardPipes
                             + BoardTop + LineWithPipes + StandardPipes + BoardMiddle
                             + LineWithPipes + StandardPipes + BoardBottom + LineWithPipes;

  } 

  void DisplayBoard() { // Print Out Board

    UpdateBoard(); // Gets the latest version of the board to avoid problems

    cout << TheCompleteBoard << endl;

  }

  void CheckDiagonalWin() {

    string DiagonalCheckLR = StoredTempCurrentSigns[0][0] + StoredTempCurrentSigns[1][1] + StoredTempCurrentSigns[2][2];
    string DiagonalCheckRL = StoredTempCurrentSigns[0][2] + StoredTempCurrentSigns[1][1] + StoredTempCurrentSigns[2][0];

    if (DiagonalCheckLR == "XXX" || DiagonalCheckRL == "XXX") { // If there is a win, return true

      VictoryAchieved = true;
      VictoriousSide = 'X';

    }

    else if (DiagonalCheckLR == "OOO" || DiagonalCheckRL == "OOO") { // If there is a win, return true

      VictoryAchieved = true;
      VictoriousSide = 'O';

    }

    else {

      VictoryAchieved = false;

    }

  }

  void CheckForWin() {

    PlayBoard Instance;

    bool WonDiagonally = false;
    bool WonHorizontaly = false;
    bool WonVertically = false;

    string TempStorageHorizontal;
    string TempStorageVertical;

    CheckDiagonalWin();

    WonDiagonally = VictoryAchieved;

    if (WonDiagonally == true) { // If there is a win, return true and end function

      return;

    }

    else { // Else Check For Other Wins

      for (int a = 0; a < 3; a++) {

        TempStorageHorizontal = StoredTempCurrentSigns[a][0] + StoredTempCurrentSigns[a][1] + StoredTempCurrentSigns[a][2];
        TempStorageVertical = StoredTempCurrentSigns[0][a] + StoredTempCurrentSigns[1][a] + StoredTempCurrentSigns[2][a];

        if (TempStorageHorizontal == "XXX" || TempStorageVertical == "XXX") {

          VictoryAchieved = true;
          VictoriousSide = 'X'; 

        }

        else if ( TempStorageHorizontal == "OOO" || TempStorageVertical == "OOO") {

          VictoryAchieved = true;
          VictoriousSide = 'O'; 

        }

      }
    
    }

  }

};

int GetRandomNumber() {

  random_device RandomSeed;
  mt19937 GenerateSUPERRandomNumber(RandomSeed());
  uniform_int_distribution<int> NumberInACertainRange(1, 2);

  return NumberInACertainRange(GenerateSUPERRandomNumber);

}

int main () {

  PlayBoard BoardInstance;

  int MoveCounterFALSE = GetRandomNumber();
  int MoveCounterTRUE = 0;
  int UCRow;
  int UCColumn;

  char TempCurrentSign;

  while (!BoardInstance.VictoryAchieved) {

    if (MoveCounterFALSE % 2 == 0) {

      TempCurrentSign = 'X';
  
    }
  
    else {
  
      TempCurrentSign = 'O';
      
    }

    system("clear");

    BoardInstance.DisplayBoard();

    cout << "Choose A Row You Want To Your Mark On:\n" << endl
        << " For Row 1               Press 1\n"
        << " For Row 2               Press 2\n"
        << " For Row 3               Press 3\n" << endl;

    cin >> UCColumn;

    // TODO ADD Input Verification here

    cout << "Choose A Column You Want To Your Mark On:\n" << endl
    << " For Column A               Press 1\n"
    << " For Column B               Press 2\n"
    << " For Column C               Press 3\n" << endl;

    cin >> UCRow;

    // TODO ADD Input Verification here

    BoardInstance.StoredTempCurrentSigns[UCColumn - 1][UCRow - 1] = TempCurrentSign;

    BoardInstance.CheckForWin();

    if (BoardInstance.VictoryAchieved == true) {

      break;

    }

    MoveCounterFALSE++;
    MoveCounterTRUE++;

  }

  if (BoardInstance.VictoriousSide == 'X') {

    system("clear");

    cout << "Congratulations, The X Side Has Won" << endl;

  }

  else if (BoardInstance.VictoriousSide == 'O') {

    system("clear");

    cout << "Congratulations, The O Side Has Won" << endl;

  }

  cout << "🎉🎉🎉" << endl;

  return 0;

}