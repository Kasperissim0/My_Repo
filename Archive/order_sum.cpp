#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>


using namespace std;

int main () {

  vector<double> AllPrices;
  int AmountOfItems;
  double TempPrice;
  double TotalPrice = 0.0;

  while (true) {

    system("clear");

    cout << "How Many Items Did You Buy ?" << endl;
    cin >> AmountOfItems;

    system("clear");

    if (AmountOfItems > 0 && !cin.fail()) {

      for (int i = 0; i < AmountOfItems; i++) {

        cout << "How Much Was Item " << i + 1 << " Worth ? ( in Euros )" << endl;
        cin >> TempPrice;
        AllPrices.push_back(TempPrice);

        system("clear");

      }

    }

    break;

  }

  for (auto cost: AllPrices) {

    TotalPrice += cost;

  }

  cout << "Your Total Is: " << TotalPrice << ((TotalPrice == 1) ? " Euro" : " Euros\n") << endl;

  return 0;

}