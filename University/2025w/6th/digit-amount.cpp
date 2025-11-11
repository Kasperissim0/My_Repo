#include<iostream>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned digitAmount(int n) { return ((n < 10) ? 1 : (1 + digitAmount(n/10))); }

int main() {
	char goAgain; int n; bool negative = false;
	
	do {
		clearScreen();
		cout << "Insert A Number: "; cin >> n;
		if (n < 0) { negative = true; n = -n; }
		cout << "The Amout Of Digits In " << (negative ? "-" : "") << n 
			  << " Is: " << digitAmount(n) << endl;
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

