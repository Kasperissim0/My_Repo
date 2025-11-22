#include<iostream>
#include<string>
#include "functions/screen.h" // use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;

unsigned amountOfMoves = 0;
unsigned amountOfFunctionCalls = 0;
unsigned maxDepth = 0;

void hanoi(char from, char help, char to, unsigned n, unsigned depth = 0) {
	++amountOfFunctionCalls;
	if (depth > maxDepth) maxDepth = depth;
	if (n == 1) {
		++amountOfMoves;
		cout << "Move from " << from << " to " << to << endl;
		return;
	}
	else {
		hanoi(from, help, to, n-1, depth+1);
		++amountOfMoves;
		cout << "Move from " << from << " to " << to << endl;
		hanoi(from, help, to, n-1, depth+1);
	}
}

int main() {
	char goAgain; unsigned torusAmount;
	
	do {
		while (cout << "Insert The Amount Of Toruses In Tower A: " && cin >> torusAmount) {
			clearScreen();
			amountOfMoves = 0;
			amountOfFunctionCalls = 0;
			maxDepth = 0;
			hanoi('A', 'B','C', torusAmount);
			cout << endl << "Amount Of Moves: " << amountOfMoves << endl
				  << "Amount Of Funtion Calls: " <<  amountOfFunctionCalls << endl
				  << "Depth Of Recursion Tree: " <<  maxDepth << endl;
		}
	} while(cout << endl << "Go Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}

