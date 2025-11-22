#include <iostream>
#include <string>

using namespace std;

int findChar(const string& text, char searchChar) {
    bool inQuotes = false;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '"') {
            inQuotes = !inQuotes;
        }
        if (!inQuotes && text[i] == searchChar) {
            return i;
        }
    }
    return -1; // Not found
}

int main() {
    string text = "He said \"I have no hint.\" and headed south";
    char searchChar = 'h';
    int position = findChar(text, searchChar);
    if (position != -1) {
        cout << "Character '" << searchChar << "' found at index: " << position << endl;
    } else {
        cout << "Character '" << searchChar << "' not found." << endl;
    }
    
    searchChar = 'a';
    position = findChar(text, searchChar);
    if (position != -1) {
        cout << "Character '" << searchChar << "' found at index: " << position << endl;
    } else {
        cout << "Character '" << searchChar << "' not found." << endl;
    }

    return 0;
}
