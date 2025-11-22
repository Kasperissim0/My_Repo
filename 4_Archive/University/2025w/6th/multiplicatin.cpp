#include<iostream>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

int mult(int a, int b) { return ((a == 0 || b == 0) ? 0 : (a + mult(a, b-1))); }

int main() {
	char goAgain;
	int a, b, answer;
	
	do {
		clearScreen();
		cout << "Insert a: "; cin >> a;
		cout << "Insert b: "; cin >> b;
		// Slight Optimization
		if (a == 1) answer = b;
		else if (b == 1) answer = a;
		else {
			if (b > a) swap(a, b);
			answer = mult(a, b);
		}
		cout << a << " * " << b << " = " << answer << endl;
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

