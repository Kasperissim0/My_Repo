#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double betAmount;
    int trials;

    cout << "Roulette Win/Loss Calculator" << endl;
    cout << "The player always bets on the number 0." << endl;
    cout << "A win on 0 pays 35 to 1." << endl;

    cout << "Enter the fixed bet amount: ";
    cin >> betAmount;
    cout << "Enter the number of trials until the win occurred: ";
    cin >> trials;

    if (betAmount <= 0 || trials <= 0) {
        cout << "Bet amount and trials must be positive numbers." << endl;
        return 1;
    }

    // There are (trials - 1) losses.
    double totalLoss = betAmount * (trials - 1);
    // The win gives a net profit of 35 times the bet.
    double winAmount = betAmount * 35;

    double finalBalance = winAmount - totalLoss;

    cout << fixed << setprecision(2);
    cout << "\nTotal money lost before winning: " << totalLoss << endl;
    cout << "Money won on the final trial: " << winAmount << endl;
    cout << "------------------------------------" << endl;

    if (finalBalance > 0) {
        cout << "Total net win: " << finalBalance << endl;
    } else if (finalBalance < 0) {
        cout << "Total net loss: " << -finalBalance << endl;
    } else {
        cout << "The player broke even." << endl;
    }

    return 0;
}
