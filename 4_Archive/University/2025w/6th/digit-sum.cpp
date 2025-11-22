#include<iostream>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned digitSum(int n) { return ((n < 10) ? n : (n % 10 + digitSum(n / 10))); }

int main() {
	char goAgain; int n; bool negative = false;
	
	do {
		clearScreen();
		cout << "Insert A Number: "; cin >> n;
		if (n < 0) { negative = true; n = -n; }
		cout << "The Sum Of The Digits From " << (negative ? "-" : "") << n 
			  << " Is: " << digitSum(n) << endl;
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

