#include<iostream>
#include "functions/screen.h" // adds clearScreen()        + #include <iomanip>
#include "functions/wait.h"   // adds wait(double seconds) + #include <thread> and #include <chrono>
															// use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

int main() {
	char goAgain;
	
	do {
		clearScreen();
		cout << "hey " << flush; wait(3); cout << " you";
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}