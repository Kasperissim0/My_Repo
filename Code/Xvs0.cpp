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

int GetRandomNumber(char specify, const int& BottomOfRange = 1, const int& TopOfRange = 2) { // Overload For A Different Number

  random_device RandomSeed;
  mt19937 GenerateSUPERRandomNumber(RandomSeed());
  uniform_int_distribution<int> NumberInACertainRange(BottomOfRange, TopOfRange);

  return NumberInACertainRange(GenerateSUPERRandomNumber);

}

int GetRandomNumber(const int& BottomOfRange = 1, const int& TopOfRange = 2) { // Overload For A Different Number

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

    int SpaceCounter = 0;

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

    else { // Else Check For Other Wins / Game End

      for (int a = 0; a < 3; a++) {

        TempStorageHorizontal = StoredTempCurrentSigns[a][0] + StoredTempCurrentSigns[a][1] + StoredTempCurrentSigns[a][2];
        TempStorageVertical = StoredTempCurrentSigns[0][a] + StoredTempCurrentSigns[1][a] + StoredTempCurrentSigns[2][a];

        if (TempStorageHorizontal == "XXX" || TempStorageVertical == "XXX") { // Check For A Win

          VictoryAchieved = true;
          VictoriousSide = 'X'; 
          return;

        }

        else if ( TempStorageHorizontal == "OOO" || TempStorageVertical == "OOO") { // Check For A Win

          VictoryAchieved = true;
          VictoriousSide = 'O'; 
          return;

        }

      }

      for (int a = 0; a < 3; a++) {

        for (int b = 0; b < 3; b++) {

          if (StoredTempCurrentSigns[a][b] == " ") {

            ++SpaceCounter;

          }

        }

      }

      if (SpaceCounter == 0) {

        VictoryAchieved = true;
        return;

      }
    
    }

  }

  int ChooseGameMode() { // User Choice to play multiplayer or vs random moves

    bool ValidUserInput = false;
    int UserChoice;

    while (!ValidUserInput) {
    
      system("clear");

      cout << setw(40) << "What Mode Do You Want To Play ?\n" << endl;

      cout << "If You Want To Play Against A Person";
      cout << setw(20) << "Press 1" << endl;
      cout << "If You Want To Play Against A Bot";
      cout << setw(23) << "Press 2" << endl;
      cout << "\nIf You Want To Watch A Bot vs Bot Match";
      cout << setw(17) << "Press 3" << endl;

      cin >> UserChoice;
      
      ValidUserInput = ValidateInput(UserChoice, 1, 3);

    }

    return UserChoice;

  }

  void MakeAMove(const char& TempCurrentSign, int MoveTracker, const int& Press1ForMultiplayer = 987) {

    bool ValidRowInput = false;
    bool ValidColumnInput = false;

    int UCRow;
    int UCColumn;
    int RandomRow;
    int RandomColumn;

    if (Press1ForMultiplayer == 1) {
      
      while (true) { // Major Loop To Avoid Overriding Placed Signs

        ValidRowInput = false; // make sure to reset the value

        while (!ValidRowInput) { // get valid input

          system("clear");
          DisplayBoard();

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
          DisplayBoard();

          cout << "Choose A Column You Want To Your Mark On:\n" << endl
          << " For Column A               Press 1\n"
          << " For Column B               Press 2\n"
          << " For Column C               Press 3\n" << endl;

          cin >> UCColumn;

          ValidColumnInput = ValidateInput(UCColumn, 1, 3);

        }

        if (StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] == "X") { // Invalid Move

          system("clear");

          cout << "You Cannot Place A Sign On A Taken Square\n" << endl;
          cout << "This Is NOT A Valid Move, Try Again" << endl;
          this_thread::sleep_for(chrono::seconds(2));

          continue; // Repeat The Major Loop ( get correct input )

        }

        else if (StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] == "O") { // Invalid Move

          system("clear");

          cout << "You Cannot Place A Sign On A Taken Square\n" << endl;
          cout << "This Is NOT A Valid Move, Try Again" << endl;
          this_thread::sleep_for(chrono::seconds(2));

          continue; // Repeat The Major Loop ( get correct input )

        }

        else { // Valid Move

          StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] = TempCurrentSign;

          break; // Exit Major Loop

        }

      }

    }

    else {
      
      if (MoveTracker % 2 == 0) {

        //? Major Loop To Avoid Overriding Placed Signs      
        while (true) { //* The Player's Move ( He Goes First )

        ValidRowInput = false; // make sure to reset the value

        while (!ValidRowInput) { // get valid input

          system("clear");
          DisplayBoard();

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
          DisplayBoard();

          cout << "Choose A Column You Want To Your Mark On:\n" << endl
          << " For Column A               Press 1\n"
          << " For Column B               Press 2\n"
          << " For Column C               Press 3\n" << endl;

          cin >> UCColumn;

          ValidColumnInput = ValidateInput(UCColumn, 1, 3);

        }

        if (StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] == "X") { // Invalid Move

          system("clear");

          cout << "You Cannot Place A Sign On A Taken Square\n" << endl;
          cout << "This Is NOT A Valid Move, Try Again" << endl;
          this_thread::sleep_for(chrono::seconds(2));

          continue; // Repeat The Major Loop ( get correct input )

        }

        else if (StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] == "O") { // Invalid Move

          system("clear");

          cout << "You Cannot Place A Sign On A Taken Square\n" << endl;
          cout << "This Is NOT A Valid Move, Try Again" << endl;
          this_thread::sleep_for(chrono::seconds(2));

          continue; // Repeat The Major Loop ( get correct input )

        }

        else { // Valid Move

          StoredTempCurrentSigns[UCRow - 1][UCColumn - 1] = TempCurrentSign;

          break; // Exit Major Loop

        }

      }

      }

      else {
        
        //? Major Loop To Avoid Overriding Placed Signs
        while (true) { //* The Bot's Move

        RandomRow = GetRandomNumber('a', 0, 2);
        RandomColumn = GetRandomNumber(0, 2);

        system("clear");
        DisplayBoard();

        if (StoredTempCurrentSigns[RandomRow][RandomColumn] == "X") { // Invalid Move

          continue; // Repeat The Major Loop ( get correct input )

        }

        else if (StoredTempCurrentSigns[RandomRow][RandomColumn] == "O") { // Invalid Move

          continue; // Repeat The Major Loop ( get correct input )

        }

        else { // Valid Move

          StoredTempCurrentSigns[RandomRow][RandomColumn] = TempCurrentSign;

          this_thread::sleep_for(chrono::milliseconds(700)); // add a small delay to the bot's move
          system("clear");
          DisplayBoard();

          break; // Exit Major Loop

        }

      }
      
    }

    }

  }

  void WatchBotMatch(const char& TempCurrentSign) {

    while (true) { // Major Loop To Avoid Overriding Placed Signs

      int RandomRow = GetRandomNumber('a', 0, 2);
      int RandomColumn = GetRandomNumber(0, 2);

      system("clear");
      DisplayBoard();

      if (StoredTempCurrentSigns[RandomRow][RandomColumn] == "X") { // Invalid Move

        continue; // Repeat The Major Loop ( get correct input )

      }

      else if (StoredTempCurrentSigns[RandomRow][RandomColumn] == "O") { // Invalid Move

        continue; // Repeat The Major Loop ( get correct input )

      }

      else { // Valid Move

        StoredTempCurrentSigns[RandomRow][RandomColumn] = TempCurrentSign;

        system("clear");
        DisplayBoard();
        this_thread::sleep_for(chrono::seconds(2));

        break; // Exit Major Loop

      }

    }

  }

};


