#include <iostream>
#include <string>
#include <iomanip> // Include this for setw()
#include <cstdlib> // Include this for system()
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm> 
#include <vector>
#include <cctype> // Required for toupper (capitalize lowercase letter)

using namespace std;

struct Information {

  int UserChoice;
  string message;
  string title;
  string password;
  bool MessageConfirmed;
  bool TitleConfirmed;
  bool HasPassword;

};


void ShowMainMenu() {

  system("clear");

  cout << "How Can I Help You ?\n" << endl;
  cout << setw(20) << "Leave A Message" << setw(40) << "Press 1" << endl;
  cout << setw(19) << "Read A Message" << setw(41) << "Press 2" << endl;
  cout << setw(9) << "Exit" << setw(51) << "Press 3" << endl;

}
void CleanLine () {

    // Clear the input buffer to ensure no leftover input interferes
    cin.clear(); // Clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove any leftover characters, including '\n'

}
void YesORNoChoice (string const& Message1 = "Yes", string const& Message2 = "No") {

  cout << setw(20) << Message1 << setw(40) << "Press 1" << endl
       << setw(19) << Message2 << setw(41) << "Press 2" << endl;

}
bool ValidateInput (const int& UserChoice, const int& AmountOfOptions = 2, const int& MinValue = 1){

  if (cin.fail() || UserChoice > AmountOfOptions || UserChoice < MinValue) {

    CleanLine();
    system("clear");
    cout << "Please select from the given options." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
    return false;

  }

  return true;


}
string TrimBlankSpace (const string& input) {

  auto StringStart = find_if_not(input.begin(), input.end(), ::isspace); // Find First Non-Space Charachter
  auto StringEnd = find_if_not(input.rbegin(), input.rend(), ::isspace).base(); // Find Last Non-Space Charachter

  string TrimmedString = string(StringStart, StringEnd); // Create a String Starting Without the Spaces
 
  return TrimmedString;

}
bool UCConfirmInput (const string& input, string InputType, const bool& RepeatInput = false, const string& ExtraMessage = "") {

  Information data;

  bool ValidUserInput = false;
  InputType = TrimBlankSpace(InputType);
  vector<char> CapitalizedInputType;

  for (char letter: InputType) {

    CapitalizedInputType.push_back(letter);

  }

  CapitalizedInputType[0] = toupper(CapitalizedInputType[0]);

  if (RepeatInput == false) {

    goto final_confirm;

  }

  confirm_input:
    system("clear");
    cout << "This Is Your ";
    for (char letter: CapitalizedInputType){

      cout << letter;

    }
    cout << ":\n\n" << "'" << TrimBlankSpace(input) << "'" << endl
         << "\nDo You Confirm That This Is Your ";
    for (char letter: CapitalizedInputType) {

      cout << letter;

    } 
    cout << " ?\n\n";

  final_confirm:
    if (ExtraMessage.empty() == false) {

      cout << ExtraMessage << '\n';

    }
    
    YesORNoChoice();

    cin >> data.UserChoice;
    ValidUserInput = ValidateInput(data.UserChoice);

    if (ValidUserInput == false) {
        
        if (ValidUserInput == false && RepeatInput == false) {

        goto final_confirm;

        }

        else if (ValidUserInput == false && RepeatInput == true) {

          goto confirm_input;

        }

      }
    
    else if (data.UserChoice == 1) {

      system("clear");
      return true;

    }

    else if (data.UserChoice == 2) {

      system("clear");
      return false;

    }

return false; // to satisfy the compiler (will never be reached)
}
string RequestMessage () {

  Information data;

    while (true) {

      CleanLine();
      system("clear");
      cout << "Insert Your Message Here: \n";
      getline(cin, data.message);

      if (data.message.empty()) {

        cout << "Message Cannot be Empty" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        continue;

      }

      else if (data.message.empty() == false) {

        data.MessageConfirmed = UCConfirmInput(data.message,"message", true);

        if (data.MessageConfirmed == true) {
        
          return data.message;

        }
        else {

          continue;

        }
      
      }

    }

}
Information DoubleRequest () {

    Information data;
    
    bool UCTitle;
    bool UCPassword;
    data.message = TrimBlankSpace(RequestMessage());
    data.MessageConfirmed = true;
    data.TitleConfirmed = false;

    while (data.TitleConfirmed == false) {

      insert_title:

          CleanLine();
          system("clear");
          cout << "Create a Title for You Message:" << endl;
          getline(cin, data.title);

      if (data.title.empty() == true) {

          // Ensure Title exists
          cout << "Title Cannot be Empty" << endl;
          this_thread::sleep_for(chrono::seconds(2));
          goto insert_title;

      }

      else if (data.title.empty() == false) {

        confirm_title:

          UCTitle = UCConfirmInput(data.title, "title", true);

        if (UCTitle == true) {
            
            create_pass:
              system("clear");
              UCPassword = UCConfirmInput("void", "void", false, "Do You Wish To Protect Your Message With a Password ?\n");

            // No Password
            if (UCPassword == false) {

              system("clear");
              cout << "This is Your Title: " << "'" << data.title << "'\n" << endl
                  << "This is Your Message: "  << "'" << data.message << "'\n" << endl;
              this_thread::sleep_for(chrono::seconds(5));
              system("clear");
              data.HasPassword = false;
              data.TitleConfirmed = true;
              break;

            }

            // With a Password
            else if (UCPassword == true) {

                system("clear");
                cout << "Insert Your Password:" << endl;
                cin >> data.password;

              // Double Check Password
              pass_check:
                system("clear");
                bool ValidUserInput = UCConfirmInput(data.password, "password", true, "Remember, You Won't Be Able To Acess Your Message Without Your Password.\n");

              if (ValidUserInput == true) {

                system("clear");
                cout << "This is Your Title: " << "'" << data.title << "'\n" << endl
                    << "This is Your Message: "  << "'" << data.message << "'\n" << endl
                    << "This is Your Password: " << data.password << "\n" << endl;
                this_thread::sleep_for(chrono::seconds(5));
                system("clear");
                data.HasPassword = true;
                data.TitleConfirmed = true;
                break;

              }
              else if (ValidUserInput == false) {

                goto create_pass;

              }

            }

        }
        
        else if (UCTitle == false) {

            goto insert_title;

          }


      }


    }

    return data;

}

