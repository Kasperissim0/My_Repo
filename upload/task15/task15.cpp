#include <iostream>

using namespace std;

int main() {
    int kegCapacity, orderQuantity;

    cout << "Beer Keg Calculator (Expression Only)" << endl;
    cout << "Enter the capacity of one keg (in liters): ";
    cin >> kegCapacity;
    cout << "Enter the total order quantity (in liters): ";
    cin >> orderQuantity;

    if (kegCapacity <= 0 || orderQuantity < 0) {
        cout << "Keg capacity must be positive and order quantity cannot be negative." << endl;
        return 1;
    }

    // Calculate the number of kegs needed using an expression for ceiling division.
    // This formula works for positive integers a and b: (a + b - 1) / b
    // Here, a = orderQuantity, b = kegCapacity
    int num_kegs = (orderQuantity + kegCapacity - 1) / kegCapacity;

    cout << "For an order of " << orderQuantity << " liters with kegs of " << kegCapacity << "L, you will need " << num_kegs << " keg(s)." << endl;

    return 0;
}
