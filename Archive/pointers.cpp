#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <chrono> // For time manipulation + delaying actions
#include <thread> // For time manipulation + delaying actions

using namespace std;

int main () {

  int number;
  int *pointer = &number; // create a pointer ( called pointer ) that points to the memory adress of the number variable

  system("clear");
  cin >> number; // change the value of the number variable 

  *pointer = 2; // change the value the pointer is pointing to ( the value of the number variable )

  cout << number << endl // the value of the number variable
       << &number << endl // the memory adress of the number variable
       << pointer << endl // the content of the pointer ( that is the memory adress of the number variable )
       << &pointer << endl // the memory adress of the pointer
       << *pointer << endl; // the value the pointer is pointing to ( the value of the number variable )

  return 0;  
}

