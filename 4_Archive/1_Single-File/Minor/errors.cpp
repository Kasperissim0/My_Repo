#include <iostream> // for output and input
#include <stdexcept>
#include <cassert>
#include <limits>

using namespace std;

void clearBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getVariable (int& input) {
  int check;
  string error = "ERROR: Invalid Input\n\n";
  cout << "Insert An Integer Larger Than 1: ";
  cin >> input;
  check = static_cast<int>(input); // error otherwise for some reason (does not consider input as an int???)
  if (cin.fail()) { clearBuffer(); error +=  "Please enter an integer."; throw runtime_error(error); }
  else if (check <= 1) { error += "Integer must be greater than 1."; throw runtime_error(error); }
} 

int main () {
  int var;
  while (true) {
    system("clear");
    try { getVariable(var); break; }
    catch (const runtime_error& e) {
      cerr << e.what() << endl;
      cout << "Press enter to try again...";
      clearBuffer();
      cin.get();
    }
  }
  cout << "You entered: " << var << endl;

  return 0;
}