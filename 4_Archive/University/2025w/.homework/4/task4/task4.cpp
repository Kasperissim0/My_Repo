#include <iostream>
#include <string>

using namespace std;

string sortAroundFirst(string text) {
    if (text.empty()) {
        return "";
    }

    char pivot = text[0];
    string smaller = "";
    string greaterOrEqual = "";

    for (char c : text) {
        if (c < pivot) {
            smaller += c;
        } else { // Includes the pivot itself and characters greater than it
            greaterOrEqual += c;
        }
    }
    return smaller + greaterOrEqual;
}

int main() {
    string inputText;
    cout << "Enter a string (lowercase only): ";
    cin >> inputText;
    string sortedString = sortAroundFirst(inputText);
    cout << "Sorted string: " << sortedString << endl;
    return 0;
}