int main () {

  PlayBoard BoardInstance;

  int MultiplayerMode = BoardInstance.ChooseGameMode();
  
  char TempCurrentSign;

  int MoveTracker = GetRandomNumber();
  int MoveCounterTRUE = 0;

  while (!BoardInstance.VictoryAchieved) {

    if (MoveTracker % 2 == 0) { // Create A Random Starting Sign

      TempCurrentSign = 'X';

    }

    else { // Create A Random Starting Sign

      TempCurrentSign = 'O';
      
    }

    if (MultiplayerMode == 1) { // If this User Chose Multiplayer

      BoardInstance.MakeAMove(TempCurrentSign, MoveTracker, 1);

    }

    else if (MultiplayerMode == 2) { // Play Against a Bot Playind random moves

      BoardInstance.MakeAMove(TempCurrentSign, MoveTracker);

    }

    else if (MultiplayerMode == 3) { // Watch A Bot vs Bot Match

      BoardInstance.WatchBotMatch(TempCurrentSign);

    }

    BoardInstance.CheckForWin();

    if (BoardInstance.VictoryAchieved == true) {

      break;

    }

    MoveTracker++;
    MoveCounterTRUE++;

  }

  // Only Reached When the game is over
  system("clear");
  BoardInstance.DisplayBoard();
  this_thread::sleep_for(chrono::seconds(1));

  if (BoardInstance.VictoriousSide == 'X') { // If the X has won

    system("clear");

    cout << "Congratulations, The X Side Has Won" << endl;
    cout << "🎉🎉🎉" << endl;

  }

  else if (BoardInstance.VictoriousSide == 'O') { // If the O has won

    system("clear");

    cout << "Congratulations, The O Side Has Won" << endl;
    cout << "🎉🎉🎉" << endl;

  }

  else { // If there is a stalemate

    system("clear");

    cout << "You Have Reached A Stalemate" << endl;

    cout << "😭😭😭" << endl;

  }

  cout << endl; 

  return 0;

}

/*

0. ✅ Fix Overriding Placed Signs

1. ✅ Seperate The User Move Entry Into A Method
2. ✅ Introduce A Stalemate, when there are no more moves
3. ✅ Fix the Person vs Bot Game Mode
4. ⏳ Add A Win Score + Replayability

*/