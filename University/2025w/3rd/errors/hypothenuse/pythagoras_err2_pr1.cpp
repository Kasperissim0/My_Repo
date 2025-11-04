#include<iostream>
#include<cmath>
using namespace std;

//Dieses Programm berechnet die Hypotenuse eines rechtwinkeligen Dreiecks aus
//den Katheten
int main() // meters instead of cm
{
	double a{0}, b{0};
    cout << "Bitte geben Sie die Laenge der Kathete a in m ein:\n";
    cin >> a;
    cout << "Bitte geben Sie die Laenge der Kathete b in m ein:\n";
    cin >> b;

    cout << "Die Hypothenuse c ist " << sqrt(a*a+b*b) <<" m lang.\n";

    return 0;
}
