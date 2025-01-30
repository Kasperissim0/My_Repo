#include <iostream>
#include <string>
#include <iomanip> // Include this for setw()
#include <cstdlib> // Include this for system()
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm> 

using namespace std;

struct Information {

  string message;
  string title;
  bool MessageConfirmed;
  bool TitleConfirmed;

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
void YesORNoChoice () {

  cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl
       << setw(19) << "No" << setw(41) << "Press 2" << endl;

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
string RequestMessage () {

    int UCMessage;
    string message;
    bool MessageConfirmed = false;

    while (MessageConfirmed == false) {

        insert_message:

            CleanLine();
            system("clear");
            cout << "Insert Your Message Here: \n";
            getline(cin, message);

        if (message.empty()) {

            // Ensure Message exists
            cout << "Message Cannot be Empty" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto insert_message;

        }

        else if (message.empty() == false) {

            confirm_message:
        
                // Show message and ask for confirmation
                system("clear");
                cout << "This Is Your Message: \n\n" << "'" << TrimBlankSpace(message) << "'" << endl
                     << "\nDo You Confirm That This Is Your Message ?\n\n";

                YesORNoChoice();

                cin >> UCMessage;
                bool ValidUserInput = ValidateInput(UCMessage, 2);

            if (ValidUserInput == false) {

              goto confirm_message;

            }

            else if (UCMessage == 1) {

                system("clear");
                cout << "Your Message Has Been Saved" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                MessageConfirmed = true;
                break;

            }
            else if (UCMessage == 2) {

                system("clear");
                goto insert_message;

            }

        }

    }

    return message;
    
}
Information DoubleRequest () {

    Information package;
    
    int UCTitle;
    package.message = TrimBlankSpace(RequestMessage());
    package.MessageConfirmed = true;
    package.TitleConfirmed = false;

    while (package.TitleConfirmed == false) {

      insert_title:

          CleanLine();
          system("clear");
          cout << "Create a Title for You Message:" << endl;
          getline(cin, package.title);

      if (package.title.empty() == true) {

          // Ensure Title exists
          cout << "Title Cannot be Empty" << endl;
          this_thread::sleep_for(chrono::seconds(2));
          goto insert_title;

      }

      else if (package.title.empty() == false) {

          package.title = TrimBlankSpace(package.title);

          confirm_title:

              // Show title and ask for confirmation
              system("clear");
              cout << "This Is Your Title: \n\n" << "'" << package.title << "'" << endl;
              cout << "\nDo You Confirm That This Is Your Title ?\n\n";

              YesORNoChoice();

              cin >> UCTitle;
              bool ValidUserInput = ValidateInput(UCTitle, 2);

          if (ValidUserInput == false) {

            goto confirm_title;

          }

          else if (UCTitle == 1) {
  
              system("clear");
              cout << "This is Your Title: " << "'" << package.title << "'\n" << endl
                  << "This is Your Message: "  << "'" << package.message << "'\n" << endl;
              this_thread::sleep_for(chrono::seconds(5));
              system("clear");
              package.TitleConfirmed = true;
              break;

          }
          
          else if (UCTitle == 2) {

            goto insert_title;

          }


      }


    }

    return package;

}



/* 

    1.  [ ] Simplify Everything <- Make Evertyting a Seperate Function ⬇️ ( int main = only function calls )
    2.  [ ] Add Multiple Messages
    3.  [ ] Add Editing Messages
    4.  [ ] Add Deleting Messages
    5.  [ ] Add Paswords

    
*/ 



int main() {
    
  // Initate Variables
  string message;
  string title;
  bool MessageConfirmed = false;
  bool TitleConfirmed = false;
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

      quit_choice:

        int UCQuit;

          system("clear");
          cout << "Are You Sure ?" << endl 
               << "All Your Messages Will Be Erased\n" << endl;

           YesORNoChoice();

          cin >> UCQuit;
          UserInputValid = ValidateInput(UCQuit, 2);

      if (UserInputValid == false) {

        goto quit_choice;

      }
      else if (UCQuit == 1) {

        system("clear");
        cout << "Exiting Program, Goodbye." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("clear");
        return 0;

      } 
      else if (UCQuit == 2) {

        system("clear");
        goto main_menu;

      }

    }
    
    // Leave a Message
    else if (UCMainMenu == 1) {

      if (title.empty() == true) {

        init_package:

          Information data = DoubleRequest();

          title = data.title;
          message = data.title;
          MessageConfirmed = data.MessageConfirmed;
          TitleConfirmed = data.TitleConfirmed;

          goto main_menu;
          

      }

      else if (title.empty() == false) {

        replace_message:

          int UCToOverride;

          system("clear");

          cout << "You Already Have a Message Titled: " << "'" << title << "'" << " Saved.\n" << endl
               << "Do You Wish To Override It ?" << endl;

          YesORNoChoice();
          cin >> UCToOverride;
          UserInputValid = ValidateInput(UCToOverride, 2);

          if (UserInputValid == false) {

            goto replace_message;

          }

          else if (UCToOverride == 1) {

            goto init_package;

          }
          
          else if (UCToOverride == 2) {

            goto main_menu;

          }


      } 


    }
    
    // Read a Message
    else if (UCMainMenu == 2) {

      int UCRead;

      if (title.empty() == true) {

        system("clear");
        cout << "There Are No Messages To Read" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        goto main_menu;

      }

      else if (title.empty() == false) {

        select_message:

          system("clear");
          cout << setw(50) << "Select The Message You Want to Read: \n\n";
          this_thread::sleep_for(chrono::seconds(1));
          cout << "1." << setw(20) << title << endl;

          cout << "\n\n\nDo You Wish to Read the Message Titled: " << setw(25) << "'" << title << "'" << " ?\n" << endl;
          
          YesORNoChoice();

          cin >> UCRead;
          UserInputValid = ValidateInput(UCRead);


      if (UserInputValid == false) {

       goto select_message;

      }

      else if (UCRead == 1) {

          system("clear");
          cout << "Title: " << title << '\n' << '\n' 
              << "Content:" << endl << endl << message << endl;
          this_thread::sleep_for(chrono::seconds(4));
          goto main_menu;

      }

      else if (UCRead == 2) {

          goto main_menu;

      }

    }

  }

  return 0;

}