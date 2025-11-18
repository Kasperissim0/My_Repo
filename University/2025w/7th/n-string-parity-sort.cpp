#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include <stdexcept>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned changeAmount = 0;

void sortByParity(vector<int>& even, vector<int>& odd) {
	vector<int> combined;
	for (size_t i = 0; i < (even.size() + odd.size()); ++i) {
		if (i < even.size()) combined.push_back(even.at(i));
		else combined.push_back(odd.at((i - (even.size() - 1))));
	} even.clear(); odd.clear();
	for (size_t i = 0; i < combined.size(); ++i) {
		if (combined.at(i) % 2 == 0) even.push_back(combined.at(i));
		else odd.push_back(combined.at(i));
	}
}

int main() {
	char goAgain; vector<int> v1, v2; int temp;
	
	do {
		unsigned entry = 0;
		clearScreen();
		while (cout << "Insert #1." << ++entry << ": " && cin >> temp) v1.push_back(temp);
		entry = 0; cin.ignore('\n', numeric_limits<int>::max()); cin.clear();
		while (cout << "Insert #2." << ++entry << ": " && cin >> temp) v2.push_back(temp);
		sortByParity(v1, v2);
		for (const auto& elem : v1) cout << elem << " ";
		cout << endl;
		for (const auto& elem : v2) cout << elem << " ";
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();
	return 0;
}
