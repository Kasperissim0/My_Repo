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

  cout << "How Can I Help You ?\n\n" << endl;


  cout << left << setw(20) << "Leave A Message";
  cout << right << setw(40) << "Press 1" << endl;

  cout << left << setw(19) << "Interact With A Message";
  cout << right << setw(38) << "Press 2\n" << endl;

  cout << left << setw(9) << "Exit";
  cout << right << setw(52) << "Press 3\n" << endl;

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
void MessageInteractionOptions () {

  system("clear");
  
  cout << "What Do You Want To Do ?\n\n" << endl;

  cout << left << "Read a Message";
  cout << right << setw(30) << "Press 1" << endl;

  cout << left << "Edit a Message";
  cout << right << setw(30) << "Press 2" << endl;

  cout << left << "\nDelete a Message";
  cout << right << setw(30) << "Press 3\n\n" << endl;


}
string TrimBlankSpace (const string& input) {

  auto StringStart = find_if_not(input.begin(), input.end(), ::isspace); // Find First Non-Space Charachter
  auto StringEnd = find_if_not(input.rbegin(), input.rend(), ::isspace).base(); // Find Last Non-Space Charachter

  string TrimmedString = string(StringStart, StringEnd); // Create a String Starting Without the Spaces
 
  return TrimmedString;

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
    string warning = "Remember, You Won't Be Able To Acess Your Message Without Your Password, And It CANNOT Be Changed\n";

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
                bool ValidUserInput = UCConfirmInput(data.password, "password", true, warning);

              if (ValidUserInput == true) {

                system("clear");
                cout << "This is Your Title: " << "'" << TrimBlankSpace(data.title) << "'\n" << endl
                    << "This is Your Message: "  << "'" << TrimBlankSpace(data.message) << "'\n" << endl
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
int DisplayMessages (const vector<Information>& DataStorage, const string& UserActionWithTitle) {

  int ChosenMessage;
  bool ValidInputMainMenu;
  
  // Show All Titles in the Vector
  select_message:
    system("clear");
    cout << setw(50) << "Select The Message You Want to " << UserActionWithTitle << ":\n\n\n";
    this_thread::sleep_for(chrono::seconds(1));

  for (int a = 0; a < DataStorage.size(); a++) {

    if (a >= 9 && a < 100) {

      cout << left << (a + 1) << ".     ";
      cout << left << setw(50) << ("   '" + TrimBlankSpace(DataStorage[a].title) + "'"); 
      cout << "If You Wish To ";;
      cout << left << UserActionWithTitle << " this Message:                ->  Press ";
      cout << left << setw(2) << (a + 1) << " <-" << endl;

    }

    else if (a >= 99 && a < 1000) {

      cout << left << (a + 1) << ".    ";
      cout << left << setw(50) << ("   '" + TrimBlankSpace(DataStorage[a].title) + "'"); 
      cout << "If You Wish To ";
      cout << left << UserActionWithTitle << " this Message:                ->  Press ";
      cout << left << setw(2) << (a + 1) << " <-" << endl;

    }

    else if (a >= 999) {

      cout << left << (a + 1) << ".   ";
      cout << left << setw(50) << ("   '" + TrimBlankSpace(DataStorage[a].title) + "'"); 
      cout << "If You Wish To ";
      cout << left << UserActionWithTitle << " this Message:                ->  Press ";
      cout << left << setw(2) << (a + 1) << " <-" << endl;

    }

    else {

      cout << left << (a + 1) << ".      ";
      cout << left << setw(50) << ("   '" + TrimBlankSpace(DataStorage[a].title) + "'"); 
      cout << "If You Wish To ";
      cout << left << UserActionWithTitle << " this Message:                ->  Press ";
      cout << left << setw(2) << (a + 1) << " <-" << endl;

    }

  }

  // Add an Exit to the Menu
  cout << "\n\nIf You Wish To Go Back To The Menu:                -> Press " << DataStorage.size() + 1 << " <-" << endl
       << "\n\n\n" << right << setw(45) << "Which Message Do You Wish To " << UserActionWithTitle <<" ?" << endl;
 

  // Get UserChoice
  cin >> ChosenMessage;
  ValidInputMainMenu = ValidateInput(ChosenMessage, DataStorage.size() + 1); 
  
  // Validate input
  if (ValidInputMainMenu == false) {

  goto select_message;

  }
       
  else {

    return ChosenMessage;

  }

}
bool GrantAcessToMessage (const vector<Information>& DataStorage, const int& ChosenMessage) {

  int ChosenMessagePosition = ChosenMessage - 1;
  string ActualPassword = DataStorage[ChosenMessagePosition].password;
  string AttemptedPassword;

  // Check if there is a Password for this Message 
  if (!DataStorage[ChosenMessagePosition].HasPassword) {

    return true;

  }

  // If Password Exists Verify Password
  else {

    system("clear");
    cout << "This Message is Password Locked, Enter the Password to Gain Acess: " << endl;
    cin >> AttemptedPassword;

    if (AttemptedPassword == ActualPassword) {

      return true;

    }

    else {

      return false;

    }

  }

}

/* //? Test Data (AI Generated)
vector<Information> GenerateTestData() {

  vector<Information> testData;
  
  // Message 1 - No password
  Information msg1;
  msg1.title = "Welcome Message";
  msg1.message = "Welcome to our messaging system! This is a test message to demonstrate the functionality.";
  msg1.HasPassword = false;
  msg1.MessageConfirmed = true;
  msg1.TitleConfirmed = true;
  testData.push_back(msg1);

  // Message 2 - With password
  Information msg2;
  msg2.title = "Personal Note";
  msg2.message = "Remember to check the monthly reports and update the spreadsheet by Friday.";
  msg2.HasPassword = true;
  msg2.password = "123";
  msg2.MessageConfirmed = true;
  msg2.TitleConfirmed = true;
  testData.push_back(msg2);

  // Message 3 - No password
  Information msg3;
  msg3.title = "Meeting Minutes";
  msg3.message = "Team meeting outcomes: 1. Project deadline extended 2. New team member joining next week 3. Budget approved";
  msg3.HasPassword = false;
  msg3.MessageConfirmed = true;
  msg3.TitleConfirmed = true;
  testData.push_back(msg3);

  // Message 4 - With password
  Information msg4;
  msg4.title = "Confidential Project Update";
  msg4.message = "The new feature implementation is ahead of schedule. Beta testing to begin next week.";
  msg4.HasPassword = true;
  msg4.password = "123";
  msg4.MessageConfirmed = true;
  msg4.TitleConfirmed = true;
  testData.push_back(msg4);

  // Message 5 - No password
  Information msg5;
  msg5.title = "Lunch Menu";
  msg5.message = "Today's specials: Grilled chicken salad, Vegetarian pasta, Fish and chips";
  msg5.HasPassword = false;
  msg5.MessageConfirmed = true;
  msg5.TitleConfirmed = true;
  testData.push_back(msg5);

  // Message 6 - With password
  Information msg6;
  msg6.title = "Birthday Plans";
  msg6.message = "Surprise party planning details: Location - Conference Room B, Time - 3 PM, Friday";
  msg6.HasPassword = true;
  msg6.password = "123";
  msg6.MessageConfirmed = true;
  msg6.TitleConfirmed = true;
  testData.push_back(msg6);

  // Message 7 - No password
  Information msg7;
  msg7.title = "Office Announcement";
  msg7.message = "The office will be closed for maintenance this Saturday. Please ensure all equipment is properly shut down.";
  msg7.HasPassword = false;
  msg7.MessageConfirmed = true;
  msg7.TitleConfirmed = true;
  testData.push_back(msg7);

  // Message 8 - With password
  Information msg8;
  msg8.title = "Financial Report";
  msg8.message = "Q3 financial results: Revenue up 15%, Expenses down 8%, Net profit increased by 22%";
  msg8.HasPassword = true;
  msg8.password = "123";
  msg8.MessageConfirmed = true;
  msg8.TitleConfirmed = true;
  testData.push_back(msg8);

  // Message 9 - No password
  Information msg9;
  msg9.title = "IT Update";
  msg9.message = "System maintenance scheduled for tonight. Expected downtime: 2 hours. Please save all work.";
  msg9.HasPassword = false;
  msg9.MessageConfirmed = true;
  msg9.TitleConfirmed = true;
  testData.push_back(msg9);

  // Message 10 - With password
  Information msg10;
  msg10.title = "Client Meeting Notes";
  msg10.message = "Key points from client meeting: New requirements discussed, Timeline adjusted, Budget increased";
  msg10.HasPassword = true;
  msg10.password = "123";
  msg10.MessageConfirmed = true;
  msg10.TitleConfirmed = true;
  testData.push_back(msg10);

  // Message 11 - No password
  Information msg11;
  msg11.title = "Team Building Event";
  msg11.message = "Next month's team building event will be held at Adventure Park. Please confirm your attendance.";
  msg11.HasPassword = false;
  msg11.MessageConfirmed = true;
  msg11.TitleConfirmed = true;
  testData.push_back(msg11);

  // Message 12 - With password
  Information msg12;
  msg12.title = "Performance Reviews";
  msg12.message = "Annual performance reviews will begin next week. Schedule will be sent individually.";
  msg12.HasPassword = true;
  msg12.password = "123";
  msg12.MessageConfirmed = true;
  msg12.TitleConfirmed = true;
  testData.push_back(msg12);

  // Message 13 - No password
  Information msg13;
  msg13.title = "Holiday Schedule";
  msg13.message = "Updated holiday schedule for the next quarter has been posted on the bulletin board.";
  msg13.HasPassword = false;
  msg13.MessageConfirmed = true;
  msg13.TitleConfirmed = true;
  testData.push_back(msg13);

  // Message 14 - With password
  Information msg14;
  msg14.title = "Project Milestone";
  msg14.message = "Phase 1 completed successfully. All deliverables met. Moving to Phase 2 next week.";
  msg14.HasPassword = true;
  msg14.password = "123";
  msg14.MessageConfirmed = true;
  msg14.TitleConfirmed = true;
  testData.push_back(msg14);

  // Message 15 - No password
  Information msg15;
  msg15.title = "Office Supply Inventory";
  msg15.message = "Please submit your office supply requests by end of week. New order being placed Monday.";
  msg15.HasPassword = false;
  msg15.MessageConfirmed = true;
  msg15.TitleConfirmed = true;
  testData.push_back(msg15);

  return testData;

}
*/


/* 

  1.  [x] Simplify Everything
  2.  [x] Add Multiple Messages
  3.  [x] Add Paswords
  4.  [x] SHORTEN: Create a Function for the (This is your ... , Do You Confirm the that this is your ...)
  5.  [x] Add Editing Messages
  6.  [x] Add Deleting Messages 
    
*/ 



int main() {
    
  // Initate Variables
  vector<Information> data; // = GenerateTestData(); //? Test Data (Messages + Titles + Passwords)
  int UCMainMenu; // UC = User Choice


  main_menu: 
  
    ShowMainMenu();
    cin >> UCMainMenu;
    bool ValidInputMainMenu = ValidateInput(UCMainMenu, 3);

  if (ValidInputMainMenu == false) {

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
    
    // Interact With a Message
    else if (UCMainMenu == 2) {

      int UCRead;
      int UCEdit;
      int UCDelete;
      int UCMessageInteract;
      bool ValidInputInteract = false;

      // If there are no messages direct back to start
      if (data.empty() == true) {

        system("clear");
        cout << "No Messages Currently Exist" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        goto main_menu;

      }

      else if (data.empty() == false) {

        // Show Avaliable Options
        message_interact:
          MessageInteractionOptions();

          cin >> UCMessageInteract;
          ValidInputInteract = ValidateInput(UCMessageInteract, 3);
        
        // Validate User Input
        if (ValidInputInteract == false) {

          goto message_interact;

        }


        // Read a Message
        else if (ValidInputInteract == true && UCMessageInteract == 1) {

          UCRead = DisplayMessages(data, "Read"); // Display ALL Message Titles Here + Get The User's Choice

          // Show Selected Message (-1 from User Choice because of 0 indexing)
          if (UCRead <= data.size()) {

            bool AllowedToReadMessage = GrantAcessToMessage(data, UCRead);

            // Correct Password
            if (AllowedToReadMessage) {

              system("clear");
              cout << "Title: " << TrimBlankSpace(data[UCRead - 1].title) << '\n' << '\n' 
                  << "Content:" << endl << endl << data[UCRead - 1].message << endl;
              this_thread::sleep_for(chrono::seconds(4));
              goto main_menu;

            }
            // Incorrect Password
            else {

              system("clear");
              cout << "Incorrect Password" << endl;
              this_thread::sleep_for(chrono::seconds(2));

              UCRead = DisplayMessages(data, "Read"); // Display ALL Message Titles Here + Get The User's Choice

            }


          }
          
            else if (UCRead == data.size() + 1) {

              goto main_menu;

            }

        }
        
        // Edit a Message
        else if (ValidInputMainMenu == true && UCMessageInteract == 2) {

          UCEdit = DisplayMessages(data, "Edit"); // Display ALL Message Titles Here + Get The User's Choice

          // Show Selected Message (-1 from User Choice because of 0 indexing)
          if (UCEdit <= data.size()) {

            bool AllowedToEditMessage = GrantAcessToMessage(data, UCEdit);
            string OldMessage = data[UCEdit - 1].message;
            string OldTitle = data[UCEdit - 1].title;
            string NewMessage;
            bool NewMessageSet;
            string NewTitle;
            bool NewTitleSet;

            // Correct Password, change message
            if (AllowedToEditMessage) {

              reset_start:
                system("clear");
                cout << "Old Title: " << TrimBlankSpace(OldTitle) << '\n' << '\n' 
                     << "\nOld Message:" << endl << endl << OldMessage << endl;
                this_thread::sleep_for(chrono::milliseconds(40));


              cout << "\n\n\n\nNew Message: ";
              cin.get();
              getline(cin, NewMessage);
              cin.clear();

              if (NewMessage.empty()) {

                system("clear");
                cout << "Message Cannot be Empty" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                goto reset_start;

              }

              NewMessageSet = UCConfirmInput(NewMessage, "message", true);

              if (NewMessageSet == false) {

                goto reset_start;

              }

              // Message Changed, now Changing Title
              else {

                data[UCEdit - 1].message = NewMessage;

                reset_last:
                  system("clear");

                  cout << "Old Title: " << TrimBlankSpace(OldTitle) << '\n' << '\n' 
                       << "\nOld Message:" << endl << endl << OldMessage << endl
                       << "\n\n\n\nNew Message: " << NewMessage << endl;

                  cout << '\n' << "New Title: ";
                  cin.get();
                  getline(cin, NewTitle);
                  cin.clear();

                  if (NewTitle.empty()) {

                    system("clear");
                    cout << "Title Cannot be Empty" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    goto reset_last;

                  }

                  NewTitleSet = UCConfirmInput(NewTitle, "title", true);

                if (NewTitleSet == false) {

                  goto reset_last;

                }

                // Both Message and Title Changed
                else {

                  data[UCEdit - 1].title = NewTitle;

                  system("clear");
                  cout << "Changes Saved" << endl;
                  this_thread::sleep_for(chrono::seconds(2));

                  goto main_menu;

                }

              }

            }
            // Incorrect Password
            else {

              system("clear");
              cout << "Incorrect Password" << endl;
              this_thread::sleep_for(chrono::seconds(2));

              UCEdit = DisplayMessages(data, "Edit"); // Display ALL Message Titles Here + Get The User's Choice

            }


          }
          
            else if (UCEdit == data.size() + 1) {

              goto main_menu;

            }

        }

        // Delete a Message 
        else if (ValidInputMainMenu == true && UCMessageInteract == 3) {

          UCDelete = DisplayMessages(data, "Delete"); // Display ALL Message Titles Here + Get The User's Choice

          if (UCDelete <= data.size()) {

            bool AllowedToDeleteMessage = GrantAcessToMessage(data, UCDelete); // Check Password

            // Incorrect Password
            if (!AllowedToDeleteMessage) {

              system("clear");
              cout << "Incorrect Password" << endl;
              this_thread::sleep_for(chrono::seconds(2));

              UCEdit = DisplayMessages(data, "Delete"); // Display ALL Message Titles Here + Get The User's Choice

            }
            
            // Correct Password, Deletion Allowed
            else {

              data.erase(data.begin() + (UCDelete - 1));

              system("clear");
              cout << "Message Deleted" << endl;
              this_thread::sleep_for(chrono::seconds(2));
              system("clear");

              goto main_menu;
            }

          }

          else if (UCDelete == data.size() + 1) {

            goto main_menu;

          }

        }

      }

     }

  return 0;

}