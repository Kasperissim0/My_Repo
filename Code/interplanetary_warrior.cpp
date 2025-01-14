#include <iostream>
#include <string>
#include <iomanip> // Include this for std::setw
using namespace std;

    int main() {
  
        string name = "Little Mac";
        double weight;
        int planet;
        int type;
        string measurement[] = {"Kilograms", "Pounds"};
            string PlanetsList[] = {"Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
            int PlanetsLength[7];
        double GravityModifiers[] = {0.38, 0.91, 0.38, 2.34, 1.06, 0.92, 1.19};

                for (int i; i < 7; i++ ) {

                    PlanetsLength[i] = PlanetsList[i].length();
                    
                }

            cout << "Greetings Brave Warrior." <<endl << "Your Name Echoes Through the Galaxy, the LEGENDARY " << name <<endl;
            cout << "What Is Your Weight On Earth, Warrior?" <<endl;
        cin >> weight;
            cout << "\nAre Those Pounds or Kilograms?\n " <<endl;
            cout << setw(20) << "Kilograms" << setw(40) << "Press 1" <<endl;
            cout << setw(17) << "Pounds" << setw(43) << "Press 2" <<endl;
        cin >> type;

        
            cout << "Very Well\n" <<endl << "On What Plannet Shall You Battle, Warrior?\n" <<endl;
        cout << "If You Will Fight On" << setw(20) << "Mercury" << setw((PlanetsLength[0] * 2) * 2) << "Press 1" << endl;
        cout << "If You Will Fight On" << setw(18) << "Venus" << setw((PlanetsLength[1] * 2 + 6) * 2 - 2) << "Press 2" << endl;
        cout << "If You Will Fight On" << setw(17) << "Mars" << setw((PlanetsLength[2] * 2 + 9) * 2 - 3) << "Press 3" << endl;
        cout << "If You Will Fight On" << setw(20) << "Jupiter" << setw((PlanetsLength[3] * 2) * 2) << "Press 4" << endl;
        cout << "If You Will Fight On" << setw(19) << "Saturn" << setw((PlanetsLength[4] * 2 + 3) * 2 - 1) << "Press 5" << endl;
        cout << "If You Will Fight On" << setw(19) << "Uranus" << setw((PlanetsLength[5] * 2 + 3) * 2 - 1) << "Press 6" << endl;
        cout << "If You Will Fight On" << setw(20) << "Neptune" << setw((PlanetsLength[6] * 2) * 2) << "Press 7" << endl;
        cin >> planet;

        switch (planet)
        {
            case 1 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 2 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 3 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 4 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 5 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 6 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
            case 7 :
                cout << "\nYour Weight on " << PlanetsList[planet - 1] << " is " << weight * GravityModifiers[planet - 1] << " " << measurement[type - 1]  << "\n\n I Wish You a Decicive Victory, " << name << ".\n\n\n";
                break;
        
        default:
            cout << "Choose Again\n";
            cin >> planet;
            break;
        }
       
  
  return 0;
}