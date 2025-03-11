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

bool GetRandomNumber(const int& BottomOfRange = 1, const int& TopOfRange = 2) {

  random_device RandomSeed;
  mt19937 GenerateSUPERRandomNumber(RandomSeed());
  uniform_int_distribution<int> NumberInACertainRange(BottomOfRange, TopOfRange);

  return NumberInACertainRange(GenerateSUPERRandomNumber);

}

bool ValidateInput(const int& UserInput, const int& MinimumInput = 1, const int& MaximumInput = 2) {

  if (UserInput < MinimumInput || UserInput > MaximumInput || UserInput == 0 || cin.fail()) {

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();

    return false;

  }

  else {

    return true;

  }

}


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

  bool PlayMultiplayerMode() { // User Choice to play multiplayer or vs random moves

    bool ValidUserInput = false;
    int UserChoice;

    while (!ValidUserInput) {
    
      system("clear");

      cout << setw(40) << "\nWhat Mode Do You Want To Play ?\n" << endl;

      cout << "If You Want To Play Against A Person";
      cout << setw(20) << "Press 1" << endl;
      cout << "If You Want To Play Against A Bot";
      cout << setw(20) << "Press 2" << endl;

      cin >> UserChoice;
      
      ValidUserInput = ValidateInput(UserChoice, 1, 2);

    }

    if (UserChoice == 1) {

      return true;

    }

    else {

      return false;

    }

  }

  int GetRandomLegalMove() {

    // TODO take the 2d array as input, and generate a random, but legal move. RETURN IT AS 12 == [1][2], 2 == [0][2], ...



  }

};


int main () {

  PlayBoard BoardInstance;

  bool MultiplayerMode = BoardInstance.PlayMultiplayerMode();
  bool ValidRowInput = false;
  bool ValidColumnInput = false;
  
  char TempCurrentSign;

  int MoveTracker = GetRandomNumber();
  int MoveCounterTRUE = 0;
  int UCRow;
  int UCColumn;

  if (MultiplayerMode) { // Play In MultiPlayer Mode

    while (!BoardInstance.VictoryAchieved) {

    if (MoveTracker % 2 == 0) { // Create A Random Starting Sign

      TempCurrentSign = 'X';
  
    }
  
    else { // Create A Random Starting Sign
  
      TempCurrentSign = 'O';
      
    }

    ValidRowInput = false; // make sure to reset the value

    while (!ValidRowInput) { // get valid input

      system("clear");
      BoardInstance.DisplayBoard();

      cout << "Choose A Row You Want To Your Mark On:\n" << endl
          << " For Row 1               Press 1\n"
          << " For Row 2               Press 2\n"
          << " For Row 3               Press 3\n" << endl;

      cin >> UCRow;

      ValidRowInput = ValidateInput(UCRow, 1, 3);

    }

    ValidColumnInput = false; // make sure to reset the value

    while (!ValidColumnInput) { // get valid input

      system("clear");
      BoardInstance.DisplayBoard();

      cout << "Choose A Column You Want To Your Mark On:\n" << endl
      << " For Column A               Press 1\n"
      << " For Column B               Press 2\n"
      << " For Column C               Press 3\n" << endl;

      cin >> UCColumn;

      ValidColumnInput = ValidateInput(UCColumn, 1, 3);

    }

    BoardInstance.StoredTempCurrentSigns[UCColumn - 1][UCRow - 1] = TempCurrentSign;

    BoardInstance.CheckForWin();

    if (BoardInstance.VictoryAchieved == true) {

      break;

    }

    MoveTracker++;
    MoveCounterTRUE++;

  }

  }
  
  else {

    // TODO Add the play mode vs the bot here

  }

  // Only Reached When Someone Wins
  system("clear");
  BoardInstance.DisplayBoard();
  this_thread::sleep_for(chrono::seconds(1));

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

/*

0. Fix Overriding Placed Signs

1. Seperate The User Move Entry Into A Method
2. 

*/