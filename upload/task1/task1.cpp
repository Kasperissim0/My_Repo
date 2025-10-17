#include <iostream>

using namespace std;

int main() {
    double length, width;
    cout << "Enter the length of the rectangle: ";
    cin >> length;
    cout << "Enter the width of the rectangle: ";
    cin >> width;

    double perimeter = 2 * (length + width);
    double area = length * width;

    cout << "Perimeter: " << perimeter << endl;
    cout << "Area: " << area << endl;

    return 0;
}