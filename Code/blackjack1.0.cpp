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

static const int AMOUNT_OF_SUITS = 4; // The Amount Of Suits  in the Deck
static const int AMOUNT_OF_CARDS = 13; // The Amount Of Cards in the Deck

class Player; // Declaration For Use, Definition Below ⬇️

void DisplayRound (Player& Player1, Player& Player2, const int& ThePot, const bool& RevealAll = false); // Declaration For Use, Definition Below ⬇️
int GetRandomNumber(const int& MaxNumber, const int& MinNumber = 0); // Declaration For Use, Definition Below ⬇️
void DeclareLostGame(const int& YourScore, const int& OppsScore = 123); // Declaration For Use, Definition Below ⬇️

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Card { // A Useful Way Of Storing Data

  string CardValue;
  string CardSuit;
  int CardStrength; // TODO Add this to the Deck constructor

};

struct Deck { // Manipulate The Deck

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

class Player { // The Main Structure

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

        cout << endl; // Make Space For The Hand Strength Rating

        if (HandStrength > 21 && AceInHand) { // If the Ace cannot be 11, automatically revert to 1

          if (ShowText) cout << "You Hand Strength Is " << (HandStrength - 10) << "/21"; // Here Representing The Ace As 1 ( 11 - 10 )
          AdjustedHand = true;

        }

        else if (HandStrength < 21 && AceInHand) {

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/21"; // If There Is No Overflow, Display Largest Hand
          OriginalHand = true;

        }

        else if (AceInHand) {

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/21 OR " << (HandStrength - 10) << "/21";
          OriginalHand = true;

        }

