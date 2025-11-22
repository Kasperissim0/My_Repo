#include<iostream>
#include<string>
using namespace std;

int main() {

  double FH;
  double CS;

  cout << "What is the Temperature?\n" << "(in Celsius)" << endl;
  cin >> CS;
  FH = CS * 1.8 + 32;

  cout << " Your Temperature in Fahrenheit is " << FH << "\n";



}