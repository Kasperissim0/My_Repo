#include<iostream>
#include<cmath>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

int main(){
  double y {0}; int count {0};
  
  clearScreen();
  while (count < 10) {
    y += 0.1;
    count++;
  }
  y = ceil(y); // necessary to avoid rounding mistakes
  cout << y << " ist ";
  if (y != 1) cout << "nicht ";
    cout << "gleich 1" << endl;

  return 0;
}
