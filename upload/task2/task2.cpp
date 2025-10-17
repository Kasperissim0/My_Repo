#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double item_price, quantity, vat_rate;
    cout << "Enter the item price: ";
    cin >> item_price;
    cout << "Enter the quantity: ";
    cin >> quantity;
    cout << "Enter the VAT rate (%): ";
    cin >> vat_rate;

    double total_price = (item_price * quantity) * (1 + vat_rate / 100.0);

    cout << fixed << setprecision(2);
    cout << "Total price: " << total_price << endl;

    return 0;
}