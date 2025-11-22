#include<iostream>
#include<cmath>

using namespace std;

void clearScreen() { system("clear"); }

int main() {
	double catet1, catet2; char again;
	
	while (1) {	
		clearScreen();
		cout << "Insert Catet Values: ";
		cin >> catet1 >> catet2;

		cout << "The Hypothenuse Of The Triangle Is: " 
			  << sqrt((pow(catet1, 2) + pow(catet2, 2))) << endl
			  << "Go Again? (y/n): ";
		cin >> again;
		if () 
	}
	return 0;
}
