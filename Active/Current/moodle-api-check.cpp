#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <curl/curl.h> // for http/api calls
#include <nlohmann/json.hpp>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

static const string MOODLE_URL = "https://moodle.univie.ac.at";
static const string UPLOAD_URL = "/webservice/upload.php";
static const string API_URL = "/webservice/rest/server.php";
static const unsigned TOKEN_MIN_LENGTH = 16, TOKEN_MAX_LENGTH = 64;
 
static size_t writeCallback(void* newContent, size_t elementSize, size_t amountOfElements, void* userData) {
  string* responseString = static_cast<string*>(userData);
  size_t totalBytesRecieved = elementSize * amountOfElements;
  responseString->append(static_cast<char*>(newContent), totalBytesRecieved);
  return totalBytesRecieved;
}

class MoodleUploader {
  private:
    const string URL = MOODLE_URL;
    string authorizationToken;
  public:
    MoodleUploader(const string& tempValue = "") { 
      if (tempValue != "") throw runtime_error("Set Token Using Setter Function"); 
      else                 this->authorizationToken = tempValue;
    }
    void setToken(const string& passedToken) {
      if (passedToken.empty())                                            throw runtime_error("Passed Token Is Empty");
      else if ((passedToken.length() - 1) < TOKEN_MIN_LENGTH)             throw runtime_error("Passed Token Does Not Match Length Specification: Too Short");
      else if ((passedToken.length() - 1) > TOKEN_MAX_LENGTH)             throw runtime_error("Passed Token Does Not Match Length Specification: Too Long"); 
      else                                                                this->authorizationToken = passedToken;
      cout << "\n ✅ Token Set Successfully: "; for (const auto& elem: authorizationToken) cout << "X"; cout << endl; 
    }
    json uploadFileToDraftArea(const fs::path& file) noexcept {
      CURL* curl; CURLcode responseStatusCode; curl_mime* form; curl_mimepart* field; json parsedResponse;
      string responseContent, destinationURLAdress = URL + UPLOAD_URL, tempStorage;

      cout << "\n=== STEP 1: Uploading File ===" << endl
           << "File: " << file << endl;

      curl = curl_easy_init();
      if (!curl) {
        cerr << "Failed To Initialize 'curl' Object" << endl;
        return json::parse("{\"error\": \"curl init failed\"}");
      }
      
      form = curl_mime_init(curl);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "token");
          curl_mime_data(field, authorizationToken.c_str(), CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "component");
          curl_mime_data(field, "user", CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "filearea");
          curl_mime_data(field, "draft", CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "itemid");
          curl_mime_data(field, "0", CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "filepath");
          curl_mime_data(field, "/", CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "filename"); tempStorage = file.filename().string();
          curl_mime_data(field, tempStorage.c_str(), CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "file"); tempStorage = file.string();
          curl_mime_filedata(field, tempStorage.c_str());
      // Set URL to send request to
      curl_easy_setopt(curl, CURLOPT_URL, destinationURLAdress.c_str());
       // Attach multipart form
      curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
      // Set callback function (where response data goes)
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      // Set pointer to response string (callback will fill this)
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContent);

      responseStatusCode = curl_easy_perform(curl);
      if (responseStatusCode != CURLE_OK) {
        cerr << "ERROR: Upload failed - " << curl_easy_strerror(responseStatusCode) << endl;
        curl_easy_cleanup(curl); curl_mime_free(form);
        return json::parse("{\"error\": \"upload failed\"}");
      }

      curl_easy_cleanup(curl); curl_mime_free(form);
      cout << "Raw Response From API: " << endl << responseContent << endl << "\n=== STEP 1.5: Parsing Response ===" << endl;

      try { parsedResponse = json::parse(responseContent); return parsedResponse; }
      catch (const json::parse_error& e) {
        cerr << "ERROR: Failed to parse JSON - " << e.what() << endl;
        return json::parse("{\"error\": \"json parse failed\", \"raw\": \"" + responseContent + "\"}");
      }
    }
    unsigned findTargetUploadField(const unsigned& courseID, const string& searchPattern, const unsigned& assignmentNumber) noexcept {
      CURL* curl; CURLcode responseStatusCode; curl_mime* form; curl_mimepart* field; json parsedResponse;
      string responseContent, apiRequestURL, fullSearchPattern = searchPattern + " " + to_string(assignmentNumber);

      cout << "\n=== STEP 2: Finding Assignment ===" << endl
           << "Course ID: " << courseID << endl
           << "Search Pattern: \"" << searchPattern << " X" << endl
           << "Specific Entry: \"" << searchPattern << " " << assignmentNumber << "\"" << endl;

      curl = curl_easy_init();
      if (!curl) {
        cerr << "Failed To Initialize 'curl' Object" << endl;
        return 0;
      }

      apiRequestURL = URL + API_URL + "?" + "wstoken=" + authorizationToken 
                                                       + "&wsfunction=mod_assign_get_assignments" 
                                                       + "&moodlewsrestformat=json" 
                                                       + "&courseids[0]=" + to_string(courseID);
      curl_easy_setopt(curl, CURLOPT_URL, apiRequestURL.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContent);
      
      responseStatusCode = curl_easy_perform(curl);
      if (responseStatusCode != CURLE_OK) {
        cerr << "ERROR: Request failed - " << curl_easy_strerror(responseStatusCode) << endl;
        curl_easy_cleanup(curl);
        return 0;
      }
      
      curl_easy_cleanup(curl); 
      cout << "Raw API Response:" << endl << responseContent << endl << "\n=== STEP 2.5: Searching For Match ===" << endl;

      try {
        parsedResponse = json::parse(responseContent);
        if (!parsedResponse.contains("courses") || !parsedResponse["courses"].is_array()) {
          cerr << "ERROR: Unexpected response format - Course Array Is Absent" << endl;
          return 0;
        }
        
        for (const auto& course : parsedResponse["courses"]) {
          if (!course.contains("assignments")) { cerr << "WARNING: Course #" << course <<  " Has No Assignments Field" << endl; continue; }
          for (const auto& assignment : course["assignments"]) {
            unsigned assignmentID = assignment["id"]; string assignmentName = assignment["id"];
            
            cout << "\n Checking: \"" << assignmentName << "\" (ID: " << assignmentID << ")" << endl;
            if (assignmentName == fullSearchPattern) {
              cout << "\n✅ MATCH FOUND!" << endl
                  << "Assignment: \"" << assignmentName << "\"" << endl
                  << "ID: " << assignmentID << endl;
              return assignmentID;
            }
            else {
              cout << "\n❌ MATCH NOT FOUND!" << endl
                  << assignmentName << " ≠ " << fullSearchPattern << endl;
            }
          }
        }
        cerr << "ERROR: No Assignment Found Matching \"" << fullSearchPattern << "\"" << endl;
        return 0;
      }
     catch (const json::parse_error& e) {
        cerr << "ERROR: JSON parsing failed - " << e.what() << endl;
        return 0;
      }

};
    bool attemptFileUpload(const unsigned& targetFieldID, const unsigned& draftItemID) noexcept {
      
    }
};

