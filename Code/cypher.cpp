#include <iostream>
#include <string>
#include <iomanip> // Include this for setw()
#include <cstdlib> // Include this for system()
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

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
            system("clear");
            goto start;

        }
        else if (message.length() > 0) {

            ask:
                // Show message and ask for confirmation
                system("clear");
                cout << "This Is Your Message: \n\n" << "'" << message << "'" << endl;
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
string RequestTitle () {

    string title; 

    // here


    return title;

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

            system("clear");
            cout << "Exiting Program, Goodbye." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("clear");
            return 0;
        
        default:
            goto start;
        }

    escape:
        break;
        system("clear");

}
    if (Choice1 == 1) {

        message = RequestMessage();
        MessageConfirmed = true;
        TitleConfirmed = false;
        title = RequestTitle();

        goto start;

    }
    else if (Choice1 == 2) {

        // here

    }
    else {

        goto start;

    }
    // ! More Code Here
    




    /*while (true) {
        // Clear screen and display main menu
        system("clear");

        cout << "How Can I Help You ?\n" << endl;
        cout << setw(20) << "Leave A Message" << setw(40) << "Press 1" << endl;
        cout << setw(19) << "Read A Message" << setw(41) << "Press 2" << endl;
        cout << setw(9) << "Exit" << setw(51) << "Press 3" << endl;

        // Get user's menu choice
        cin >> Choice1;
        cin.ignore(); // Clear input buffer
        system("clear");

        switch (Choice1) {
            case 1: {
                // Reset confirmation flags at the start of message creation
                MessageConfirmed = false;
                TitleConfirmed = false;

                // Message input and confirmation loop
                while (!MessageConfirmed) {
                    // Prompt for message
                    cout << "Insert Your Message Here: ";

                    // Get the entire line of input
                    getline(cin, sentence);

                    // Validate message is not empty
                    if (sentence.empty()) {
                        cout << "Message cannot be empty. Press Enter to continue." << endl;
                        cin.ignore();
                        system("clear");
                        continue; // Go back to the start of the loop
                    }

                    system("clear");

                    // Show message and ask for confirmation
                    cout << "This Is Your Message: \n\n" << "'" << sentence << "'" << endl;
                    cout << "\nDo You Confirm That This Is Your Message ?\n\n";

                    cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl;
                    cout << setw(19) << "No" << setw(41) << "Press 2" << endl;

                    // Get confirmation choice
                    cin >> Choice1a;
                    cin.ignore();
                    system("clear");

                    switch (Choice1a) {
                        case 1: {
                            // Encrypt message
                            sentence = ReverseSentence(sentence);
                            cout << "Your Message Has Been Saved" << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("clear");

                            // Title input loop
                            while (true) {
                                cout << "Create a Name For Your Message: \n";
                                getline(cin, Name1);

                                // Validate title is not empty
                                if (!Name1.empty()) {
                                    TitleConfirmed = true;
                                    break;
                                }

                                cout << "Title cannot be empty. Try again." << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                system("clear");
                            }

                            MessageConfirmed = true;
                            break;
                        }
                        case 2:
                            // Clear message if user chooses to cancel
                            sentence.clear();
                            system("clear");
                            break;

                        default:
                            // Handle invalid input
                            cout << "Invalid option selected. Please try again." << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            break;
                    }
                }
                break;
            }
            case 2:
                cout << "Under Development" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                break;

            case 3:
                // Exit the program
                cout << "Exiting the program. Goodbye!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                return 0;

            default:
                cout << "Invalid option selected. Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                break;
        }
    }
    */
    return 0;
}
