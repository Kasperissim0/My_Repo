#include<iostream>
#include<cmath>
#include<vector>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

bool isPrime(int& number) { 
	int upperBound = ceil(sqrt(number)); // optional optimization
	
	if (number % 2 == 0) return false;
	for (int i = 3; i <= upperBound; i += 2) {
		if (number == 2) return true;
		else if (number % i == 0) return false;
	}
	return (number <= 1 ? false : true);
}
vector<int> findDivisors(int& number) { 
	vector<int> divisors;
	
	for (int i = 1; i <= number; i++) {
		if (number % i == 0) divisors.push_back(i);
	}
	return divisors;
}

int main() {
	int userInput;
	vector<int> divisors;
	
	clearScreen();
	cout << "Insert an Integer: ";
	cin >> userInput;
	
	cout << "The Number " << userInput << " Is "
		  << (isPrime(userInput) ? "" : "NOT ") << "Prime" << endl
	 	  << "\nIt Is Divisible By: ";
	 	  
	 divisors = findDivisors(userInput);
	 for (size_t i = 0; i < divisors.size(); i++) {
	 	cout << divisors.at(i);
	 	if (i != (divisors.size() - 1)) cout << ", ";
	 	else cout << "." << endl;
	 }	
}
