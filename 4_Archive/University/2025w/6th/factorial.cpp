#include<iostream>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned factorial(unsigned n){ return ((n == 0) ? 1 : (n * factorial(n - 1))); }

int main() {
	for (unsigned i = 0; i < 30; ++i) cout << i << "! = " << factorial(i) << endl;
	return 0;
}
