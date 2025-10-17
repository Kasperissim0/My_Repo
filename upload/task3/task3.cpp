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

    double angle_rad = angle_deg * M_PI / 180.0;
    double area = (radius * radius / 2.0) * (angle_rad - sin(angle_rad));

    cout << "The area of the circular segment is: " << area << endl;

    return 0;
}