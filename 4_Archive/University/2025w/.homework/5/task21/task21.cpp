#include <iostream>

using namespace std;

// unsigned callAmount = 0;

unsigned ackerman(unsigned m, unsigned n) {
  // clog << "Call #" << ++callAmount << endl;
  if (m == 0) return (n + 1);
  else if (m > 0 && n == 0) return ackerman((m - 1), 1);
  else if (m > 0 && n > 0) return ackerman((m - 1), ackerman(m, (n - 1)));
  else cerr << "ERROR" << endl; return 1;
}

int main() {
  char goAgain; unsigned m, n;
  do {
    cout << "Insert 2 Natural Numbers: ";
    cin >> m >> n;
    if (m <= 0 || n <= 0) cout << "INVALID INPUT: Natural Numbers Only" << endl;
    else cout << "The Value Of The Ackerman Function For" << " A(" << m << ", " << n << ") Is: " << ackerman(m, n);
  } while (cout << endl << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');

  return 0;
}