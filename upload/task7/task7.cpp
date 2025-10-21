#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const double eurToUsdRate = 1.08;
    int choice;
    double amount;

    cout << "Currency Converter" << endl;
    cout << "1. Euros to Dollars" << endl;
    cout << "2. Dollars to Euros" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    cout << fixed << setprecision(2);

    if (choice == 1) {
        cout << "Enter amount in Euros: ";
        cin >> amount;
        double dollars = amount * eurToUsdRate;
        cout << amount << " EUR is equal to " << dollars << " USD." << endl;
    } else if (choice == 2) {
        cout << "Enter amount in Dollars: ";
        cin >> amount;
        double euros = amount / eurToUsdRate;
        cout << amount << " USD is equal to " << euros << " EUR." << endl;
    } else {
        cout << "Invalid choice. Please run the program again and select 1 or 2." << endl;
    }

    return 0;
}
