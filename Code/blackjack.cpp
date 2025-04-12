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

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;

static const int AMOUNT_OF_SUITS = 4; // The Amount Of Suits In The Deck
static const int AMOUNT_OF_CARDS = 13; // The Amount Of Cards In The Deck
static const int BLACKJACK = 21; // The Number Required To Win In Blackjack
static const int BUY_IN = 20; // The Current Buy In Rate

class Player; // Declaration For Use, Definition Below ⬇️

void DisplayRound (Player& Player1, Player& Player2, const int& ThePot, const bool& RevealAll = false); // Declaration For Use, Definition Below ⬇️
int GetRandomNumber(const int& MaxNumber, const int& MinNumber = 0); // Declaration For Use, Definition Below ⬇️
void DeclareFinishedRound(const int& YourScore, const int& OppsScore, bool GameWon); // Declaration For Use, Definition Below ⬇️
bool PlayRound(Player& ThePlayer, Player& TheDealer, int& ThePot); // Declaration For Use, Definition Below ⬇️
void CalculateHandStrengths(Player& ThePlayer, Player& TheDealer, int& PlayerHandStrength, int& DealerHandStrength); // Declaration For Use, Definition Below ⬇️
void ClearStream(const string message = "IGNORE");

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Card { // A Useful Way Of Storing Data

  string CardValue;
  string CardSuit;
  int CardStrength;

};

struct Deck { // Manipulate The Deck, Store Cards

  Card TheDeck[AMOUNT_OF_CARDS * AMOUNT_OF_SUITS];

  Deck() { // Constructor, Create Deck + Insert Cards

    int TempIndex = 0;

    string PossibleSuits[] = {

      "Hearts", "Clubs", "Diamonds", "Spades"

    };
    string PossibleValues[] = {

      "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
      "Jack", "Queen", "King", "Ace"

    };
    int PossibleStrengths[] = {

      2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11

    };

    for (string suit: PossibleSuits) { // The Major Loop, Runs 4 Times
      
      for (int i = 0; i < AMOUNT_OF_CARDS; i++) { // Minor Loop, Runs 13 Times

        TheDeck[TempIndex].CardSuit = suit;
        TheDeck[TempIndex].CardValue = PossibleValues[i];
        TheDeck[TempIndex].CardStrength = PossibleStrengths[i];

        TempIndex++;

      }

    }


  }

  Card GetCard() { // Get Random Card

    return TheDeck[GetRandomNumber((AMOUNT_OF_CARDS * AMOUNT_OF_SUITS) - 1)];

  }


};

class Player { // The Main Structure, Store Deck, Chips, + Useful Methods

  public:
    vector<Card> MyHand;
    int AvaliableChips = 100;

    Player() { // Constructor ( Get A Deck + Get A Randomly Dealt Hand )

      GetStartingHand(); // Automatically Get A Hand;

    }

    void TakeACard() { // Adds A Random Card Object Into The MyHand Vector

      MyHand.push_back(PlayingDeck.GetCard());

    }

