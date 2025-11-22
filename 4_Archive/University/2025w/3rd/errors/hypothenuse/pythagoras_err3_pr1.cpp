#include<iostream>
#include<cmath>
using namespace std;

//Dieses Programm berechnet die Hypotenuse eines rechtwinkeligen Dreiecks aus
//den Katheten
int Main() // main incorrect
{
    double a{0}, b{0};
    cout << "Bitte geben Sie die Laenge der Kathete a in cm ein:\n";
    cin >> a;
    cout << "Bitte geben Sie die Laenge der Kathete b in cm ein:\n";
    cin >> b;

    cout << "Die Hypothenuse c ist " << sqrt(a*a+b*b) <<" cm lang.\n";

    return 0;
}
