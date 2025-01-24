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

  system("clear");

  int Choice1;
  int Choice1a;
  string sentence;

  while (true) {
        cout << "How Can I Help You ?\n" << endl;

        cout << setw(20) << "Leave A Message" << setw(40) << "Press 1" << endl;
        cout << setw(19) << "Read A Message" << setw(41) << "Press 2" << endl;
        cout << setw(9) << "Exit" << setw(51) << "Press 3" << endl;
        cin >> Choice1;
        cin.ignore();
        system("clear");

        switch (Choice1) {
            case 1:
                while (true) {
                    cout << "Insert Your Message Here: " << endl;
                    getline(cin, sentence);
                    system("clear");

                    cout << "This Is Your Message: \n\n" << "'" << sentence << "'" << endl;
                    cout << "\nDo You Confirm That This Is Your Message ?\n\n";

                      this_thread::sleep_for(chrono::seconds(2));
                      cout << setw(20) << "Yes" << setw(40) << "Press 1" << endl;
                      cout << setw(19) << "No" << setw(41) << "Press 2" << endl;
                      cin >> Choice1a;
                      cin.ignore();
                      system("clear");

                    switch (Choice1a) {
                        case 1:
                            sentence = ReverseSentence(sentence);
                            cout << "Your Message Has Been Saved" << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("clear");
                            break; // Add break here to prevent fall-through
                        case 2: 
                            system("clear");
                            break; // This will go back to the start of the while loop
                        default:
                            cout << "Invalid option selected. Please try again." << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("clear");
                            break;
                    }
                    // If the user confirmed the message, break out of the inner loop
                    if (Choice1a == 1) {
                        break; // Exit the message entry loop
                    }
                }
                break;

            case 2:
                cout << "Under Development" << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("clear");
                break;

            case 3: // Exit option
                cout << "Exiting the program. Goodbye!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                return 0; // Exit the program

            default:
                cout << "Invalid option selected. Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("clear");
                break;
         }
    }

    return 0; // This line will never be reached due to the infinite loop

}