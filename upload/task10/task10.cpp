#include <iostream>

using namespace std;

int main() {
    int kegCapacity, orderQuantity;

    cout << "Beer Keg Calculator" << endl;
    cout << "Enter the capacity of one keg (in liters): ";
    cin >> kegCapacity;
    cout << "Enter the total order quantity (in liters): ";
    cin >> orderQuantity;

    if (kegCapacity <= 0 || orderQuantity < 0) {
        cout << "Keg capacity must be positive and order quantity cannot be negative." << endl;
        return 1;
    }

    if (orderQuantity == 0) {
        cout << "You need 0 kegs for an order of 0 liters." << endl;
        return 0;
    }

    int numKegs = orderQuantity / kegCapacity;

    // If there is any remainder, one more keg is needed.
    if (orderQuantity % kegCapacity != 0) {
        numKegs++;
    }

    cout << "For an order of " << orderQuantity << " liters with kegs of " << kegCapacity << "L, you will need " << numKegs << " keg(s)." << endl;

    return 0;
}
