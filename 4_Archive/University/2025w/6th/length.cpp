#include<iostream>
#include<string>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned stringLength(string n) { return ((n.empty()) ? 0 : (1 + stringLength(n.substr(1)))); }

int main() {
	char goAgain; string n;
	
	do {
		clearScreen();
		cout << "Insert A String: "; cin >> n;
		cout << "The Length Of This String Is: " << stringLength(n) << endl;
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

