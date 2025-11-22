#include<iostream>
// #include<string>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

// extern int abc;
// extern ostream std::cout;

int main() {
  clearScreen();
  // cout << abc;

  int i, j, x = 0;
  string s {""};
  
  cout << "Geben Sie eine Zahl ein: ";
  cin >> i;
  cout << "Geben sie eine Zahl ein: ";
  cin >> j;

  while (j != 0) {
    if (j%2 == 1)  // if j is odd
      x = x+i;
    i *= 2;
    j /= 2;
  }
  while (x != 0) {
    if (x%2 != 0) 
      s = '*' + s; // if j is odd
    else 
      s = '.' + s; // if j is even
    x /= 2; // should remain even/odd after loop
  }
  cout << s << '\n'; 

  return 0;
}