void GenerateTestData(vector<Information>& data) {
    // Create several Information objects with test content
    Information msg1;
    msg1.title = "Daily Report";
    msg1.message = "Today's meeting went well. We discussed the upcoming project timeline and assigned tasks to team members.";
    msg1.MessageConfirmed = true;
    msg1.TitleConfirmed = true;
    data.push_back(msg1);

    Information msg2;
    msg2.title = "Shopping List";
    msg2.message = "Milk, eggs, bread, cheese, fruits, vegetables, and don't forget to pick up cat food!";
    msg2.MessageConfirmed = true;
    msg2.TitleConfirmed = true;
    data.push_back(msg2);

    Information msg3;
    msg3.title = "Birthday Party";
    msg3.message = "Remember to organize Sarah's surprise birthday party next Saturday. Need to order cake and decorations.";
    msg3.MessageConfirmed = true;
    msg3.TitleConfirmed = true;
    data.push_back(msg3);

    Information msg4;
    msg4.title = "Project Ideas";
    msg4.message = "1. Create a mobile app\n2. Design new website\n3. Develop game prototype\n4. Write technical documentation";
    msg4.MessageConfirmed = true;
    msg4.TitleConfirmed = true;
    data.push_back(msg4);

    Information msg5;
    msg5.title = "Vacation Plans";
    msg5.message = "Book flights for summer vacation. Check hotels in Paris and Rome. Make restaurant reservations.";
    msg5.MessageConfirmed = true;
    msg5.TitleConfirmed = true;
    data.push_back(msg5);

    Information msg6;
    msg6.title = "Bug Fixes";
    msg6.message = "Fixed memory leak in main loop. Updated user interface. Resolved login issues. Testing needed.";
    msg6.MessageConfirmed = true;
    msg6.TitleConfirmed = true;
    data.push_back(msg6);

    Information msg7;
    msg7.title = "Movie List";
    msg7.message = "Must watch: The Matrix, Inception, Interstellar, The Dark Knight, and The Shawshank Redemption";
    msg7.MessageConfirmed = true;
    msg7.TitleConfirmed = true;
    data.push_back(msg7);

    Information msg8;
    msg8.title = "Recipe Notes";
    msg8.message = "Grandma's secret chocolate cake recipe: 2 cups flour, 1 cup sugar, 3 eggs, 1 cup milk, vanilla extract...";
    msg8.MessageConfirmed = true;
    msg8.TitleConfirmed = true;
    data.push_back(msg8);
}


