#include<iostream>
#include<cmath>
#include<string>

using namespace std;

int main() {

  int radius;
  double result;

  cout << "What is the Radius of the Circle? \n";
  cin >> radius;

  result =  pow(radius, 2) * 3.14;

  cout << "\n" << result << "cm\n";

}