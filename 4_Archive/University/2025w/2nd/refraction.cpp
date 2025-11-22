#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>

using namespace std;

void clearScreen() { system("clear"); }
bool wantToEscape(string& userInput) { 
	if (userInput == "q" || userInput == "exit") { clearScreen(); return true; }
	else { return false; }
}
bool possibleToCreateNumber(string userInput) {
	try { stod(userInput); return true; } 
	catch (const exception& e) { return false; } 
 } 

int main() {
	string userInput; double n1, n2, a1; bool angle1, angle2, angle3;
	
	do {
		clearScreen();
			cout << "Insert n1: ";
		cin >> userInput;
		if (wantToEscape(userInput)) { clearScreen(); return 0; } 
		else if (!possibleToCreateNumber(userInput)) { continue; }
		else { n1 = stod(userInput); angle1 = true;  }
				cout << "Insert n2: ";
		cin >> userInput;
		if (wantToEscape(userInput)) { clearScreen(); return 0; } 
		else if (!possibleToCreateNumber(userInput)) { continue; }
		else { n2 = stod(userInput); angle2 = true;  }
				cout << "Insert a1: ";
		cin >> userInput;
		if (wantToEscape(userInput)) { clearScreen(); return 0; } 
		else if (!possibleToCreateNumber(userInput)) { continue; }
		else { a1 = stod(userInput); angle3 = true;  }
	} while (!angle1 && !angle2 && !angle3);
	// clearScreen(); // not necessary
	cout << "The Area Of A Circle With The Radius " << finalNumber
		  << " Equals: " << (M_PI * pow(finalNumber, 2)) <<  endl;
	return 0;
}
