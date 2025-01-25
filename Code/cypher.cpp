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

string ReverseSentence(const string& sentence) {

  char ReversedSentenceCharachters[sentence.length() + 1]; // +1 for null terminator

    for (int i = sentence.length(); i > 0; i--) { 
      // Reverse the string into the Array

      ReversedSentenceCharachters[i - 1] = sentence[sentence.length() - i];
      
    }

    ReversedSentenceCharachters[sentence.length()] = '\0'; // Null-terminate the string


    return string(ReversedSentenceCharachters); // Return the reversed string

}
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
string TrimBlankSpace (const string& input) {

  auto StringStart = find_if_not(input.begin(), input.end(), ::isspace); // Find First Non-Space Charachter
  auto StringEnd = find_if_not(input.rbegin(), input.rend(), ::isspace).base(); // Find Last Non-Space Charachter

  string TrimmedString = string(StringStart, StringEnd); // Create a String Starting Without the Spaces
 
  return TrimmedString;

}
string RequestMessage () {

    int Choice1a;
    string message;
    bool MessageConfirmed = false;

    while (MessageConfirmed == false) {

        start:
            CleanLine();
            system("clear");
            cout << "Insert Your Message Here: \n";
            getline(cin, message);

        if (message.empty()) {

            // Ensure Message exists
            cout << "Message Cannot be Empty" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto start;

        }
        else if (message.length() > 0) {

            ask:
                // Show message and ask for confirmation
                system("clear");
                cout << "This Is Your Message: \n\n" << "'" << TrimBlankSpace(message) << "'" << endl;
                cout << "\nDo You Confirm That This Is Your Message ?\n\n";

                cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl;
                cout << setw(19) << "No" << setw(41) << "Press 2" << endl;

                cin >> Choice1a;

            if (cin.fail() || (Choice1a != 1 && Choice1a != 2)) {

                CleanLine();
                system("clear");
                cout << "Please select from the given options." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                goto ask;

            }
            else if (Choice1a == 1) {

                system("clear");
                cout << "Your Message Has Been Saved" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                MessageConfirmed = true;
                break;

            }
            else if (Choice1a == 2) {

                system("clear");
                goto start;

            }

        }

    }

    return message;
    
}
Information DoubleRequest () {

    Information package;
    
    int Choice1b;
    package.message = TrimBlankSpace(RequestMessage());
    package.MessageConfirmed = true;
    package.TitleConfirmed = false;

    while (package.TitleConfirmed == false) {

        start:
            CleanLine();
            system("clear");
            cout << "Create a Title for You Message:" << endl;
            getline(cin, package.title);

        if (package.title.empty() == true) {

            // Ensure Title exists
            cout << "Title Cannot be Empty" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto start;

        }
        else if (package.title.empty() == false) {

            package.title = TrimBlankSpace(package.title);
            ask:
                // Show title and ask for confirmation
                system("clear");
                cout << "This Is Your Title: \n\n" << "'" << package.title << "'" << endl;
                cout << "\nDo You Confirm That This Is Your Title ?\n\n";

                cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl;
                cout << setw(19) << "No" << setw(41) << "Press 2" << endl;

                cin >> Choice1b;

            if (cin.fail() || (Choice1b !=1 && Choice1b !=2)) {

                CleanLine();
                system("clear");
                cout << "Please select from the given options." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                goto ask;

             }
            else if (Choice1b == 1) {
    
                system("clear");
                cout << "This is Your Title: " << "'" << package.title << "'\n" << endl
                    << "This is Your Message: "  << "'" << package.message << "'\n" << endl;
                this_thread::sleep_for(chrono::seconds(5));
                system("clear");
                package.TitleConfirmed = true;
                break;

            }
            else if (Choice1b == 2) {

                goto start;

            }
        }
        else {

            goto start;

        }
    }

    return package;

}


