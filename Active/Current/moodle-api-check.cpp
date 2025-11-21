#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <curl/curl.h> // for http/api calls
#include <nlohmann/json.hpp>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

static const string MOODLE_URL = "https://moodle.univie.ac.at";
static const unsigned REQUIRED_TOKEN_LENGTH = 11;


class MoodleUploader {
  private:
    const string URL = MOODLE_URL;
    unsigned authorizationToken;
  public:
    MoodleUploader(const string& passedToken) {
      if (passedToken.empty())                                      throw runtime_error("Passed Token Is Empty");
      else if ((passedToken.length() - 1) != REQUIRED_TOKEN_LENGTH) throw runtime_error("Passed Token Does Not Match Length Specification");
      else                                                          this->authorizationToken = stoi(passedToken);
    }
    json uploadFileToDraft(const fs::path& filePath) {

    }
    unsigned findAssignmentUploadField(const unsigned& courseID, const string& searchPattern) {

    }
    bool attemptToUploadFile(const unsigned& targetFieldID, const unsigned& draftItemID) {

    }
};

int main(int amountOfArguments, char *arrayOfArguments[]) {
  unsigned moodleToken, courseID, assignmentFieldID, draftItemID; 
  string assignmentField; fs::path fileToUpload; json uploadResult; // MoodleUploader = uploader; // defined later

  //* Step 0: Verify + Assign Passed Arguments
  if (amountOfArguments != 5) {
    cerr << "Invalid Executable Envocation" << endl << "Execution MUST Look Like This: "
         << "./executable-title MOODLE_TOKEN COURSE_ID \"ASSIGNMENT_COURSE_FOR_UPLOAD\" \"PATH_TO_UPLOAD_FILE\""
         << endl << "EXAMPLE: " << endl << "./moodle_test 1234567890123 12345 \"Blatt 1\" \"test.pdf\"" << flush;
    return 1;
  }
  else {
    try { moodleToken = stoi(arrayOfArguments[1]); }
    catch (const invalid_argument& e) {
       cerr << "Unable To Convert \"" << arrayOfArguments[1] << "\" Into An Integer: " << e.what() << endl; 
       return 1;
      }
    catch (const out_of_range& e) {
       cerr << "Unable To Convert \"" << arrayOfArguments[1] << "\" Into An Integer: " << e.what() << endl; 
       return 1;
      }
    try { courseID = stoi(arrayOfArguments[2]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    assignmentField = arrayOfArguments[3];
    fileToUpload = arrayOfArguments[4];
    if (!fs::exists(fileToUpload)) {
      cerr << fileToUpload << " Does Not Exist" << endl;
      return 1;
    }
    cout << "Proceeding With: " << endl
         << "- Moodle Token: " << moodleToken
            << " | Identical To Passed Variable: " << (moodleToken == stoi(arrayOfArguments[1]) ? "✅" : "❌") << endl
         << "- Course ID" << courseID
            << " | Identical To Passed Variable: " << (courseID == stoi(arrayOfArguments[2]) ? "✅" : "❌") << endl
         << "- Assignment Upload" << assignmentField
            << " | Identical To Passed Variable: " << (assignmentField == arrayOfArguments[3] ? "✅" : "❌") << endl
         << "- File To Upload" << fileToUpload
            << " | Identical To Passed Variable: " << (fileToUpload.string() == arrayOfArguments[4] ? "✅" : "❌") << endl;
    try { MoodleUploader uploader(arrayOfArguments[1]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << to_string(moodleToken) << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << to_string(moodleToken) << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const runtime_error& e) { 
      cerr << "Error Encountered During Construction Of The Uploader: " << e.what() << endl; 
      return 1;
    }
  }

  //* Step 1: Upload File To Draft Area


  //* Step 2: Find Upload Target (Course/Assignment/Target)


  //* Step 3: Attempt The Upload + Handle Result
    try {
      if (uploader.attemptToUploadFile(assignmentFieldID, draftItemID)) {
        cout << "\n✅ SUCCESS!" << endl
             << ""; // TODO specify variables used here
        return 0;
      }
      else cerr << "\n❌ FAILURE!" << endl;
    }
    catch (const runtime_error& e){
      cerr << e.what() << endl;
      return 1;
    }
}