    int DisplayHand(const string& PlayerType = "Normal", const bool& RevealHand = false, const bool& ShowText = true) { // Display All Data About All Card Objects In The MyHand Vector

      int HandStrength = 0;
      int TheHiddenCard = MyHand.size() - 1;
      bool AceInHand = false;

      bool AdjustedHand = false; // Flags To Decide Return Value
      bool OriginalHand = false; // Flags To Decide Return Value

      if (PlayerType == "Normal" || RevealHand == true) {

        for (Card card: MyHand) {

          if (ShowText) cout << card.CardValue << " of " << card.CardSuit << endl;

          if(card.CardValue == "Ace") { // For The Ace

            AceInHand = true;

          }

          HandStrength+= card.CardStrength;

        }

        if (ShowText) cout << endl; // Make Space For The Hand Strength Rating

        if (HandStrength > BLACKJACK && AceInHand) { // If the Ace cannot be 11, automatically revert to 1

          if (ShowText) cout << "You Hand Strength Is " << (HandStrength - 10) << "/" << BLACKJACK; // Here Representing The Ace As 1 ( 11 - 10 )
          AdjustedHand = true;

        }

        else if (HandStrength < BLACKJACK && AceInHand) {

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/" << BLACKJACK; // If There Is No Overflow, Display Largest Hand
          OriginalHand = true;

        }

        else if (AceInHand) {

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/" << BLACKJACK << " OR " << (HandStrength - 10) << "/" << BLACKJACK;
          OriginalHand = true;

        }

        else { // No Ace, Or Ace And No Ovelflow

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/" << BLACKJACK;
          OriginalHand = true;

        }

      }

      else if (PlayerType == "Dealer") {

        for (int i = 0; i < MyHand.size(); i++) {

          if (i == TheHiddenCard) { // Do Not Show Second Card After Dealing Hand

            if (ShowText) cout << "HIDDEN CARD" << endl;
            HandStrength-= MyHand[i].CardStrength; // Remove The Last Card's Strengts From The Total

          }

          else {

            if (ShowText)cout << MyHand[i].CardValue << " of " << MyHand[i].CardSuit << endl;

          }

          if(MyHand[i].CardValue == "Ace") { // For The Ace

            AceInHand = true;

          }

          HandStrength+= MyHand[i].CardStrength;

        }

        if (ShowText) cout << endl; // Make Space For The Hand Strength Rating

        if (HandStrength > BLACKJACK && AceInHand) { // If the Ace cannot be 11, automatically revert to 1

          if (ShowText) cout << "Hand Strength Is At Least" << (HandStrength - 10) << "/" << BLACKJACK; // Here Representing The Ace As 1 ( 11 - 10 )
          AdjustedHand = true;

        }

        else { // No Ace

          if (ShowText) cout << "Hand Strength Is At Least " << HandStrength << "/" << BLACKJACK;
          OriginalHand = true;

        }

      }

      else { // Should Never Be Reached 
      
        cout << "\nERROR OCCURED WHILE TRYING TO MANIPULATE CHIPS" << endl;
        return 0;
      
      }
      
      if (AdjustedHand) {

        return (HandStrength - 10);

      }

      else if (OriginalHand) {

        return HandStrength;

      }

      return 0;
    }

    void ManipulateChips (const string& OperationCode, const int& ChangeByAmount) { // Press 1 For Addition, 2 For Substraction

      if (OperationCode == "+") { // Add Chips to Total Amount

        AvaliableChips+= ChangeByAmount;

      }

      else if (OperationCode == "-") { // Substracte Chips from Total Amount

        AvaliableChips-= ChangeByAmount;

      }

      else { // Should Never Be Reached 

        cout << "\nERROR OCCURED WHILE TRYING TO DISPLAY HAND" << endl;

      }

    }

    int StartGame() { // Some Text Walkthrough With Options For Entering A Round Of Play

      int UCChoice;
      TotalGames++;
    
      while (true) {
        
        system("clear");
    
        cout << right << setw(130) << "You Currently Have " << AvaliableChips << " Chips At Your Disposal" << endl;
        
        cout << right << setw(80) << "Welcome to the Casino!" << endl; // Centered title
        cout << left << setw(15) << "1. Start A Game ( Buy In Costs " << BUY_IN << " Chips )" << endl;
        cout << left << setw(23) << "2. Exit\n\n" << endl;
    
        cin >> UCChoice;
    
        if (cin.fail() || UCChoice > 2 || UCChoice <= 0) {
  
          ClearStream("Invalid Input");
          continue;
    
        }
    
        return UCChoice;
      
      }
    
    }

    void LeaveGame() { // Shows The Stats ( Games Played, Games Won + Chips Left)

      system("clear");

      if (AvaliableChips <= 0) { // Negative or 0 Chips

        cout << "You Have Lost, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else if (AvaliableChips > 0 && AvaliableChips < BUY_IN) { // Can't Afford The Buy-In

        cout << "You Cannot Affort The Buy-In, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else { // Left The Game With Chips

        cout << "You Had " << AvaliableChips << " Chips Left 😮\n" << endl;

      }

      
      cout << "You Have Played " << TotalGames << " Games." << endl;
      cout << "Of Which You Won " << TotalWins << "." << endl;

      cout << endl << "\nWell Played, And Farewell 👋 \n\n" << endl;
      this_thread::sleep_for(chrono::seconds(2));

    }

    int MakeAMove() { // Some Text Walkthrough With Options During The Round Of Play

      int UCChoice;
    
      while (true) {
    
        cout << left << setw(15) << "0. Bet More Chips\n" << endl;
        cout << left << setw(15) << "1. Take Another Card" << endl;
        cout << left << setw(15) << "2. Keep Current Hand" << endl;
    
        cin >> UCChoice;
    
        if (cin.fail() || UCChoice > 2 || UCChoice < 0) {
  
          ClearStream("Invalid Input");
          continue;
    
        }
    
        return UCChoice;
      
      }

    }

