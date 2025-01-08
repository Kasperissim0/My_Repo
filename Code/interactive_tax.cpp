#include <iostream>
using namespace std;

int main() {
   const double income = 95000;
   double TempIncome= 95000;

   double tax1 = TempIncome * 0.04;
   TempIncome = TempIncome - tax1;
   double tax2 = TempIncome * 0.02;
   TempIncome = TempIncome - tax2;
   double TotalTax = tax1 + tax2;

   double TotalPercent = (TotalTax / income) * 100;
   int TotalSum = tax1 + tax2;


   cout << "Your Income is: " << income << " Dollars" <<endl;
   cout << "Your State Tax is 4% ( " << tax1 << " )" <<endl;
   cout << "Your Couty Tax is 2% ( " << tax2 << " )" <<endl;
   cout << "\nYour Total Tax is " << TotalPercent << "%" << " Of Your Income." <<endl;

   cout << "\nTherefore You Will Have To Pay " << TotalSum << " Dollars in Taxes." << endl;
   TempIncome = income - TotalSum;
   cout << "Afterwards You Will Be Left With " << TempIncome << " Dollars.";

   return 0;
}