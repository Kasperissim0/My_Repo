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

const int AMOUNT_OF_SUITS = 4; // The Amount Of Suits  in the Deck
const int AMOUNT_OF_CARDS = 13; // The Amount Of Cards in the Deck

using namespace std;

int GetRandomNumber(const int& MaxNumber, const int& MinNumber = 0) {

  if (MaxNumber == MinNumber) {

    return 0;

  }

  // TODO Recreate A Random Number Generator From Scratch

}

struct Card { // A Useful Way Of Storing Data

  string CardValue;
  string CardSuit;

};

struct Deck { // Manipulate The Deck

  Card TheDeck[AMOUNT_OF_CARDS * AMOUNT_OF_SUITS];

  Deck() { // Constructor, Create Deck + Shuffle Cards

    ShuffleDeck();

  }

  Card GetCard() { // Get Random Card

    return TheDeck[(AMOUNT_OF_CARDS * AMOUNT_OF_SUITS) - 1];

  }

  void ShuffleDeck() {

    int TempIndex = 0;

    vector<string> PossibleSuits = {

      "Hearts", "Clubs", "Diamonds", "Spades"

    };
    vector<string> PossibleValues = {

      "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
      "Jack", "Queen", "King", "Ace"

    };

    // TODO Create A Way To Randomly Shuffle The Deck, Using All Cards And Suits

  }


};

struct Player { // Not Sure If This Struct Is Needed

  int MyMoney = 500; // Expand On This LATER

  vector<Card> MyHand; // TODO Expand On This
  Deck PlayingDeck;

}

int main () {

  system("clear");


  // here
  

  return 0;

}

/*

  0. ⏳ Create A Way To Randomly Shuffle The Deck
  1. ❌ Create A User Interface For Playing
  2. ❌ Add Multiplayer ( Playing Against Yourself )
  3. ❌ Add Playing Against The Dealer ( Random Moves )
    - 1 Game
    - You Take Or Don't
    - Want To Get To 21
    - Lose If Opp. Get's More, Or If You Get Above 21
  4. ❌ Add Replayability ( A Score Of Wins And Total Games )
  5. ❌ Add Bets
  6. ❌ Improve User Interface
  6. ❌ Improve Dealer's Strategy

*/