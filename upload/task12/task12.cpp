#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Calculate combinations for 6 out of 45
    long long combinations = 45LL * 44 * 43 * 42 * 41 * 40 / (6 * 5 * 4 * 3 * 2 * 1);
    
    double probability = 1.0 / combinations;

    cout << "Austrian Lottery (6 out of 45)" << endl;
    cout << "Total number of combinations: " << combinations << endl;
    cout << "Probability of a jackpot: 1 in " << combinations << endl;
    cout << scientific << setprecision(8);
    cout << "As a decimal: " << probability << endl;

    return 0;
}