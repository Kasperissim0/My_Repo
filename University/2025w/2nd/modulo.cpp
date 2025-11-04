#include<iostream>

using namespace std;

void clearScreen() { system("clear"); }

int main() {
	const int muffinsPerPerson = 2, muffinsPerBatch = 12;
	int amountOfGuests, muffinsNeeded;
	
	clearScreen();
	cout << "Insert The Amount Of Guests: ";
	cin >> amountOfGuests;
	muffinsNeeded = amountOfGuests * muffinsPerPerson;
	cout << "You Need " << ((muffinsNeeded / muffinsPerBatch) + 1) << " Batches" << endl
		  << (muffinsPerBatch - (muffinsNeeded % muffinsPerBatch)) << " Muffins Will Be Left" 
		  << endl;
	return 0;
}
