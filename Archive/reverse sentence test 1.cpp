#include <iostream>
#include <string>

using namespace std;

int main() {

  string sentence = "This is a sentence";
  char SentenceCharachter[sentence.length()];
  char ReversedSentenceCharachters[sentence.length() + 1]; // +1 for null terminator

    for (int a = 0,  b = sentence.length(); a < sentence.length(); a++, b--) {

      SentenceCharachter[a] = sentence[a];
      ReversedSentenceCharachters[b - 1] = SentenceCharachter[a];
    
    }

    ReversedSentenceCharachters[sentence.length()] = '\0'; // Null-terminate the string
    cout << ReversedSentenceCharachters << endl;

  return 0;  

}