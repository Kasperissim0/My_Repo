#include<iostream>
#include<cmath>
using namespace std;

//Dieses Programm berechnet die Hypotenuse eines rechtwinkeligen Dreiecks aus
//den Katheten
int main()
{
    double a{0}, b{0};
    cout << "Bitte geben Sie die Laenge der Kathete a in cm ein:\n";
    cin >> a;
    cout << "Bitte geben Sie die Laenge der Kathete b in cm ein:\n";
    cin >> b;

    cout << "Die Hypothenuse c ist " << sqrt(a*a/100+b*b/00) <<" m lang.\n"; // 2nd division is wrong

    return 0;
}
