#include <iostream>
#include <iomanip>

using namespace std;

void clearScreen() {
  #ifdef __WIN32
      system("cls");
    #else
      system("clear");
  #endif
}

int main () {
  static int array[5];
  double mean; // for a more accurate answer

  clearScreen();
  for (int i = 0; i < 5; i++) {
    cout << "Insert Number " << (i + 1) << ": ";
    cin >> array[i];
    mean += array[i];
  }
  cout << "The Mean Value Of The Array {"; 
  for (int i = 0; i < 5; i++) { cout << array[i] << ((i == 5 - 1) ? "" : ", "); }
  cout << "} Is: " << (mean / 5) << endl;
  return 0;
}