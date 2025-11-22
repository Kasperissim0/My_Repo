#include<iostream>
#include<string>
#include<vector>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned changeAmount = 0;

bool sortByLength(vector<string>& input) {
	bool changesMade = false;
	
	clog << "Changes Made: " << endl << endl;
	for (size_t a = 0; a < input.size(); ++a) {
		size_t currentIndex = a;
		for (size_t b = (a + 1); b < input.size(); ++b) {
			if (input.at(b).length() < input.at(currentIndex).length()) currentIndex = b;
			}
		if (currentIndex != a) {
				clog << ++changeAmount << ". vector[" << a << "] = " 
					  << input.at(currentIndex) << endl;
				swap(input.at(currentIndex), input.at(a)); changesMade = true;
		}
	}
	return changesMade;
}

int main() {
	char goAgain; vector<string> container; bool changes;
	
	do {
		string tempStorage;
		container = {};
		clearScreen();
		cout << "Press 'q' To Stop Adding Strings" << endl;
		do {
			tempStorage = "";
			clearScreen();
			cout << "Insert String #" << (container.size() + 1) << ": ";
			cin >> tempStorage; if (tempStorage != "q") container.push_back(tempStorage);
		} while (tempStorage != "q" || (container.size() < 2)); clearScreen();
		changes = sortByLength(container); 
		cin.get(); cin.get(); clearScreen();
		cout << "The Strings Were " 
			  << (changes ? "Originally NOT" : "Already") 
			  << " Sorted" << endl << endl;
		for (size_t i = 0; i < container.size(); ++i) { 
			cout << "[ " << (i + 1) << " ] = " << container.at(i) << endl;
		}
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();
	return 0;
}
