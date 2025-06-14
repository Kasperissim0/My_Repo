#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <cstdlib> // For clearing the terminal
#include <vector> // For Hand
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions
#include <random> // For generating random numbers

using namespace std;

int main () { // The Actual Game

  Player ThePlayer;
  Player TheDealer;
  int ThePot = 0;
  bool EndTheGame = false;

  while (!EndTheGame) {
    
    system("clear");
    int UCStart = StartGame(ThePlayer);

    if (UCStart == 1) {

      if (PlayRoundResult(ThePlayer, TheDealer, ThePot) == true) EndTheGame = true;

    }

    else if (UCStart == 2) { // Player Quits
      
      EndTheGame = true; // Break Loop

    }

    else {

      cout << "ERROR IN int main";
      return 0; 

    }

    // Reset
    ThePot = 0;
    ThePlayer.StartNewRound();
    TheDealer.StartNewRound();

  }

  ThePlayer.LeaveGame(); // display stats 
  return 0;

}

/*

1. 🚧 Player Class
  1.1. ❌ StartNewRound ( clear hand + new cards )
  1.2. ❌ LeaveGame ( display stats )

2. 🚧 StartGame Function ( int return )
3. ❌ PlayRoundResult Function ( bool return )

*/