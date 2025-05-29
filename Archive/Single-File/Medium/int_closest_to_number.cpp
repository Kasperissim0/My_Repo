#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {

  // Get Inputs
  const int COMPARE_AGAINST = 0; // Change According To Requirements
  int AmountOfData; // the number of NumbersToCompare to analyse
  int TotalRemoved1 = 0; // Will need later
  int TotalRemoved2 = 0; // Will need later
  int TempCompareMax = numeric_limits<int>::max();
  int TempCompareMin = numeric_limits<int>::min();
  
  cin >> AmountOfData; // Get Data
  cin.ignore(); // Get Data

  int NumbersToCompare[AmountOfData];
  bool ExactMatchFound = false;
  
  for (int i = 0; i < AmountOfData; i++) { // Get Data

    cin >> NumbersToCompare[i]; 
    cin.ignore();

  }

  // Recreate A Simple Sort
  for(int i = 0; i < AmountOfData; i++) {

    if(NumbersToCompare[i] == COMPARE_AGAINST) { // If You Match The Number, Print It Out

      cout << COMPARE_AGAINST << endl;
      ExactMatchFound = true;

    }

    else if (NumbersToCompare[i] < 0) { // For Negative Numbers

      if (NumbersToCompare[i] > TempCompareMin) {

        TempCompareMin = NumbersToCompare[i];

      }

    }

    else { // For Positive Numbers

      if (NumbersToCompare[i] < TempCompareMax) {

        TempCompareMax = NumbersToCompare[i];

      }

    }

  }

 if (!ExactMatchFound) {

  if (TempCompareMax == numeric_limits<int>::max() && TempCompareMin == numeric_limits<int>::min() && AmountOfData == 0) { // handle possible errors
    
    cout << "0" << endl;

  }

  else if (TempCompareMax == numeric_limits<int>::max() && TempCompareMin == numeric_limits<int>::min() && AmountOfData != 0) { // handle possible errors
    
    cout << "fuck" << endl;

  }

  else if (TempCompareMax == numeric_limits<int>::max()) { // handle possible errors
    
    cout << TempCompareMin << endl;

  }

  else if (TempCompareMin == numeric_limits<int>::min()) { // handle possible errors
    
    cout << TempCompareMax << endl;

  }

  else {

    TotalRemoved1 = TempCompareMax;
    TotalRemoved2 = -TempCompareMin; // Covert to a positive number

    if (TempCompareMax + TempCompareMin == 0) { // If the numbers are the same ( different sign ) positive wins

      cout << TempCompareMax << endl;
      return 0;

    }

    else if (TotalRemoved1 < TotalRemoved2) {

      cout << TotalRemoved1 << endl;

    }

    else {

      cout << -TotalRemoved2 << endl;

    }
  
  }

 }

  return 0;

}