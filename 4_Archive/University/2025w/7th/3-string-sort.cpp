#include<iostream>
#include<cassert>
#include<string>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

bool sortByLength(string& a, string& b, string& c) {
	const size_t aLength = a.length(), bLength = b.length(), cLength = c.length();
	
	if (a.length() > b.length()) swap(a, b);
	if (b.length() > c.length()) swap (b, c);
	if (a.length() > b.length()) swap(a, b);
	return ((aLength <= bLength && bLength <= cLength) ? true : false);
}

int main() {
	char goAgain; string a, b, c;
	
	do {
		clearScreen();
		cout << "Insert 3 Strings: " << endl;
		cin >> a >> b >> c; clearScreen();
		cout << "The String Were " 
			  << (sortByLength(a, b, c) ? "Already" : "Originally NOT") 
			  << " Sorted" << endl << endl
		 	  << "min: " << a << endl
			  << "mid: " << b << endl
			  << "max: " << c << endl;
		assert(a.length() <= b.length() && b.length() <= c.length());
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();
	return 0;
}
