#include <iostream>
#include <string>
#include <iomanip> // Include this for setw()
#include <cstdlib> // Include this for system()
#include <thread>
#include <chrono>

using namespace std;

// Define The Reverse Sentence Function (for cyphering the message)
string ReverseSentence(const string& sentence) {

  char ReversedSentenceCharachters[sentence.length() + 1]; // +1 for null terminator

    for (int i = sentence.length(); i > 0; i--) { 
      // Reverse the string into the Array

      ReversedSentenceCharachters[i - 1] = sentence[sentence.length() - i];
      
    }

    ReversedSentenceCharachters[sentence.length()] = '\0'; // Null-terminate the string


    return string(ReversedSentenceCharachters); // Return the reversed string

}


int main() {
    // Variables to manage program state and user inputs
    bool MessageConfirmed = false;
    bool TitleConfirmed = false;
    int Choice1;
    int Choice1a;
    string sentence;
    string Name1;

    while (true) {
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
                            cout << "Press Enter To Continue" << endl; 
                            cin.ignore();
                            cin.get();

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

    return 0;
}
