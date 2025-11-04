#include<iostream>
#include<vector>
#include "/home/korniienkd07/2025w/functions/screen.h"

using namespace std;

int main() {
    vector<double> values;
    double tempStorage,totalDistance = 0, totalFuel = 0, answer;
    char decision; bool input = true;
    
    // Recieve Input
    while (input) {
		 clearScreen();
		 cout << "Amout Of Kilometers Driven: ";
		 cin >> tempStorage;
		 values.push_back(tempStorage);
		 cout << "Amout Of Fuel Used (in liters): ";
		 cin >> tempStorage;
		 values.push_back(tempStorage);
		 
		 // Evaluate Loop Continuation
		 cout << "Continue? (y/n): ";
		 cin >> decision;
		 input = (decision != 'n');
    }

    // Calculate
    for (size_t i = 0; i < values.size(); i++) {
    	if (i % 2 == 0) totalDistance += values[i];
    	else totalFuel += values[i];
    }
    answer = (totalFuel/totalDistance)*100;
    
    // Display
    clearScreen();
    cout << "Total Distance Driven: " << totalDistance << " kilometers" << endl
    		<< "Total Fuel Used: " << totalFuel << " liters" << endl
         << "\nThis Vehicle Will Use " << answer << " liters of fuel per 100 kilometers" << endl;

    return 0;
}
