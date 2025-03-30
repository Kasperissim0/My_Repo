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

int GetRandomNumber(const int& MaxNumber, const int& MinNumber = 0); // For Use In The Classes

struct Card { // A Useful Way Of Storing Data

  string CardValue;
  string CardSuit;
  int CardStrength; // TODO Add this to the Deck constructor

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

class Player {

  public:
    vector<Card> MyHand;
    int AvaliableChips = 100;

    Player() {

      GetStartingHand(); // Automatically Get A Hand;

    }

    void TakeACard() { // Adds A Random Card Object Into The MyHand Vector

      MyHand.push_back(PlayingDeck.GetCard());

    }

    void DisplayHand(const string& PlayerType = "Normal", const bool& RevealHand = false) { // Display All Data About All Card Objects In The MyHand Vector

      int TempIndex = 0;

      if (PlayerType == "Normal" || RevealHand == true) {

        for (Card card: MyHand) {

          cout << MyHand[TempIndex].CardValue << " of " << MyHand[TempIndex].CardSuit << endl;

          TempIndex++;

        }

      }

      else if (PlayerType == "Dealer") {

        for (int i = 0; i < MyHand.size(); i++) {

          if (i == (MyHand.size() - 1)) {

            cout << "HIDDEN CARD" << endl;

          }

          else {

            cout << MyHand[i].CardValue << " of " << MyHand[i].CardSuit << endl;

          }

        }

      }

    }

    void ManipulateChips (const string& OperationCode, const int& ChangeByAmount) { // Press 1 For Addition, 2 For Substraction

      if (OperationCode == "+") { // Add Chips to Total Amount

        AvaliableChips+= ChangeByAmount;

      }

      else if (OperationCode == "-") { // Substracte Chips from Total Amount

        AvaliableChips-= ChangeByAmount;

      }

      else { // Should Never Be Reached 

        cout << "\nERROR OCCURED WHILE TRYING TO MANIPULATE CHIPS" << endl;

      }

    }

    int StartGame() {

      int UCChoice;
    
      while (true) {
        
        system("clear");
    
        cout << right << setw(130) << "You Currently Have " << AvaliableChips << " Chips At Your Disposal" << endl;
        
        cout << right << setw(80) << "Welcome to the Casino!" << endl; // Centered title
        cout << left << setw(15) << "1. Start A Game ( Buy In Costs 20 Chips )" << endl;
        cout << left << setw(23) << "2. Exit\n\n" << endl;
        cout << "Enter your choice >>> ";
    
        cin >> UCChoice;
    
        if (cin.fail() || UCChoice > 2 || UCChoice <= 0) {
  
          system("clear");
          cout << "Invalid Input" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          this_thread::sleep_for(chrono::seconds(1));
          continue;
    
        }
    
        return UCChoice;
      
      }
    
    }

    void LeaveGame() {

      system("clear");

      if (AvaliableChips <= 0) {

        cout << "You Have Lost, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else if (AvaliableChips > 0 && AvaliableChips < 20) {

        cout << "You Cannot Affort The Buy-In, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else {

        cout << "You Have " << AvaliableChips << " Chips Left 😮\n" << endl;

      }

      
      cout << "You Have Played " << TotalGames << " Games\n" << endl;
      cout << "Of Which You Won " << TotalWins << endl;

      cout << endl << "\nWell Played, And Farewell 👋 \n\n" << endl;
      this_thread::sleep_for(chrono::seconds(2));

    }

    int MakeAMove() {

      int UCChoice;
    
      while (true) {
        
        system("clear");
    
        cout << left << setw(15) << "1. Take Another Card" << endl;
        cout << left << setw(15) << "2. Keep Current Hand\n\n" << endl;
        cout << "Enter your choice >>> ";
    
        cin >> UCChoice;
    
        if (cin.fail() || UCChoice > 2 || UCChoice <= 0) {
  
          system("clear");
          cout << "Invalid Input" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          this_thread::sleep_for(chrono::seconds(1));
          continue;
    
        }
    
        return UCChoice;
      
      }

    }


  private:
    Deck PlayingDeck;
    int TotalWins = 0;
    int TotalGames = 0;

    void GetStartingHand() { // Adds 2 Random Card Objects Into The MyHand Vector ( used for the constructor )

      TakeACard();
      TakeACard();

    }


};

void DisplayRound (Player& Player1, Player& Player2, const int& ThePot, const bool& RevealAll = false) {

  cout << right << setw(100) << "The Current Pot Is: " << ThePot << " Chips\n" << endl;

  cout << right << setw(50) << "YOUR OPPONENT'S HAND:" << endl;

  if (RevealAll) { // For Final Reveal

    Player1.DisplayHand("Dealer", true);

  }

  else {

    Player1.DisplayHand("Dealer");

  }

  cout << endl << endl;

  cout << right << setw(39) << "YOUR HAND:" << endl;
  Player2.DisplayHand();
  cout << endl << endl;

}

int GetRandomNumber(const int& MaxNumber, const int& MinNumber) {

  if (MaxNumber == MinNumber) {

    return 0;

  }

  random_device RandomSeed;
  mt19937 GenerateNumber(RandomSeed());
  uniform_int_distribution<int> DistributionRange(MinNumber, MaxNumber);

  return DistributionRange(GenerateNumber);

}

int main () {
  system("clear");
  
  Player Bob;
  Player TheDealer;

  int UCStart;
  int UCMove;
  int ThePot;

  bool EndTheRound = false;

  while(true) { // Infinite Game Loop

    UCStart = Bob.StartGame();

    switch(UCStart) {

      case 1: // The Player Places A Bet
        if (Bob.AvaliableChips < 20) { // If You Cannot Afford To Play

          Bob.LeaveGame();
          return 0;

        }

        Bob.ManipulateChips("-", 20); // Pay The Buy-In
        ThePot+= 40; // 20 from you and the dealer
        
        while (!EndTheRound) {

          system("clear");

          DisplayRound(TheDealer, Bob, ThePot);

          UCMove = Bob.MakeAMove();

          if (UCMove == 1) { // Another Card

            Bob.TakeACard();
            continue;

          }

          else { // End The Round

            EndTheRound = true;
            break;

          }

        }

        DisplayRound(TheDealer, Bob, ThePot, true);


        break;

      case 2: // The Player Leaves The Table
        Bob.LeaveGame();
        return 0;

      default:
        continue; // By Default Restart The Game Loop

    }

    continue;

  }

  return 0;
}

/*

  1. ✅ Read The Rules For Blackjack
    1.1. 🚧 Figure Out How To Calculate Hand Strength ( Sum ) In General
    1.2. ❌ Figure Out How To Calculate Hand Strength ( Sum ) For The Ace

  1. 🚧 Create A User Interface For Playing
  2. ❌ Add Playing Against The Dealer ( Random Moves )
    - 1 Game, Many Turns
    - Start With 2 Cards
    - You Take Or Don't
    - Want To Get To 21
    - Lose If Opp. Get's More, Or If You Get Above 21
  3. ❌ Add Multiplayer ( Playing Against Yourself )
  4. ❌ Add Replayability ( A Score Of Wins And Total Games )
  5. ❌ Add Bets
  6. ❌ Improve Dealer's Strategy ( Make The Dealer Play OPTIMALLY )
  7. ❌ Improve User Interface

  99. ⛔︎ Create A Way To Randomly Shuffle The Deck ( just for the challenge )
*/