#include<iostream>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned fib(unsigned n){ return ((n <= 2) ? 1 : (fib(n-2)+fib(n-1))); }

int main() {
	clearScreen();
	for (unsigned i = 0; i <= 45; ++i) cout << "fibonacciSequence[" << i << "] = " << fib(i) << endl;
	return 0;
}
