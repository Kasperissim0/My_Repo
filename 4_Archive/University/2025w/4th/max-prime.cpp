#include<iostream>
#include<limits>
#include<cmath>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

bool isPrime(int& number) { 
	int upperBound = ceil(sqrt(number)); // optional optimization
	
	if (number % 2 == 0) return false;
	for (int i = 3; i <= upperBound; i += 2) {
		if (number == 2) return true;
		else if (number % i == 0) return false;
	}
	return (number <= 1 ? false : true);
}

int main() {
	int currentInput = numeric_limits<int>::min(), largestInput = currentInput;
	bool userInput = false;
	
	clearScreen();
	cout << "Insert A Series Of Integers: " << endl;
	while (cin >> currentInput) {
		userInput = true;
		if (currentInput >= largestInput && isPrime(currentInput)) 
			largestInput = currentInput;
	}
	
	cout << endl << endl;
	if (!userInput) cout << "No Numbers Entered";
	else if (userInput && largestInput == numeric_limits<int>::min() ) { 
		cout << "No Prime Numbers Entered";
	}
	else cout << "The Largest Prime From The Given Array Is: " << largestInput;
	cout << endl;
	
	return 0;
}
