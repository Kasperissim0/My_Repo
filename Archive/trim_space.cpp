#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main () {

  string input; // Test String

  getline(cin, input);

  auto StringStart = find_if_not(input.begin(), input.end(), ::isspace); // Find First Non-Space Charachter
  auto StringEnd = find_if_not(input.rbegin(), input.rend(), ::isspace).base(); // Find Last Non-Space Charachter

  string TrimmedString = string(StringStart, StringEnd); // Create a String Starting Without the Spaces
  cout << endl << TrimmedString << endl;
 
  return 0;

}