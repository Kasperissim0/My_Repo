#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

string ReverseSentence(const string& sentence) {

  char ReversedSentenceCharachters[sentence.length() + 1]; // +1 for null terminator

    for (int i = sentence.length(); i > 0; i--) { 
      // Reverse the string into the Array

      ReversedSentenceCharachters[i - 1] = sentence[sentence.length() - i];
      
    }

    ReversedSentenceCharachters[sentence.length()] = '\0'; // Null-terminate the string


    return string(ReversedSentenceCharachters); // Return the reversed string

}

int main() {

  string sentence;

  cout << "Insert Your Sentence Here: " << endl;
  getline(cin, sentence);

  sentence = ReverseSentence(sentence); // Call the function to reverse the sentence
  cout << "\nThe Reversed Sentence: " << endl << sentence << endl;

  return 0;

}