#include <iostream> // For output and input
#include <utility> // Required for std::swap

using namespace std;

int findGCF(int& firstNumber, int& secondNumber) {
    // Ensure firstNumber is always the larger number
    if (firstNumber < secondNumber) {
        swap(firstNumber, secondNumber); // Use swap to simplify the logic
    }

    // system("clear");

    // Subtract the smaller number from the larger number
    firstNumber -= secondNumber;
    cout << "\n" << (firstNumber + secondNumber) << " - " << secondNumber << " = " << firstNumber; // Show the operation

    // Check if the numbers are equal
    if ((firstNumber == secondNumber) && firstNumber != 0) {
        return firstNumber; // can return any of the 2
    } else if (firstNumber == 0) {
        return secondNumber; // If firstNumber becomes 0, return secondNumber
    } else {
        return findGCF(firstNumber, secondNumber); // Recursive call
    }
}

int main() {
    int firstNumber;
    int secondNumber;
    int greatestCommonFactor;

    system("clear");

    cout << "Select 2 Numbers To Find The Greatest Common Factor Of" << endl;
    cout << "\nNumber 1 - ";
    cin >> firstNumber;
    cout << "Number 2 - ";
    cin >> secondNumber;

    // Call the function to find the GCF
    greatestCommonFactor = findGCF(firstNumber, secondNumber);
    cout << "\n\nThe GCF Of " << firstNumber << " and " << secondNumber << " Is - " << greatestCommonFactor << endl;

    return 0;
}