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
  int numbers[3];
  for (int i = 0; int < 3; i++) {
    cout << "Insert Number " << i << " :";
    cin >> numbers[i];
  }
  cout <<  << endl;
  return 0;
}