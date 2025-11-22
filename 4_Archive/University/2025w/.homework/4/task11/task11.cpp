#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string scrambleString(string text) {
    string oddChars = "";
    string evenChars = "";
    for (int i = 0; i < text.length(); ++i) {
        if (i % 2 != 0) {
            oddChars += text[i];
        } else {
            evenChars += text[i];
        }
    }
    reverse(evenChars.begin(), evenChars.end());
    return oddChars + evenChars;
}

int main() {
    string inputText;
    cout << "Enter a string to scramble: ";
    cin >> inputText;
    cout << "Scrambled string: " << scrambleString(inputText) << endl;
    return 0;
}