    void StartNewRound() { // Remove Your Old Hand, And Get A New One

      MyHand.clear();
      GetStartingHand();

    }

    bool RoundFinished(Player& YourOpponent, int ThePot, int GamePhase = 3) { // Double Check If The Game Is Over, React Accordingly, Returns True, If Round Is Finished

      int YourHandStrength = DisplayHand("Normal", true, false);
      int OpponentsHandStrength = YourOpponent.DisplayHand("Dealer", true, false);
      bool draw = false;
      bool win = false;
      bool loss = false;

      system("clear");

      if (GamePhase >= 1) { // Check For Immediate Win, + Immediate Double Win

        if (YourHandStrength == BLACKJACK && OpponentsHandStrength == BLACKJACK) { // Double Blackjack Dealt

          draw = true;

        }
        
        else if (YourHandStrength == BLACKJACK && OpponentsHandStrength != BLACKJACK) { // Blackjack, Without Opp. Interferance

          win = true;

        }

        

      }

      if (GamePhase >= 2) { // Check For Hand Overflow, For The Player

        if (YourHandStrength > BLACKJACK) {

          loss = true;

        }

      }

      if (GamePhase == 3) {

        if (YourHandStrength == OpponentsHandStrength) { //* If There Is A Draw

          draw = true;

        }

        else if (OpponentsHandStrength > BLACKJACK || YourHandStrength > OpponentsHandStrength) { //* If You Won

          win = true;

        }

        else if (OpponentsHandStrength == BLACKJACK || OpponentsHandStrength > YourHandStrength) { //* If You Lost

          loss = true;

        }

      }

     //* The Final Check, Relying On The Flags Triggered
     if (win) { // The Round Is Finished Via ⬅

      DeclareFinishedRound(YourHandStrength, OpponentsHandStrength, true); // Show Appropriate Round End Text

      // Enjoy The Spoils Of War 😉
      TotalWins++;
      AvaliableChips+= ThePot;

      return true;

    }

    else if (loss) { // The Round Is Finished Via ⬅

      DeclareFinishedRound(YourHandStrength, OpponentsHandStrength, false); // Show Appropriate Round End Text

      return true;

    }

    else if (draw) { // The Round Is Finished Via ⬅

      AvaliableChips+= (ThePot / 2); // Get Half Of The Pot

      cout << setw(35) << "A DRAW Has Occured 😐😐😐\n" << endl
           << " You Get 1/2 The Pot" << endl;

      this_thread::sleep_for(chrono::seconds(4));

      return true;

    }

    else { // The Round Is Not Finished

      return false;

    }

    }

  private:
    Deck PlayingDeck;
    int TotalWins = 0;
    int TotalGames = -1;

    void GetStartingHand() { // Adds 2 Random Card Objects Into The MyHand Vector ( used for the constructor )

      TakeACard();
      TakeACard();

    }


};

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

void DisplayRound (Player& ThePlayer, Player& TheDealer, const int& ThePot, const bool& RevealAll) { // Display Cards Of All Players + The Pot

  cout << right << setw(100) << "Total Chips Left: " << ThePlayer.AvaliableChips << " || " << "The Current Pot Is: " << ThePot << " Chips\n" << endl;

  cout << right << setw(50) << "YOUR OPPONENT'S HAND:" << endl;

  if (RevealAll) { // For Final Reveal

    TheDealer.DisplayHand("Dealer", true);

  }

  else {

    TheDealer.DisplayHand("Dealer");

  }

  cout << endl << endl;

  cout << right << setw(39) << "YOUR HAND:" << endl;
  ThePlayer.DisplayHand();
  cout << endl << endl;

}

int GetRandomNumber(const int& MaxNumber, const int& MinNumber) { // For Getting A Random Card

  if (MaxNumber == MinNumber) {

    return 0;

  }

  random_device RandomSeed;
  mt19937 GenerateNumber(RandomSeed());
  uniform_int_distribution<int> DistributionRange(MinNumber, MaxNumber);

  return DistributionRange(GenerateNumber);

}

