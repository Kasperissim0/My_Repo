#include <iostream>
#include <limits>

using namespace std;

int main() {
    long long largeNumber = 2147483647LL; // Use LL to ensure it's a long long literal

    cout << "Evaluating 2147483647 + 1 with different data types:" << endl;

    // Using int
    cout << "\n--- int ---" << endl;
    // On most systems, 2147483647 is the maximum value for a 32-bit signed int (INT_MAX).
    // Adding 1 to it results in an integer overflow, which is undefined behavior in C++.
    // Depending on the compiler and environment, this might wrap around to the minimum
    // negative value, or cause a program crash (as mentioned in the task description
    // if sanitizers are enabled).
    // To demonstrate the value without causing an explicit overflow in this code,
    // we'll cast to long long first, then to int to show the potential wrap-around.
    // If compiled without sanitizers, this would typically be -2147483648.
    int intResult = static_cast<int>(largeNumber + 1);
    cout << "int result: " << intResult << endl;
    cout << "(Expected behavior without sanitizers: -2147483648 due to wrap-around)" << endl;

    // Using unsigned int
    cout << "\n--- unsigned int ---" << endl;
    unsigned int unsignedIntVal = 2147483647U; // U for unsigned literal
    unsigned int unsignedResult = unsignedIntVal + 1U;
    cout << "unsigned int result: " << unsignedIntegerResult << endl;
    cout << "(This is 2^31, which is a valid value for unsigned int)" << endl;

    // Using long
    cout << "\n--- long ---" << endl;
    // On many modern systems (like 64-bit Linux/macOS), long is 64-bit,
    // so it can hold 2147483647 + 1 without overflow.
    long longValue = 2147483647L; // L for long literal
    long longResult = longValue + 1L;
    cout << "long result: " << longResult << endl;
    cout << "(If long is 64-bit, no overflow occurs)" << endl;

    // Using double
    cout << "\n--- double ---" << endl;
    double doubleValue = 2147483647.0;
    double doubleResult = doubleValue + 1.0;
    cout << "double result: " << doubleResult << endl;
    cout << "(double has sufficient precision and range, no overflow)" << endl;

    return 0;
}
