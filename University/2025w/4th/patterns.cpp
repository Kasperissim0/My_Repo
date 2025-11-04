#include<iostream>
#include<thread>
#include<chrono>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

const int amountOfPatterns = 6;

void displayPattern(char& selection) {
	clearScreen();
	char space = ' ', star = '*', line = '\n';
	switch (selection) { 
		case 'a':
			for (int a = 5; a < 0; a--) {
				for (int b = 0; b < a; b++) {
					cout << star;
				}
				cout << line;
			} 
		break;
		case 'b':
			
		break;
		case 'c':
			
		break;
		case 'd':
			
		break;
		case 'e':
			
		break;
		case 'f':
			
		break;
		default:
			cout << "Invalid Input" << endl;
		break;
	}
	cout << endl;
	this_thread::sleep_for(chrono::seconds(2));
}
char toChar(int object) {
	return (static_cast<char>(96 + object)); // add 
}
void getInput(char& storage) {
	cout << endl << "Choice: ";
	cin >> storage;
} 

int main() {
	char userChoice; bool again;
	do {
		// Choose Pattern
		clearScreen();
		cout << "Choose A Pattern: " << endl;
		for (int i = 1; i <= amountOfPatterns; i++) {
			cout << "[ " << toChar(i) << " ]" << " Pattern " << i << endl;
		}
		getInput(userChoice);
		displayPattern(userChoice); // Display Pattern
		
		// Choose Whether To Continue
		cout << "Go Again? (y/n)" << endl;
		getInput(userChoice);
		if (userChoice == 'y') again = true;
		else again = false;
	} while(again);
	return 0;
}
