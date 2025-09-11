#include <iostream> // For output and input
#include <cmath>
#include <string>

using namespace std;

const string divider = "----------------------";

bool g(bool a, bool b, bool c, string functionType = "default"){
  bool g = (a || (b && !c)) && ((a && b) || (!b && c));
  cout << (a ? "| 1 |" : "| 0 |") 
       << " " << (b ? "1 |" : "0 |")
       << " " << (c ? "1 |" : "0 |");
  if (functionType == "default" || functionType == "complement") {
    cout << " " << (g ? "1 |" : "0 |");
  } if (functionType == "complement") {
    cout << " " << (g ? "0 |" : "1 |"); // switch
  } // if (functionType == "dual") {}

  cout << endl << divider << endl;
  return g;
}

int main () {
  const int AMOUNT_OF_ARGUMENTS = 3; // a - 1, b - 2, c - 3
  int possibleVariationAmount = pow(2, AMOUNT_OF_ARGUMENTS); // 8 = 2^3
  bool a, b, c;

  system("clear");
  cout << divider << endl << "| a | b | c | g | !g |" << endl << divider << endl;

  for (int i = 0; i < possibleVariationAmount; i++) {
    a = (i & 4) != 0; // check if the 3rd bit is flipped; if flipped - a is true, if not - false
    b = (i & 2) != 0; // check if the 2nd bit is flipped; if flipped - b istrue, if not - false
    c = (i & 1) != 0; // check if the 1st bit is flipped; if flipped - c is true, if not - false
    g (a, b, c, "complement");
  }
  return 0;

}