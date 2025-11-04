#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<iomanip> // remove if using clearScreen();
// #include "/home/korniienkd07/University/2025w/functions/screen.h"

using namespace std;

static const size_t LIST_CAPACITY = 3; //! Set List Clumping Here, 0 for 1 single list

vector<string> splitVectors(vector<vector<string>>& elements, int returnVector) {
	return elements.at(returnVector);
}
string turnIntoList(vector<string>& elements, int changeLength = 0) {
	string list = ""; 
	size_t listLength = (changeLength ? changeLength : elements.size());
	if (elements.size() < listLength) listLength = elements.size();
	
	for(size_t i = 0; i < listLength; i++) {
		if (i < (listLength - 2)) list += (elements.at(i) + ", ");
		else if (i < (listLength - 1)) list += (elements.at(i) + " and ");
		else list += (elements.at(i) + "."); 
	}
	return list;
}

int main() {
	vector<string> elements;
	string tempStorage, spacing = ".     ";

	static_assert(LIST_CAPACITY != 1, "A List With One Element Makes No Sense");
	
	system("clear"); // clearScreen();
	cout << "Insert Element #1: ";
	while (cin >> tempStorage && (tempStorage != "q" || elements.size() < 2 || (LIST_CAPACITY != 0 && elements.size() % LIST_CAPACITY == 1))) {
		if (tempStorage != "q") { elements.push_back(tempStorage); }
		else if (elements.size() > 2 && (elements.size() % LIST_CAPACITY != 1)) break;
		cout << "Insert Element #" << (elements.size() + 1) << ": ";
		tempStorage =  "";
	} 
	
	system("clear"); // clearScreen();
	if (LIST_CAPACITY > 0 && !elements.empty()) {
		size_t listAmount = ceil((double)elements.size() / LIST_CAPACITY), index = 0;
		vector<vector<string>> allVectors;
		allVectors.resize(listAmount);
		for (size_t a = 0; a < listAmount; a++) {
			allVectors.at(a).resize(LIST_CAPACITY);
			for (size_t b = 0; b < LIST_CAPACITY; b++) {
				if (index >= elements.size()) {	allVectors.at(a).resize(b);	break; }
				allVectors.at(a).at(b) = elements.at(index);
				index++;
			}
		}
		
		cout << "The List(s) Are: " << endl << endl;
		for (size_t i = 0; i < listAmount; i++) {
			vector<string> current = splitVectors(allVectors, i);

			// Dynamic Space Scaling
			if ((i + 1) == 10) spacing.pop_back();
			if ((i + 1) == 100) spacing.pop_back();
			if ((i + 1) == 1000) spacing.pop_back();
			
			cout << (i + 1) << spacing << turnIntoList(current, LIST_CAPACITY) << endl;
		}
	}
	else cout << "The List Is: " << endl << endl << turnIntoList(elements) << endl;
	return 0;
}