#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  double x1, y1, z1, x2, y2, z2;

  cout << "Enter the coordinates of the first point (x1 y1 z1): ";
  cin >> x1 >> y1 >> z1;
  cout << "Enter the coordinates of the second point (x2 y2 z2): ";
  cin >> x2 >> y2 >> z2;

  double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));

  cout << fixed << setprecision(4);
  cout << "The distance between the two points is: " << distance << endl;

  return 0;
}
