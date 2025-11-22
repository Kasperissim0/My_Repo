#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string caesarEncode(string text, int shift) {
    string encodedText = "";
    for (char character : text) {
        if (isalpha(character)) {
            char base = islower(character) ? 'a' : 'A';
            encodedText += (character - base + shift) % 26 + base;
        } else {
            encodedText += character;
        }
    }
    return encodedText;
}

int main() {
    string inputText;
    int shift;

    cout << "Enter text and a shift value (end with Ctrl-D):" << endl;
    while (cout << "Input: ", cin >> inputText >> shift) {
        string encoded = caesarEncode(inputText, shift);
        cout << "Output: " << encoded << endl;
    }

    cout << "\nprogram end" << endl;
    return 0;
}
