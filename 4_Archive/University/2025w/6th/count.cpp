#include<iostream>
#include<string>
#include<vector>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

vector<size_t> substrIndexes(string n, char c) {
	vector<size_t> indexes = {};
	for (size_t i = 0; i < n.length(); ++i) if (n.at(i) == c) indexes.push_back(i); 
 	return indexes;
 }
void highlighterArrows (string n, vector<size_t> indexes) {
	string space = " ", point = "△", base = "|"; unsigned row = 3; // i for the point and one for the base
	bool foundIndex = false; unsigned count = 1;
	while (row) {
		cout << "                "; //! TODO Scale This Dynamically
	 	for (size_t i = 0; i < n.length(); ++i) {
	 		foundIndex = false;
	 		for (size_t t = 0; t < indexes.size(); ++t) {
	 			if (indexes.at(t) == i) {
	 				foundIndex = true;
	 				switch(row) {
	 					case 1:
	 						cout << count++;
	 						break;
	 					case 2:
	 						cout << base;
	 						break;
	 					case 3:
							cout << point;
							break;
						default:
		 					cout << "ERROR";
		 					break;
	 				} 
	 			}
	 		}
	 		if (!foundIndex) cout << space;
	 	}
	 	cout << endl;
	 	--row;
 	}
 }

int main() {
	char goAgain; string n; char c;
	
	do {
		clearScreen();
		cout << "Insert The String: "; cin >> n;
		cout << "A Char To Find In \"" << n << "\": "; cin >> c;
		clearScreen();
		cout << "'" << c << "'" << " Appears In \"" << n << "\" " 
			  << substrIndexes(n, c).size() << " Times" << endl;
		highlighterArrows(n, substrIndexes(n, c));
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