/* 

  1.  [x] Simplify Everything
  2.  [x] Add Multiple Messages
  3.  [x] Add Paswords
  4.  [x] SHORTEN: Create a Function for the (This is your ... , Do You Confirm the that this is your ...)
  4.  [ ] Add Editing Messages
  5.  [ ] Add Deleting Messages 
    
*/ 



int main() {
    
  // Initate Variables
  vector<Information> data;
  GenerateTestData(data); // TODO Delete this later.
  int UCMainMenu; // UC = User Choice


  main_menu: 

    ShowMainMenu();
    cin >> UCMainMenu;
    bool UserInputValid = ValidateInput(UCMainMenu, 3);

  if (UserInputValid == false) {

    goto main_menu;

  }

    // Exit the Programm  
    else if (UCMainMenu == 3) {

      bool UCQuit;

      system("clear");
      cout << "Are You Sure ?" << endl << "All Your Messages Will Be Erased\n" << endl;

      UCQuit = UCConfirmInput("void", "void");

      if (UCQuit == true) {

        system("clear");
        cout << "Exiting Program, Goodbye." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("clear");
        return 0;

      } 
      
      else {

        system("clear");
        goto main_menu;

      }

    }
    
    // Leave a Message
    else if (UCMainMenu == 1) {

      Information NewInfoPackage = DoubleRequest();

      data.insert(data.rbegin().base(), NewInfoPackage);

      goto main_menu;

    }
    
    
    // Read a Message
    else if (UCMainMenu == 2) {

      int UCRead;

      // If there are no messages direct back to start
      if (data.empty() == true) {

        system("clear");
        cout << "There Are No Messages To Read" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        goto main_menu;

      }

      else if (data.empty() == false) {
        
        // Show All Titles in the Vector
        select_message:

          system("clear");
          cout << setw(50) << "Select The Message You Want to Read: \n\n";
          this_thread::sleep_for(chrono::seconds(1));

          for (int a = 0; a < data.size(); a++) {

           cout << left << setw(2) << a + 1 << ". ";
           cout << left << setw(50) << ("   '" + data[a].title + "'"); 
           cout << setw(39) << "If You Wish To Read this Message:                ->  Press ";
           cout << left << setw(2) << (a + 1) << " <-" << endl;

          }
          // Add an Exit to the menu
          cout << "\nIf You Wish To Go Back To The Menu:                -> Press " << data.size() + 1 << " <-" << endl
               << "\n\n\n" << right << setw(45) << "Which Message Do You Wish To Read ?" << endl;

          cin >> UCRead;
          UserInputValid = ValidateInput(UCRead, data.size() + 1); 
          
      }
      // Validate input
      if (UserInputValid == false) {

       goto select_message;

      }
      // Show Selected Message (-1 from User Choice because of 0 indexing)
      else if (UCRead <= data.size()) {

        // Check for a password
        if (data[UCRead - 1].HasPassword == false) {

          system("clear");
          cout << "Title: " << data[UCRead - 1].title << '\n' << '\n' 
               << "Content:" << endl << endl << data[UCRead - 1].message << endl;
          this_thread::sleep_for(chrono::seconds(4));
          goto main_menu;

        }
        // Password Found
        else if (data[UCRead - 1].HasPassword == true) {

          string AttemptedPassword;
          
          system("clear");

          cout << "This Message is Password Locked, Enter the Password to Gain Acess: " << endl;
          cin >> AttemptedPassword;

          // Correct Password
          if (AttemptedPassword == data[UCRead - 1].password) {

            system("clear");
            cout << "Title: " << data[UCRead - 1].title << '\n' << '\n' 
                 << "Content:" << endl << endl << data[UCRead - 1].message << endl;
            this_thread::sleep_for(chrono::seconds(4));
            goto main_menu;

          }
          // Incorrect Password
          else if (AttemptedPassword != data[UCRead - 1].password) {

            system("clear");
            cout << "Incorrect Password" << endl;
            this_thread::sleep_for(chrono::seconds(2));

            goto main_menu;

          }


        }

      }
      else if (UCRead == data.size() + 1) {

        goto main_menu;

      }

  }

  return 0;

}