int main() {
    
    string message;
    string title;
    bool MessageConfirmed = false;
    bool TitleConfirmed = false;
    int Choice1;


   while (true) {

    // Request Choice
    start:  
        ShowMainMenu();
        cin >> Choice1;

    if (cin.fail() || (Choice1 < 1 || Choice1 > 3)) {

        CleanLine();
        system("clear");
        cout << "Please select from the given options." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("clear");
        goto start;

    }

    else if (!cin.fail() && Choice1 == 1 || Choice1 == 2 || Choice1 == 3) {

        goto choice;

    }

    choice:
        switch (Choice1)
        {
        case 1:
            goto escape;
        case 2:
            goto escape;
        case 3:
            
            int QuitApp;

            quit_choice:
                system("clear");
                cout << "Are You Sure ?" << endl 
                    << "All Your Messages Will Be Erased\n" << endl
                    << setw(20) << "Yes" << setw(40) << "Press 1" << endl
                    << setw(19) << "No" << setw(41) << "Press 2" << endl;

                cin >> QuitApp;

            if (cin.fail() || (QuitApp != 1 && QuitApp != 2)) {

                CleanLine();
                system("clear");
                cout << "Please select from the given options." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                goto quit_choice;

            }
            else if (QuitApp == 1) {

                system("clear");
                cout << "Exiting Program, Goodbye." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                return 0;

            } 
            else if (QuitApp == 2) {

                system("clear");
                goto start;

            }
        
        default:
            goto start;
        }

    escape:
        break;
        system("clear");

}
    if (Choice1 == 1) {

        if (title.empty() == true) {

            init_package:
                Information InfoBundle = DoubleRequest();

                title = InfoBundle.title;
                message = InfoBundle.message;
                MessageConfirmed = InfoBundle.MessageConfirmed;
                TitleConfirmed = InfoBundle.TitleConfirmed;

                goto start;
        }
        else if (title.empty() == false) {

            int ToOverride;

            replace_m:
                system("clear");
                cout << "You Already Have a Message Titled " << "'" << title << "'" << " Saved.\n" << endl
                    << "Do You Wish to Override it ?\n" << endl
                    << setw(20) << "Yes" << setw(40) << "Press 1" << endl
                    << setw(19) << "No" << setw(41) << "Press 2" << endl;
                cin >> ToOverride;

            if (cin.fail() || (ToOverride != 1 && ToOverride != 2)) {

                CleanLine();
                system("clear");
                cout << "Please select from the given options." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                goto replace_m;

            }
            else if (ToOverride == 1) {

                goto init_package;

            }
            else if (ToOverride == 2) {

                goto start;

            }
            else {

                goto start;

            }


        }

    }
    else if (Choice1 == 2) {

        // ! Add Message Reading Functionality

        int Choice2;

        if (title.empty() == false) {
            ask_message:
                system("clear");
                cout << setw(50) << "Select The Message You Want to Read: \n\n";
                this_thread::sleep_for(chrono::seconds(1));
                cout << "1." << setw(20) << title << endl;

                cout << "\n\n\nDo You Wish to Read the Message Titled: " << setw(25) << "'" << title << "'" << " ?\n" << endl;
                cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl;
                cout << setw(19) << "No" << setw(41) << "Press 2" << endl;
                cin >> Choice2;

            if (cin.fail() || (Choice2 != 1 && Choice2 != 2)) {

                CleanLine();
                system("clear");
                cout << "Please select from the given options." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                goto ask_message;

            }
            else if (Choice2 == 1) {

                system("clear");
                cout << "Title: " << title << '\n' << '\n' 
                    << "Content:" << endl << endl << message << endl;
                this_thread::sleep_for(chrono::seconds(5));
                goto start;

            }
            else if (Choice2 == 2) {

                goto start;

            }
            else {

                goto ask_message;

            }

        }

        else if (title.empty() == true) {

            system("clear");
            cout << "There Are No Messages To Read" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            goto start;

        }

    }
    else {

        goto start;

    }
    
    return 0;

}
