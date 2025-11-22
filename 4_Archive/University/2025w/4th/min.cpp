#include<iostream>
#include<limits>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

int main() {
	int currentInput = numeric_limits<int>::max(), smallestInput = currentInput;
	bool userInput = false;
	
	clearScreen();
	cout << "Insert A Series Of Integers: " << endl;
	while (cin >> currentInput) {
		userInput = true;
		if (currentInput <= smallestInput) smallestInput = currentInput;
	}
	
	cout << endl << endl;
	if (!userInput) cout << "No Numbers Entered";
	else cout << "The Smallest Number from The Given Array Is: " << smallestInput;
	cout << endl;
	
	return 0;
}
