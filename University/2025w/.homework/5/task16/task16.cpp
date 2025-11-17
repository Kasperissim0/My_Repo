#include <iostream>
#include <string>

using namespace std;

void displayPermutations(string input, size_t index = 0) {
  if (index >= input.length()) cout << input << " ";
  else {
    for (size_t i = index; i < input.length(); ++i) {
      swap(input.at(index), input.at(i));
      displayPermutations(input, index + 1);
      swap(input.at(index), input.at(i));
    }
  }
}

int main() {
  char goAgain; string userInput = "";
  do {
    cout << "Insert String: ";
    cin >> userInput;
    cout << "Permutations: ";
    displayPermutations(userInput);
  } while (cout << endl << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');

  return 0;
}