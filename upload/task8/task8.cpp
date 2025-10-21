#include <iostream>

using namespace std;

int main() {
    const int secondsPerMinute = 60;
    const int secondsPerHour = 3600;
    const int secondsPerDay = 86400;
    const int secondsPerYear = 31536000; // 365 days

    int choice;
    cout << "Time Converter" << endl;
    cout << "1. Seconds to Years, Days, Hours, Minutes, Seconds" << endl;
    cout << "2. Years, Days, Hours, Minutes, Seconds to Seconds" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        long long totalSeconds;
        cout << "Enter total seconds: ";
        cin >> totalSeconds;

        int years = totalSeconds / secondsPerYear;
        long long remainingSeconds = totalSeconds % secondsPerYear;
        int days = remainingSeconds / secondsPerDay;
        remainingSeconds %= secondsPerDay;
        int hours = remainingSeconds / secondsPerHour;
        remainingSeconds %= secondsPerHour;
        int minutes = remainingSeconds / secondsPerMinute;
        int seconds = remainingSeconds % secondsPerMinute;

        cout << totalSeconds << " seconds is equivalent to: " << endl;
        cout << years << " years, " << days << " days, " << hours << " hours, " << minutes << " minutes, and " << seconds << " seconds." << endl;

    } else if (choice == 2) {
        int years, days, hours, minutes, seconds;
        cout << "Enter years: ";
        cin >> years;
        cout << "Enter days: ";
        cin >> days;
        cout << "Enter hours: ";
        cin >> hours;
        cout << "Enter minutes: ";
        cin >> minutes;
        cout << "Enter seconds: ";
        cin >> seconds;

        long long totalSeconds = (long long)years * secondsPerYear +
                                  (long long)days * secondsPerDay +
                                  (long long)hours * secondsPerHour +
                                  (long long)minutes * secondsPerMinute +
                                  seconds;

        cout << "The total number of seconds is: " << totalSeconds << endl;

    } else {
        cout << "Invalid choice. Please run the program again and select 1 or 2." << endl;
    }

    return 0;
}
