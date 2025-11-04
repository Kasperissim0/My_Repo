#include<iostream>

using namespace std;

void clearScreen() { system("clear"); }

int main() {
	const int muffinsPerPerson = 2, muffinsPerBatch = 12;
	int amountOfGuests, muffinsNeeded, muffinsLeft;
	
	clearScreen();
	cout << "Insert The Amount Of Guests: ";
	cin >> amountOfGuests;
	muffinsNeeded = amountOfGuests * muffinsPerPerson;
	muffinsLeft = muffinsNeeded % muffinsPerBatch;
	cout << "You Need " 
		  << ((muffinsNeeded / muffinsPerBatch) + (muffinsLeft == 0 ? 0 : 1))
		  << " Batches" << endl
		  << (muffinsLeft == 0 ? 0 : (muffinsPerBatch - muffinsLeft)) << " Muffins Will Be Left" 
		  << endl;
	return 0;
}