        else { // No Ace, Or Ace And No Ovelflow

          if (ShowText) cout << "You Hand Strength Is " << HandStrength << "/21";
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

        if (HandStrength > 21 && AceInHand) { // If the Ace cannot be 11, automatically revert to 1

          if (ShowText) cout << "Hand Strength Is At Least" << (HandStrength - 10) << "/21"; // Here Representing The Ace As 1 ( 11 - 10 )
          AdjustedHand = true;

        }

        else { // No Ace

          if (ShowText) cout << "Hand Strength Is At Least " << HandStrength << "/21";
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

    void LeaveGame() { // Shows The Stats ( Games Played, Games Won + Chips Left)

      system("clear");

      if (AvaliableChips <= 0) {

        cout << "You Have Lost, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else if (AvaliableChips > 0 && AvaliableChips < 20) {

        cout << "You Cannot Affort The Buy-In, Your Balance Currently Has " << AvaliableChips << " Chips Left 😭\n" << endl;

      }

      else {

        cout << "You Had " << AvaliableChips << " Chips Left 😮\n" << endl;

      }

      
      cout << "You Have Played " << TotalGames << " Games\n" << endl;
      cout << "Of Which You Won " << TotalWins << endl;

      cout << endl << "\nWell Played, And Farewell 👋 \n\n" << endl;
      this_thread::sleep_for(chrono::seconds(2));

    }

    int MakeAMove() { // Some Text Walkthrough With Options During The Round Of Play

      int UCChoice;
    
      while (true) {
    
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

    void StartNewRound() { // Remove Your Old Hand, And Get A New One

      MyHand.clear();
      GetStartingHand();

    }

    void RoundFinished(Player& YourOpponent, int& ThePot) { // Check If The Game Is Over, React Accordingly

      int YourHandStrength = DisplayHand("Normal", false, false);
      int OpponentsHandStrength = YourOpponent.DisplayHand("Dealer", true, false);

      system("clear");

      if (YourHandStrength == 21 || YourHandStrength > OpponentsHandStrength || OpponentsHandStrength > 21) { 

        //! If You Won
        TotalWins++;
        AvaliableChips+= ThePot;

        cout << "Congratulations, You WON 🎉🎉🎉" << endl;
        this_thread::sleep_for(chrono::seconds(1));

      }

      else if (OpponentsHandStrength == 21 || OpponentsHandStrength > YourHandStrength || YourHandStrength > 21) {

        //! If You Lost
        DeclareLostGame(YourHandStrength, OpponentsHandStrength);

      }

      else {

        cout << "ERROR IN THE RoundFinished FUNCTION" << endl;

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

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

void DisplayRound (Player& Player1, Player& Player2, const int& ThePot, const bool& RevealAll) { // Display Cards Of All Players, + The Pot

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

int GetRandomNumber(const int& MaxNumber, const int& MinNumber) { // For Getting A Random Card

  if (MaxNumber == MinNumber) {

    return 0;

  }

  random_device RandomSeed;
  mt19937 GenerateNumber(RandomSeed());
  uniform_int_distribution<int> DistributionRange(MinNumber, MaxNumber);

  return DistributionRange(GenerateNumber);

}

void DeclareLostGame(const int& YourScore, const int& OppsScore) { // Different Text Based On Different Loss Type

  system("clear");

  cout << setw(35) << "You LOST\n" << endl;

  if (OppsScore == 123 && YourScore > 21) { // Random Default Value => Your Hand Exceeded 21

    cout << "The Score Of Your Hand Is To Large " << YourScore << " Is Larger Than 21" << endl;;

  }

  else if (OppsScore > YourScore) {

    cout << "You Hand ( Total Of " << YourScore << " ) Was Beat By The Opponent's Hand " << OppsScore << endl;

  }

  else { // Should Not Be Reached

    cout << "ERROR IN THE LostAGame FUNCTION" << endl;

  }

  this_thread::sleep_for(chrono::seconds(1));

}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () { // The Actual Game
  system("clear");
  
  Player Bob;
  Player TheDealer;

  int UCStart;
  int UCMove;
  int ThePot = 0;

  bool EndTheRound;

  while(true) { // Infinite Game Loop

    EndTheRound = false;
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

          //! ⬇️ THIS IS PROBABLY WRONG ⬇️
          if (Bob.DisplayHand("Normal", false, false) == 21) Bob.RoundFinished(TheDealer, ThePot); // Exactly 21 = Win
          if (TheDealer.DisplayHand("Dealer", true, false) == 21) TheDealer.RoundFinished(Bob, ThePot); // Exactly 21 = Win
          //! ⬆️ THIS IS PROBABLY WRONG ⬆️

          UCMove = Bob.MakeAMove();

          if (UCMove == 1) { // Another Card

            //! ⬇️ THIS IS PROBABLY WRONG ⬇️
            if (Bob.DisplayHand("Normal", false, false) > 21) Bob.RoundFinished(TheDealer, ThePot); // Overflow = Loss 
            if (Bob.DisplayHand("Normal", false, false) == 21) Bob.RoundFinished(TheDealer, ThePot); // Exactly 21 = Win
            //! ⬆️ THIS IS PROBABLY WRONG ⬆️

            Bob.TakeACard();
            continue;

          }

          else { // End The Round

            EndTheRound = true; // escape the round

          }

        }

        system("clear");
        DisplayRound(TheDealer, Bob, ThePot, true);
        ThePot = 0; // reset the pot

        this_thread::sleep_for(chrono::seconds(2));

        // ! ADD FINAL COMPARSION OF HAND STRENGTH HERE
        // TODO Add Pot To Your Chips If You Win
        // TODO Add GamesWon++ If You Win
        Bob.RoundFinished(TheDealer, ThePot);

        break; // Necessary For THe Switch Statement

      case 2: // The Player Leaves The Table
        Bob.LeaveGame();
        return 0;

      default:
      cout << "\nERROR OCCURED WITH THE SWITCH CASE ( int main )" << endl;
        continue; // By Default Restart The Game Loop ( should never be reached )

    }

   // Reset Players For A New Round
   Bob.StartNewRound();
   TheDealer.StartNewRound();

    continue;

  }

  return 0;

}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

/* // The Roadmap For This Project

  0. ✅ Read The Rules For Blackjack
    0.1. 🚧 Figure Out How To Calculate Hand Strength ( Sum ) In General
    0.2. ✅ Figure Out How To Calculate Hand Strength ( Sum ) For The Ace

  1. ✅ Create A User Interface For Playing
  2. 🚧 Add Playing Against The Dealer ( Random Moves )
    - 1 Game, Many Turns
    - Start With 2 Cards
    - You Take Or Don't
    - Want To Get To 21
    - Lose If Opp. Get's More, Or If You Get Above 21
  3. ❌ Add Multiplayer ( Playing Against Yourself )
  4. ✅ Add Replayability ( A Score Of Wins And Total Games )
  5. 🚧 Add Bets
  6. ❌ Improve Dealer's Strategy ( Make The Dealer Play OPTIMALLY )
  7. ❌ Refactor Code
    - 7.1. ❌ More Readable
      - 7.1.1.❌ Remove The Switch Statement In int main()
    - 7.2. ❌ Functions For Repetitions 
      - 7.2.1. ❌ Counting + Displaying The Worth Of Cards
  8. 
  

  98. ⛔︎ Improve User Interface ( ADD ACTUAL GRAPHICS )
  99. ⛔︎ Create A Way To Randomly Shuffle The Deck ( just for the challenge )

*/