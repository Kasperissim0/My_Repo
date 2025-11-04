#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

static const size_t LIST_LENGTH = 4; // Set List Clumping Here
// TODO FIX currently cannot set to 0 since modulo is used later

vector<string> splitVectors(vector<vector<string>>& elements, int returnVector) {
	return elements.at(returnVector);
}

string turnIntoList(vector<string>& elements, int changeLength = 0) {
	string list = ""; 
	size_t listLength = (changeLength ? changeLength : elements.size());
	if (elements.size() < listLength) listLength = elements.size();
	
	for(size_t i = 0; i < listLength; i++) {
		if (i < (listLength - 2)) list += (elements.at(i) + ", ");
		else if (i < (listLength - 1)) list += (elements.at(i) + " und ");
		else list += (elements.at(i) + "."); 
	}
	return list;
}

int main() {
	unsigned int inputAmount = 1;
	vector<string> elements;
	string tempStorage, spacing = ".    ";
	
	clearScreen();
	cout << "Insert Element #1: ";
	while (cin >> tempStorage && (tempStorage != "q" || (inputAmount %  LIST_LENGTH) >= 2)) {
		// DEBUG
		clog << "Input Amount: " << inputAmount << " | " 
			  << inputAmount << " % " << LIST_LENGTH << " = " 
			  << (inputAmount %  LIST_LENGTH) << endl;
		// DEBUG
		// TODO FIX currently increments inputAmount ONCE after input "q"
		if (tempStorage != "q") { elements.push_back(tempStorage); inputAmount++; }
		cout << "Insert Element #" << (elements.size() + 1) << ": ";
		tempStorage =  "";
	} 
	clearScreen();
	if (LIST_LENGTH) {
		size_t listAmount = round(inputAmount / LIST_LENGTH), index = 0;
		vector<vector<string>> allVectors {{""}};
		allVectors.resize(listAmount);
		// DEBUG
		clog << "List Amount: " << listAmount << endl;
		// DEBUG
		for (size_t a = 0; a < listAmount; a++) {
			allVectors.at(a).resize(LIST_LENGTH);
			for (size_t b = 0; b < LIST_LENGTH; b++) {
				// DEBUG
				clog << "Assigning: v[" << a << "][" << b << "] = v[" << index 
					  << "] = " << elements.at(index);
				// DEBUG
				allVectors.at(a).at(b) = elements.at(index);
				index++;
				if (index >= elements.size()) {
					allVectors.at(a).resize(LIST_LENGTH -1);
					// DEBUG
					clog << " | Final v[] size: " << elements.size() << endl;
					// DEBUG
					break; 
				}
				// DEBUG
				clog << " | v[] size: " << elements.size() << endl;
				// DEBUG
			}
		}
		
		cout << "The List(s) Are: " << endl << endl;
		for (size_t i = 1; i <= listAmount; i++) {
			vector<string> current = splitVectors(allVectors, (i - 1));
		
			// Dynamic Space Scaling
			if (i == 10) spacing.pop_back();
			if (i == 100) spacing.pop_back();
			if (i == 1000) spacing.pop_back();
			
			cout << i << spacing << turnIntoList(current, LIST_LENGTH) 
				  << endl;
		}
	}
	else {
		cout << "The List Is: " << endl << endl << turnIntoList(elements) << endl;
	}
	// cout <<  endl << inputAmount << endl; // Troubleshooting
	return 0;
}
