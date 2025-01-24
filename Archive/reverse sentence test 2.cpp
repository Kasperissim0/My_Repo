#include <iostream>
#include <string>

using namespace std;

int main() {

  string sentence = "This is a sentence";
  char ReversedSentenceCharachters[sentence.length() + 1]; // +1 for null terminator

    for (int i = sentence.length(); i > 0; i--) {

      ReversedSentenceCharachters[i - 1] = sentence[sentence.length() - i];
    
    }

    ReversedSentenceCharachters[sentence.length()] = '\0'; // Null-terminate the string
    cout << ReversedSentenceCharachters << endl;

  return 0;  

}