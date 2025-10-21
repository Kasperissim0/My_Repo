#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int mWorkers, xPieces, nWorkers;

  cout << "Enter the number of workers (m): ";
  cin >> mWorkers;
  cout << "Enter the number of pieces they produce in an hour (x): ";
  cin >> xPieces;
  cout << "Enter the number of workers for the question (n): ";
  cin >> nWorkers;

  if (mWorkers <= 0) {
      cout << "Number of workers (m) must be positive." << endl;
      return 1;
  }

  cout << "\nOriginal (potentially incorrect) calculation for 10, 5, 2: " << 5 / 10 * 2 << endl;

  cout << "\n--- Two Improved Methods --- " << endl;

  // Method 1: Change the order of operations to perform multiplication first.
  // This avoids the integer division truncation that happens when x < m.
  double result1 = (double)xPieces * nWorkers / mWorkers;
  cout << "Method 1 (reordering operations): " << result1 << " pieces." << endl;

  // Method 2: Force floating-point division by casting one of the operands.
  // This ensures the division is precise.
  double result2 = (double)xPieces / mWorkers * nWorkers;
  cout << "Method 2 (using floating-point division): " << result2 << " pieces." << endl;

  return 0;
}
