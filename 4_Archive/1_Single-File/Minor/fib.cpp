#include <iostream> 
using namespace std;
unsigned fib(unsigned n) { return (n == 0 ? 0 : (n == 1 ? 1 : (fib(n-2)+fib(n-1)))); }
int main() { unsigned i; cin >> i; cout << "Fibonnaci.at(" << i << ")  = " << fib(i) << endl; return 0; }