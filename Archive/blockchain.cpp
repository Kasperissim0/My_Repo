// ! Doesn't Work For Some Reason

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <bitset>
#include <cstdlib> // Include this for system()
#include <thread>
#include <chrono>
#include <cstdint>

using namespace std;

uint32_t String2Binary(const string& input) {
    
    string BinaryString = "";

    for (char letter : input) {

        BinaryString += bitset<8>(static_cast<unsigned char>(letter)).to_string();

    }

    if (BinaryString.length() > 32) {

        BinaryString = BinaryString.substr(0, 32);

    }
    while (BinaryString.length() < 32) {
        
        BinaryString = "0" + BinaryString;

    }

    return bitset<32>(BinaryString).to_ulong();
}
string Binary2String(const string& input) {
    
    string DecypheredString = "";
    stringstream CypheredStream (input);
    string TempString;

    while (CypheredStream >> TempString) {

        if (TempString.length() == 8) {

            unsigned long DecimalValue = bitset<8>(TempString).to_ulong();
            DecypheredString += static_cast<char>(DecimalValue);

        }

    }
    
    return DecypheredString;
}
uint32_t RandomNumber() {

  random_device RandomSeed; // Get a Random Number to use as a Seed
  mt19937 GenerateNumber(RandomSeed()); // Generate a Random Number Using The Seed
  uniform_int_distribution<> DistributionRange(111, 99999); // Define The Range Of The Number

  return DistributionRange(GenerateNumber); // Generate and return a random number within the specified range

}
uint32_t RequestPassword() {

    uint32_t Password;
    cout << "Create Your Password" << endl;
    cin >> Password;
    cin.ignore();

    return Password;

}
string RequestMessage() {

    string TempMessage;

    cout << "What is Your Message ?\n";
    getline(cin, TempMessage);
    system("clear");
    
    return TempMessage;

}


int main (){

    const uint32_t CommonNumber = RandomNumber(); // Represented as "g" in the Equation, from the Brilliant Course
    const uint32_t Modulus = RandomNumber(); // Represented as "n" in the Equation, from the Brilliant Course
    uint32_t Temp = RequestPassword();
    const uint32_t SecretKey = Temp;
    const uint32_t PublicKey = (CommonNumber * SecretKey) % Modulus;

    system("clear");

    string NormalMessage = RequestMessage();
    uint32_t BinaryMessage = String2Binary(NormalMessage);
    uint32_t Signature = (BinaryMessage * SecretKey) % Modulus;

    system("clear");

    if ((Signature * CommonNumber) % Modulus == (PublicKey * BinaryMessage) % Modulus) {

        cout << "Identity Verified\n" << endl;
    }

    else {

        cout << "Fake Identity\n" << endl;

    }

    cout << "(" << Signature << " * " << CommonNumber << ")" << " % " << Modulus << " = " << (Signature * CommonNumber) % Modulus << endl
         << "(" << PublicKey << " * " << BinaryMessage << ")" << " % " << Modulus << " = " << (PublicKey * BinaryMessage) % Modulus << endl
         << "\nCommonNumber - " << CommonNumber << endl
         << "Modulus - " << Modulus << endl
         << "SecretKey - " << SecretKey << endl
         << "PublicKey - " << PublicKey << endl
         << "NormalMessage - " << NormalMessage << endl
         << "BinaryMessage - " << BinaryMessage << endl
         << "Signature - " << CommonNumber << endl << endl;


    return 0;
}