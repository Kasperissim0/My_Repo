#include <iostream>
#include <random>

using namespace std;

int main() {

  const short MinValue = 1;
  const short MaxValue = 2;
  int RandomNumber;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<short> distr(MinValue, MaxValue);
  
  RandomNumber = distr(gen);

  switch (RandomNumber)
  {
  case 1 :
  cout << "The Coin Landed on Tails.\n";
    break;
  case 2 :
  cout << "The Coin Landed on Tails.\n";
  break;
  default:
  cout << "The Coin Landed on it's Side.\n";
    break;
  }

  return 0;
