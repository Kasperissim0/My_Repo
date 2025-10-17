#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const double distance_ly = 4.37; // Distance to Alpha Centauri in light-years
    double x;

    cout << "Enter the spaceship's speed as a percentage of the speed of light (0-100): ";
    cin >> x;

    if (x <= 0 || x >= 100) {
        cout << "Percentage must be between 0 and 100 (exclusive)." << endl;
        return 1;
    }

    double speed_fraction = x / 100.0;
    double time_earth = distance_ly / speed_fraction;
    double time_pilot = time_earth * sqrt(1 - (speed_fraction * speed_fraction));

    cout << "Time passed on Earth: " << time_earth << " years." << endl;
    cout << "Time passed for the pilot: " << time_pilot << " years." << endl;

    return 0;
}