#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

int main() {
    double radius, angle_deg;
    cout << "Enter the radius of the circle: ";
    cin >> radius;
    cout << "Enter the angle in degrees: ";
    cin >> angle_deg;

    double area = (angle_deg / 360.0) * M_PI * radius * radius;

    cout << "The area of the circular sector is: " << area << endl;

    return 0;
}