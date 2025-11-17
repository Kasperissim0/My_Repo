#include <iostream>
#include <string>
using namespace std;

unsigned originalValue;

void displayBreakdown(unsigned remainingSum, unsigned largestSummand, string currentSummandChain = "") {
  if (remainingSum == 0) { cout << originalValue << " = " << currentSummandChain << endl; return; }
  for (unsigned i = largestSummand; i >= 1; --i) {
    if (i <= remainingSum) {
      string newSummandChain = (currentSummandChain.empty() ? to_string(i) : (currentSummandChain + " + " + to_string(i)));
      displayBreakdown(remainingSum - i, i, newSummandChain);
    }
  }
}

int main() {
  char goAgain;
  do {
    cout << "Insert A Positive Integer Larger Than 1: ";
    cin >> originalValue;
    if (cin.fail() || originalValue <= 1) continue;
    displayBreakdown(originalValue, originalValue);
  } while (cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');

  return 0;
}

// taken from https://gemini.google.com/app/8463386f32f5f5ed?hl=en-GB