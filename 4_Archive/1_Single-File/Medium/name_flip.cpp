#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using  namespace std;

int main() {
  
  string Name;

  cout << "What is Your Name ?\n";
  cin >> Name; // Normal Name

  vector<char> NameCharacters(Name.length()); // Create a Vector with the length equal to the amount of characters in Name
  char TempName[Name.length()]; // Create an Array with the length equal to the amount of characters in Name

  for (int i = 0; i < Name.length()+1; ++i)
    NameCharacters[i] = Name[i]; // Store each letter of the Name inside the Vector

  for (int i = NameCharacters.size(), a = 0; i > 0; a++ ,i--)
    TempName[a] = NameCharacters[i - 1]; // Feed the previous vector into thins one in reverse order

  cout << "\nWelcome, " << TempName << " To the Weird and Wacky World of Reversicron.\n\n";
  this_thread::sleep_for(chrono::seconds(3)); // Wait, for dramatic effect
  cout << "Did You See What We Did ?\n" << "Behold, " << TempName << endl << endl;

  for (char Letter : NameCharacters)
    cout << Letter << endl; // Print out the Name, each letter on a seperate line

  cout << endl << "Into" << endl << endl;

  for (int i = 0; i < Name.length(); i++)
  cout << NameCharacters[i] << " = " << TempName[i] << endl; // Print out the both Name and reverse Name, letter by letter, each letter on a seperate line

cout << endl;

}

