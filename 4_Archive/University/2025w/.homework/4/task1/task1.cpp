#include <iostream>
#include <string>

using namespace std;

string removeCharacter(string text, char character) {
    string result = "";
    for (char c : text) {
        if (c != character) {
            result += c;
        }
    }
    return result;
}

int main() {
    string inputText; char charToRemove;
    cout << "Input string: ";
    cin >> inputText;

    cout << "Enter characters to remove (end with Ctrl-D):" << endl;
    while (cout << "Input: ", cin >> charToRemove) {
        inputText = removeCharacter(inputText, charToRemove);
        cout << "Output: " << inputText << endl;
    }

    return 0;
}

