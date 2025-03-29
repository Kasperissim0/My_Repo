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

  random_device RandomSeed;
  mt19937 GenerateNumber(RandomSeed());
  uniform_int_distribution<int> DistributionRange(MinNumber, MaxNumber);

  return DistributionRange(GenerateNumber);


}

struct Card { // A Useful Way Of Storing Data

  string CardValue;
  string CardSuit;

};

struct Deck { // Manipulate The Deck

  Card TheDeck[AMOUNT_OF_CARDS * AMOUNT_OF_SUITS];

  Deck() { // Constructor, Create Deck + Insert Cards

    int TempIndex = 0;

    vector<string> PossibleSuits = {

      "Hearts", "Clubs", "Diamonds", "Spades"

    };
    vector<string> PossibleValues = {

      "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
      "Jack", "Queen", "King", "Ace"

    };

    for (string suit: PossibleSuits) {  // Change suit

      for (string value: PossibleValues) { // Insert All cards in one suit

        TheDeck[TempIndex].CardSuit = suit;
        TheDeck[TempIndex].CardValue = value;

        TempIndex++;

      }

    }


  }

  Card GetCard() { // Get Random Card

    return TheDeck[GetRandomNumber((AMOUNT_OF_CARDS * AMOUNT_OF_SUITS) - 1)];

  }


};

struct Player { // Not Sure If This Struct Is Needed

  int MyMoney = 500; // Expand On This LATER

  Deck PlayingDeck;
  vector<Card> MyHand; // TODO Expand On This

  void TakeACard () {

    MyHand.push_back(PlayingDeck.GetCard());

  }

};

int main () {
  system("clear");
  
  Player John;
  John.TakeACard();

  cout << John.MyHand[0].CardValue << " of " << John.MyHand[0].CardSuit << endl;

  return 0;
}

/*

  -1. ✅ Read The Rules For Blackjack

  1. 🚧 Create A User Interface For Playing
  2. ❌ Add Multiplayer ( Playing Against Yourself )
  3. ❌ Add Playing Against The Dealer ( Random Moves )
    - 1 Game, Many Terms
    - You Take Or Don't
    - Want To Get To 21
    - Lose If Opp. Get's More, Or If You Get Above 21
  4. ❌ Add Replayability ( A Score Of Wins And Total Games )
  5. ❌ Add Bets
  6. ❌ Improve User Interface
  6. ❌ Improve Dealer's Strategy

  99. Create A Way To Randomly Shuffle The Deck ( just for the challenge )
*/