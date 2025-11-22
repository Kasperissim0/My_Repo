#include <iostream>
#include <string>

using namespace std;

bool checkIfRealNumber(string test) {
  try { stod(test); return true; }
  catch (...) { return false; }
}
void printNumber(char number) { 
  switch (number) {
    case '0': cout << "zero"; break;
    case '1': cout << "one"; break;
    case '2': cout << "two"; break;
    case '3': cout << "three"; break;
    case '4': cout << "four"; break;
    case '5': cout << "five"; break;
    case '6': cout << "six"; break;
    case '7': cout << "seven"; break;
    case '8': cout << "eight"; break;
    case '9': cout << "nine"; break;
    default: throw runtime_error("Invalid Integer In Printing Function"); break;
  }
}

int main () {
  string userInput = "";

  do {
    system("clear");
    cout << "Insert A Real Number: ";
    cin >> userInput;
    system("clear");
  } while(!checkIfRealNumber(userInput));

  cout << userInput << " Is Equivalent To:" << endl;
  for (size_t i = 0; i < userInput.length(); i++) {
    if (userInput.at(i) == '.') cout << " point ";
    else if (userInput.at(i) == ',') cout << " comma ";
    else {
     printNumber(userInput.at(i));
     if (i != (userInput.length() - 1) && userInput.at(i + 1) != '.' && userInput.at(i + 1) != ',') cout << "-"; // between words except last
    }
  }
  cout << endl;
  return 0;
}