int main(int amountOfArguments, char* arrayOfArguments[]) {
  unsigned courseID, assignmentFieldID, assignmentNumber, draftItemID; 
  string moodleToken, assignmentFieldSearchPattern; 
  fs::path fileToUpload; json uploadResult; MoodleUploader uploader;

  //* Step 0: Verify + Assign Passed Arguments
  if (amountOfArguments != 6) {
    cerr << "Invalid Executable Envocation" << endl << "Execution MUST Look Like This: "
         << "./executable-title \"MOODLE_TOKEN\" COURSE_ID \"TARGET_FOR_FILE_UPLOAD\" ASSIGNMENT_NUMBER \"PATH_TO_UPLOAD_FILE\""
         << endl << "EXAMPLE 1: " << endl << "./moodle_test \"1esh4a43aehsa3hs\" 12345 \"Blatt\" 5 \"test.pdf\""
         << endl << "EXAMPLE 2: " << endl << "./moodle_test \"1esh4a43aehsa3hs\" 32431 \"Semesteraufgabe\" 3 \"another-file.pdf\"" << flush;
    return 1;
  }
  else {
    moodleToken = arrayOfArguments[1];
    try { courseID = stoi(arrayOfArguments[2]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    assignmentFieldSearchPattern = arrayOfArguments[3];
    try { assignmentNumber = stoi(arrayOfArguments[4]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[4] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[4] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    fileToUpload = arrayOfArguments[5];
    if (!fs::exists(fileToUpload)) {
      cerr << fileToUpload << " Does Not Exist" << endl;
      return 1;
    }
    cout << "Proceeding With: " << endl
         << "- Moodle Token: " << moodleToken
            << " | Identical To Passed Variable: " << (moodleToken == arrayOfArguments[1] ? "✅" : "❌") << endl
         << "- Course ID" << courseID
            << " | Identical To Passed Variable: " << (courseID == stoi(arrayOfArguments[2]) ? "✅" : "❌") << endl
         << "- Assignment Upload Target" << assignmentFieldSearchPattern << " " << assignmentNumber
            << " | Identical To Passed Variable: " << ((assignmentFieldSearchPattern + " " + to_string(assignmentNumber) == (static_cast<string>(arrayOfArguments[3]) + " " + static_cast<string>(arrayOfArguments[4]))) ? "✅" : "❌") << endl
         << "- File To Upload" << fileToUpload
            << " | Identical To Passed Variable: " << (fileToUpload.string() == arrayOfArguments[5] ? "✅" : "❌") << endl;
    try { uploader.setToken(moodleToken); }
    catch (const runtime_error& e) { 
      cerr << "Error Encountered While Setting Token: " << e.what() << endl; 
      return 1;
    }
  }

  //* Step 1: Upload File To Draft Area
  uploadResult = uploader.uploadFileToDraftArea(fileToUpload);
  if (uploadResult.contains("error")) {
    cerr << "\n ❌ Upload Failed" << endl;
    return 1;
  }
  try {
    if (!uploadResult.empty() && uploadResult.is_array()) {
      draftItemID = uploadResult.at(0).at("itemid").get<int>();
      cout << "\n ✅ File Upload To Draft Area Completed" << endl
           << "Draft Item Identification Number: " << draftItemID << endl;
    }
    else {
      cerr << "\n ❌ File Upload To Draft Area Failed" << endl
           << "Encountered Unexpected Response Format" << endl;
      return 1;
    }
  }
  catch (const json::exception& e) {
    cerr << "Failed To Parse Draft Item Identification: " << e.what() << endl;
    return 1;
  }

  //* Step 2: Find Upload Target (Course/Assignment/Target)
  assignmentFieldID = uploader.findTargetUploadField(courseID, assignmentFieldSearchPattern, assignmentNumber);
  if (assignmentFieldID == 0) {
    cerr << "\n❌ Could Not Find Upload Target Matching: " << assignmentFieldSearchPattern << endl;
    return 1;
  }

  //* Step 3: Attempt Upload + Handle Result
    try {
      if (uploader.attemptFileUpload(assignmentFieldID, draftItemID)) {
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