void DeclareFinishedRound(const int& YourScore, const int& OppsScore, bool GameWon) {

  system("clear");

    if (GameWon) { // If You Won

      cout << setw(35) << "Congratulations, You WON 🎉🎉🎉\n" << endl;

      if (YourScore == BLACKJACK) { // Your Equals 21

        cout << "In Fact, You Hit The BLACKJACK 🤯🤯🤯" << endl;

      } 

      else if (OppsScore > BLACKJACK) { // <<< ADD THIS: Win because dealer busted

        cout << "The Dealer Overflowed (with " << OppsScore << ")!" << endl;
      
      } 
      
      else if (YourScore > OppsScore) { // Your Hand Is Larger

        cout << "You Hand ( Total Of " << YourScore << " ) Defeated Your Opponent's Hand (Total Of " << OppsScore << " )." << endl;
      
      } 
      
      else { // Should Not Be Reached anymore

        cout << "ERROR IN DeclareFinishedRound (Win condition mismatch)" << endl; // Refined error
     
      }

    }

    else { // If You Lost

      cout << setw(35) << "You LOST 😭😭😭\n" << endl;

      if (YourScore > BLACKJACK) { // Your Hand Exceeded 21

        cout << "The Score Of Your Hand Is Too Large; " << YourScore << " Is Larger Than " << BLACKJACK << endl;

      }
      
      else if (OppsScore == BLACKJACK) { // <<< ADD THIS: Lost to dealer Blackjack

        cout << "The Dealer Got Blackjack!" << endl;

      }
      
      else if (OppsScore > YourScore) { // Your Hand Is Smaller

        cout << "You Hand ( Total Of " << YourScore << " ) Was Beaten By Your Opponent's Hand (Total Of " << OppsScore << " )." << endl;

      }
      
      else { // Should Not Be Reached anymore

        cout << "ERROR IN DeclareFinishedRound (Loss condition mismatch)" << endl; // Refined error

      }

    }

  this_thread::sleep_for(chrono::seconds(4)); // Read The Result

}

bool PlayRound(Player& ThePlayer, Player& TheDealer, int& ThePot) { // Full Round Of Play ( Return True If Game Needs To End, False Otherwise )

  int PlayerHandStrength;
  int DealerHandStrength;

  bool EndTheRound = false;

  CalculateHandStrengths(ThePlayer, TheDealer, PlayerHandStrength, DealerHandStrength);

  // Check If You Can Play
  if (ThePlayer.AvaliableChips < BUY_IN) { // If You Cannot Afford To Play

    ThePlayer.LeaveGame();
    return true; // End The Game

  }

  // Pay The Buy In + Calculate The Pot
  ThePlayer.ManipulateChips("-", BUY_IN); // Buy In - 20 Chips
  ThePot+= (BUY_IN * 2); // 20 from you and the dealer

  while (!EndTheRound) {

    system("clear");
    DisplayRound(ThePlayer, TheDealer, ThePot);
    int UCMove = TheDealer.MakeAMove(); // User Choice Variables Defined Separately

    //* Phase 1 ( 2 Cards )
    if(ThePlayer.RoundFinished(TheDealer, ThePot, 1)) break;

    //* Respond According To User Choice
    if (UCMove == 0) { // Bet More Chips

      int AdditionalBet = 0;

      select_bet:
        system("clear");
        cout << "How Many Chips Do You Want To Bet?" << endl;
        cin >> AdditionalBet;

      if (cin.fail() || AdditionalBet > ThePlayer.AvaliableChips || ThePlayer.AvaliableChips == 0 || AdditionalBet <= 0) { // Error Handling

        ClearStream("You Cannot Bet That Amount Of Chips");
        goto select_bet;

      }

      ThePlayer.AvaliableChips-= AdditionalBet; // Remove The Bet From The Account
      ThePot+= (AdditionalBet * 2); // The Bet Is Always Matched By The Dealer
      continue;
      
    }

    else if (UCMove == 1) { // Another Card ( "Hit" )

      ThePlayer.TakeACard();
      CalculateHandStrengths(ThePlayer, TheDealer, PlayerHandStrength, DealerHandStrength);

      //* Phase 2 ( 2+ Cards )
      if (ThePlayer.RoundFinished(TheDealer, ThePot, 2)) { // If The Round Is Finished, Exit

        break;

      }
      else { // If It Is Not, Repeat The Loop

        continue;

      }

    }

    else { // No More Cards ( "Stay" )

      EndTheRound = true; // escape the round

    }

    // Display After The Round Is Over
    system("clear");
    CalculateHandStrengths(ThePlayer, TheDealer, PlayerHandStrength, DealerHandStrength);
    DisplayRound(ThePlayer, TheDealer, ThePot, true);
    this_thread::sleep_for(chrono::seconds(2));

    //? The Dealer's "Move"
    while(true) { // This Is The Dealer's Behavior In The Rules

      if (TheDealer.DisplayHand("Dealer", true, false) <= 16) {

        TheDealer.TakeACard();

      }

      else {

        system("clear");
        CalculateHandStrengths(ThePlayer, TheDealer, PlayerHandStrength, DealerHandStrength);
        DisplayRound(ThePlayer, TheDealer, ThePot, true);
        this_thread::sleep_for(chrono::seconds(2));
        break;
        
      }

      system("clear");
      CalculateHandStrengths(ThePlayer, TheDealer, PlayerHandStrength, DealerHandStrength);
      DisplayRound(ThePlayer, TheDealer, ThePot, true);
      this_thread::sleep_for(chrono::seconds(2));

    } 

    //* Phase 3 ( Compare Hands )
    ThePlayer.RoundFinished(TheDealer, ThePot);

  }

  return false; // The Game Goes On

}

