#include <iostream>

using namespace std;

int main() {
    double result, number;
    char op;

    cout << "Enter a mathematical expression: ";
    cin >> result;

    while (cin >> op && op != '!') {
        cin >> number;
        switch (op) {
            case '+':
                result += number;
                break;
            case '-':
                result -= number;
                break;
            case '*':
                result *= number;
                break;
            case '/':
                if (number != 0) result /= number; 
                else {
                    cout << "Error: Division by zero." << endl;
                    return 1;
                }
                break;
            default:
                cout << "Error: Invalid operator." << endl;
                return 1;
        }
    }

    cout << "Result: " << result << endl;

    return 0;
}