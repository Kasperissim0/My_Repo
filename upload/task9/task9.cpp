#include <iostream>

using namespace std;

int main() {
    double hydrogen_mass;
    cout << "Enter the mass of hydrogen to be burned (in grams): ";
    cin >> hydrogen_mass;

    if (hydrogen_mass < 0) {
        cout << "Mass cannot be negative." << endl;
        return 1;
    }

    double oxygen_mass = 8.0 * hydrogen_mass;
    double water_volume = 9.0 * hydrogen_mass; // in ml, assuming density of 1g/ml

    cout << "For the reaction, you need " << oxygen_mass << " grams of oxygen." << endl;
    cout << "This will produce " << water_volume << " milliliters of water." << endl;

    return 0;
}