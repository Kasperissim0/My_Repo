#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

string convertNumber(string& originalNumber, short& originalBase, const short& newBase) {
  string convertedString = ""; long long int passedNumber; bool numberNegative = false;

  if (originalBase > 30 || originalBase < 2 || newBase > 30 || newBase < 2) throw runtime_error("Invalid Number Base Entered");
  try { 
    passedNumber = stoll(originalNumber, nullptr, originalBase);
    if (passedNumber == 0) return "0";
    if (passedNumber < 0) { passedNumber = -passedNumber; numberNegative = true; }
  }
  catch (const invalid_argument& e) { throw runtime_error("The Number You Entered Is Not A Valid Base " + to_string(originalBase) + " Number"); }
  catch (const out_of_range& e) { throw runtime_error("The Number You Entered Is Too Large"); }
  catch (...) { throw runtime_error("Caught Unspecified Error"); }

  while (passedNumber) { // Implicitly Converted To while(passedNumber != 0)
    char tempStorage = ' '; short remainder = passedNumber % newBase;
    if (remainder < 10) tempStorage = (char)('0' + remainder);
    else tempStorage = (char)('A' + (remainder - 10));
    convertedString.insert(convertedString.begin(), tempStorage);
    passedNumber /= newBase;
  }
  if (numberNegative) convertedString.insert(convertedString.begin(), '-');
  return convertedString;
}

int main() {
  string number; short originalBase, newBase;
  
  do {
    system("clear");
    cout << "Insert:\n --- \n 1. Number\n 2. Current Base\n 3. New Base\n---" << endl;
    cin >> number >> originalBase >> newBase;
    try {
      system("clear");
      cout << "The Integer " << number << " (in base " << originalBase << ")" << endl
           << "Is Equal To: " << convertNumber(number, originalBase, newBase) << " (in base " << newBase << ")" << endl;
    }
    catch (const runtime_error& e) { system("clear"); cerr << e.what() << endl; }
    cout << endl << "Go Again? (y/n): ";
  } while (cin >> number && number == "y");
  return 0;
}