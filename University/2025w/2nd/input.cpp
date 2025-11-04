#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>

using namespace std;

void clearScreen() { system("clear"); }
bool possibleToCreateNumber(string userInput) {
	try { stod(userInput); return true; } 
	catch (const exception& e) { return false; } 
 } 

int main() {
	string userInput; double finalNumber;
	
	while (true) {
		clearScreen();
		cout << "Insert Radius Value: ";
		cin >> userInput;
		if (userInput == "q" || userInput == "exit") { clearScreen(); return 0; } 
		else if (!possibleToCreateNumber(userInput)) { continue; }
		else { finalNumber = stod(userInput); break;  }
	}
	// clearScreen(); // not necessary
	cout << "The Area Of A Circle With The Radius " << finalNumber
		  << " Equals: " << (M_PI * pow(finalNumber, 2)) <<  endl;
	return 0;
}
