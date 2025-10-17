#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double EUR_TO_USD = 1.08, amount;
    int choice;
    
    cout << "Currency Converter" << endl;
    cout << "1. Euros to Dollars" << endl;
    cout << "2. Dollars to Euros" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    cout << fixed << setprecision(2);

    if (choice == 1) {
        cout << "Enter amount in Euros: ";
        cin >> amount;
        cout << amount << " EUR is " << (amount * EUR_TO_USD) << " USD." << endl;
    } else if (choice == 2) {
        cout << "Enter amount in Dollars: ";
        cin >> amount;
        cout << amount << " USD is " << (amount / EUR_TO_USD) << " EUR." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
