#include <iostream>
#include <string>
#include <algorithm> // For std::reverse

using namespace std;

string reverseString(string text) {
    reverse(text.begin(), text.end());
    return text;
}

int main() {
    string inputText;
    cout << "Enter a string to reverse: ";
    getline(cin, inputText);
    string reversedString = reverseString(inputText);
    cout << "Reversed string: " << reversedString << endl;
    return 0;
}
