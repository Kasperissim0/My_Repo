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

struct Game {

  bool GameIsOver;

  int HorizontalAim;
  int VerticalIndex;

  char SavedSymbol;

  string TheBoard;

  string PlacedCharachterIndex[3][3];

  Game() { // Constructor

    for (int a = 0; a < 3; a++) { // Set The Values

      for (int b = 0; b < 3; b++) {

        PlacedCharachterIndex[a][b] = "___"; // insert value

        PlacedCharachterIndex[a][b] = HorizontalIndex[a][b]; // copy to the Horizontal

        HorizontalSlice[a][b] = VerticalSlice[b][a]; // flip to fit in the Vertical

      }

    }

    DiagonalSlice[0][0] = PlacedCharachterIndex[0][0];
    DiagonalSlice[0][1] = PlacedCharachterIndex[1][1];
    DiagonalSlice[0][2] = PlacedCharachterIndex[2][2];
    DiagonalSlice[1][0] = PlacedCharachterIndex[0][2];
    DiagonalSlice[1][0] = PlacedCharachterIndex[1][1];
    DiagonalSlice[1][2] = PlacedCharachterIndex[2][0];

    TheBoard = " A  B  C\n  _____________\n1 |" 
              + PlacedCharachterIndex[0][0]
              + "|" + PlacedCharachterIndex[0][1] 
              + "|" + PlacedCharachterIndex[0][2]
              + "|\n2 |" + PlacedCharachterIndex[1][0]
              + "|" + PlacedCharachterIndex[1][1]
              + "|" + PlacedCharachterIndex[1][2]
              + "|\n3 |" + PlacedCharachterIndex[2][0]
              + "|" + PlacedCharachterIndex[2][1]
              + "|" + PlacedCharachterIndex[2][2]
              + "|\n\n";

  }

  Game GetUserInput (const char& ReturnForm) { // If You Want to Return an X, type X, else will return O

    Game UserInput;
    bool GotXAxis = false;
    bool GotYAxis = false;
  
    while (!GotXAxis) { // Get Horizonal Value
  
      system("clear");

      cout << UserInput.TheBoard;
  
      cout << "Where Do You Want to Place Your " << ((ReturnForm == 'X') ? 'X' : 'O') << " On The Horizontal Axis? \n\n 1 or 2 or 3" << endl;
      cin >> UserInput.HorizontalAim;
  
      if (cin.fail() || UserInput.HorizontalAim < 0 || UserInput.HorizontalAim > 3) { // Catch Errors
  
        system("clear");
  
        cout << "Invalid Input";
        this_thread::sleep_for(chrono::seconds(2));
  
        continue;
  
      }
  
      UserInput.HorizontalIndex = UserInput.HorizontalAim - 1; // Convert User Input Into Usable Index 
  
      GotXAxis = true;
  
    }
  
    while (!GotYAxis) { // Get Horizonal Value
  
      system("clear");

      cout << UserInput.TheBoard;
  
      cout << "Where Do You Want to Place Your " << ((ReturnForm == 'X') ? 'X' : 'O') << " On The Vertical Axis? \n\n A or B or C" << endl;
      cin >> UserInput.VerticalAim;
  
      if (cin.fail() || (UserInput.VerticalAim != 'A' && UserInput.VerticalAim != 'B' && UserInput.VerticalAim != 'C')) { // Catch Errors
  
        system("clear");
  
        cout << "Invalid Input";
        this_thread::sleep_for(chrono::seconds(2));
  
        continue;
  
      }
  
      switch (UserInput.HorizontalAim) { // Convert User Input Into Usable Index 
  
        case 'A':
          UserInput.VerticalAim = 0;
          break;
        
          case 'B':
            UserInput.VerticalAim = 1;
            break;
    
          case 'C':
            UserInput.VerticalAim = 2;
            break;
    
          default:
            continue;
    
      }
  
      GotYAxis = true;
  
    }
  
    UserInput.SavedSymbol = ReturnForm;

    return UserInput; // Got Horizontal And Vertical Index for the "PlacedCharachterIndex"
  
  }
  
  bool CheckIfTheGameIsOver () {

    for (int i = 0; i < 2; i++) {

      string CheckTheSentence[2];
      CheckTheSentence[0] = "";
      CheckTheSentence[1] = "";
      
      CheckTheSentence[0] += PlacedCharachterIndex[i][i];

      CheckTheSentence[1] += PlacedCharachterIndex[0][2];
      CheckTheSentence[1] += PlacedCharachterIndex[1][1];
      CheckTheSentence[1] += PlacedCharachterIndex[2][0];

      if (CheckTheSentence[0] == "XXX" || CheckTheSentence[1] == "XXX") { // Check For A Win On The Diagonal Axis

        cout << "X won";
        this_thread::sleep_for(chrono::seconds(2));
        
        return GameIsOver = true;

      }

      else if (CheckTheSentence[0] == "OOO" || CheckTheSentence[1] == "OOO") { // Check For A Win On The Diagonal Axis

        cout << "O won";
        this_thread::sleep_for(chrono::seconds(2));
        
        return GameIsOver = true;

      }
    
    }

    

    else if () { // Check For A Win On The Horizontal Axis

      string CheckTheSentence[3];

      for (int a = 0; a < 3; a++) {

        for (int b = 0; b < 3; b++) {

          CheckTheSentence[a] = "";
          CheckTheSentence[a] += PlacedCharachterIndex[a][b];

        }

      }

    }

    else if () { // Check For A Win On The Vertical Axis

      

    }

    else {



    }

    return GameIsOver = true;
    return GameIsOver = false;
  
  }
  
  Game UpdateTheBoard (Game& PreviousBoard) {
  
    CheckIfTheGameIsOver();

    PreviousBoard.PlacedCharachterIndex[PreviousBoard.HorizontalIndex][PreviousBoard.VerticalIndex] = PreviousBoard.SavedSymbol;
  
  }

};


int main () {

  system("clear");

  int KeepTrack = 1;
  Game PlayingField;
  PlayingField.GameIsOver = false;

  while (!PlayingField.GameIsOver) {

    if (KeepTrack % 2 == 0) { // O goes 2nd

      PlayingField = PlayingField.UpdateTheBoard(PlayingField.GetUserInput('O'));
  
    }
  
    else { // X goes 1st
  
      PlayingField.UpdateTheBoard(PlayingField.GetUserInput('X'));
  
    }
  
    KeepTrack++;
    
  }

  system("clear"); 

  cout << " The Game Is Over";
  this_thread::sleep_for(chrono::seconds(2));
 

  return 0; // ! REPLAYABILITY AND A SCORE ( X vs O )
}
