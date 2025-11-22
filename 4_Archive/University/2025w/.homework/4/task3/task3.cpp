#include <iostream>
#include <string>
#include <map>

using namespace std;

int countOccurrences(const string& text, char character) {
    int count = 0;
    for (char c : text) {
        if (c == character) {
            count++;
        }
    }
    return count;
}

int main() {
    string inputText;
    cout << "Input a string (end with Ctrl-D):" << endl;
    while (cout << "Input: ", getline(cin, inputText)) {
        if (inputText.empty()) continue;
        
        map<char, int> frequencies;
        for (char c : inputText) {
            frequencies[c]++;
        }

        cout << "Output: ";
        bool first = true;
        for (const auto& p : frequencies) {
            if (!first) {
                cout << " ";
            }
            cout << p.first << "(" << p.second << ")";
            first = false;
        }
        cout << endl;
    }
    cout << "\nprogram end" << endl;
    return 0;
}
