#include <iostream>

using namespace std;

int main() {
    int n1, n2, n3;
    cout << "Enter three integer values: " << endl;
    cin >> n1 >> n2 >> n3;

    int d1 = n1 % 10;
    int d2 = n2 % 10;
    int d3 = n3 % 10;

    int r1 = n1 / 10;
    int r2 = n2 / 10;
    int r3 = n3 / 10;

    cout << "Output: " << d3 << d2 << d1;
    cout << r1 << r2 << r3 << endl;

    return 0;
}