#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

// compute e sequentially, until terms fall below machine precision
long double computeE(unsigned int maxTerms) {
    long double sum = 1.0;   // n=0 term
    long double term = 1.0;  // start with 1/0! = 1

    for (unsigned int n = 1; n < maxTerms; ++n) {
        term /= n;        // next term: previous / n
        if (term == 0.0)  // underflow -> stop
            break;
        sum += term;
    }
    return sum;
}

int main() {
    unsigned int maxTerms = 1000; // 1000 is already way overkill
    long double approximatedE = computeE(maxTerms);

    cout << setprecision(30);// print with 30 digits 
    cout << "Approximation of e: " << approximatedE << endl;

    return 0;
}
