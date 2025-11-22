#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const string divider = "-------------------------";
const int AMOUNT_OF_ARGUMENTS = 3; // a - 1, b - 2, c - 3a

bool fullFunction (bool a, bool b, bool c) {
  return (!(!a && c) || (a && !c && a || !(c && b)) && c && b || a); // ⬅️ put the expression you want to check here
}
bool simplifiedFunction (bool a, bool b, bool c) {
  return (a || !c); // ⬅️ put the expression you want to check here
}

int main () {
  int possibleVariationAmount = static_cast<int> (pow (2, AMOUNT_OF_ARGUMENTS)); // 8 = 2^3
  bool a, b, c, simplificationMistake = false;
  vector<bool> fullFunctionResult, simplifiedFunctionResult;

  system ("clear");
  cout << divider << endl
       << "| a | b | c | f_1 | f_2 |" << endl
       << divider << endl;

  for (int i = 0; i < possibleVariationAmount; i++) {
    a = (i & 4) != 0; // check if the 3rd bit is flipped; if flipped - a is true, if not - false
    b = (i & 2) != 0; // check if the 2nd bit is flipped; if flipped - b istrue, if not - false
    c = (i & 1) != 0; // check if the 1st bit is flipped; if flipped - c is true, if not - false
    fullFunctionResult.push_back(fullFunction(a, b, c));
    simplifiedFunctionResult.push_back(simplifiedFunction(a, b, c));
    cout << (a ? "| 1 |" : "| 0 |")
         << " " << (b ? "1 |" : "0 |")
         << " " << (c ? "1 |" : "0 |")
         << " " << (fullFunctionResult[i] ? " 1  |" : " 0  |")
         << " " << (simplifiedFunctionResult[i] ? " 1  |" : " 0  |")
         << endl
         << divider << endl;
    if (fullFunctionResult[i] != simplifiedFunctionResult[i]) { simplificationMistake = true; }
  }
  if (!simplificationMistake) {
    cout << endl
         << "CORRECT\n"
         << endl;
  } else {
    cout << endl
         << "INCORRECT\n"
         << endl;
  }
  return 0;
}