#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using  namespace std;

int main() {
  
  string Name;

  cout << "What is Your Name ?\n";
  cin >> Name;

  vector<char> NameCharacters(Name.length());
  char TempName[Name.length()];

  for (int i = 0; i < Name.length()+1; ++i)
    NameCharacters[i] = Name[i];

  for (int i = NameCharacters.size(), a = 0; i > 0; a++ ,i--)
    TempName[a] = NameCharacters[i - 1];

  cout << "\nWelcome, " << TempName << " To the Weird and Wacky World of Reversicron.\n\n";
  this_thread::sleep_for(chrono::seconds(3));
  cout << "Did You See What We Did ?\n" << "Observe, " << TempName << endl << endl;

  for (char Letter : NameCharacters)
    cout << Letter << endl;

  cout << endl << "Into" << endl << endl;

  for (int i = 0; i < Name.length(); i++)
  cout << NameCharacters[i] << " = " << TempName[i] << endl; 

cout << endl;

}