void CalculateHandStrengths(Player& ThePlayer, Player& TheDealer, int& PlayerHandStrength, int& DealerHandStrength) { // Updates The Strength Of The Hands

  PlayerHandStrength = ThePlayer.DisplayHand("Normal", true, false); // The Second Boolean Value Does Not Actually Matter For The Player
  DealerHandStrength = TheDealer.DisplayHand("Dealer", true, false); // It Does , However, Matter To The Dealer

}

void ClearStream(const string message) {

  system("clear");

  if (message != "IGNORE") { // If There Is A Message Given, Display It
    cout << message << endl;
  }
  
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  this_thread::sleep_for(chrono::seconds(1));

}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () { // The Actual Game

  // Declare Variables
  Player TheDealer;
  Player Bob;
  int ThePot = 0;
  bool EndGame = false;
  
  while(!EndGame) { // The Game Loop

    system("clear");
    int UCStart = Bob.StartGame(); // User Choice Variables Defined Separately

    if (UCStart == 1) { // The Player Places A Bet, Play 1 Round

      if(PlayRound(Bob, TheDealer, ThePot) == true) EndGame = true;

    }
    
    else if (UCStart == 2) { // The Player Leaves The Table

      EndGame = true; // Break The Loop
      
    }

    else { // Should Never Be Reached 

      cout << "\nERROR OCCURED WITH UCStart ( int main )" << endl;
      EndGame = true; // Break The Loop

    }

   // Reset For The Next Loop
   TheDealer.StartNewRound();
   Bob.StartNewRound();
   ThePot = 0;

  }

  Bob.LeaveGame(); // Show Stats + Goodbye Screen

  return 0; // This Will Only Be Reached When The Above Loop Is Broken

}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

/* // The Roadmap For This Project

  0. ✅ Read The Rules For Blackjack
    0.1. ✅ Figure Out How To Calculate Hand Strength ( Sum ) In General
    0.2. ✅ Figure Out How To Calculate Hand Strength ( Sum ) For The Ace
    0.3. ✅ Research How To Add Graphics with C++
    0.4. ❌ Create An Implementation Plan
      0.4.1. 🚧 Learn SDL

  1. ✅ Create A User Interface For Playing
  2. ✅ Add Playing Against The Dealer
    2.1 ✅ Give The Dealer A Turn
  3. ✅ Add Different Bet Sizes
  4. ✅ Add Replayability ( A Score Of Wins And Total Games )
  5. ✅ Refactor Code
    5.0. ✅ Simplify The Round End Checks In `PlayRound`
    5.1. ✅ More Readable
      5.1.1. ✅ Remove The Switch Statement In int main()
      5.1.2. ✅ Create A Seperate Function For Finishing The Round ( check for win, win type + reward ) 
    5.2. ✅ Functions For Repetetitive Tasks 
      5.2.1. ✅ Counting + Displaying The Worth Of Cards
      5.2.2. ✅ Checking If The Round Is Over
      5.2.3. ✅ Clearing The Stream After Invalid Input

  6. 🚧 Improve User Interface ( ADD ACTUAL GRAPHICS )
    6.1. 
  


  99. ⛔︎ Create A Way To Randomly Shuffle The Deck ( just for the challenge )

*/