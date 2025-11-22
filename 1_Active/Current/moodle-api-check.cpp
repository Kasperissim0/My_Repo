#include <iostream>
#include <iomanip>
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
static const unsigned TOKEN_MIN_LENGTH = 16, TOKEN_MAX_LENGTH = 64, REQUIRED_ARGUMENT_AMOUNT = 6;
 
static size_t writeCallback(void* newContent, size_t elementSize, size_t amountOfElements, void* userData) {
  string* responseString = static_cast<string*>(userData);
  size_t totalBytesRecieved = elementSize * amountOfElements;
  responseString->append(static_cast<char*>(newContent), totalBytesRecieved);
  return totalBytesRecieved;
}

struct AssignmentInfo {
  unsigned id;
  string name, courseName;

  void display(int index) const {
    cout << " - [ " << index << " ] " << left << setw(50) << name << " (Course: " << courseName << ", ID: " << id << ")" << endl;
  }
};
struct AssignmentData {
  fs::path file;
  struct Information {
    string searchPattern, assignmentIdentifier, fullSearchPattern;
    unsigned courseID, assignmentNumber;
    void constructFullSearchPattern() {
      // clog << endl << "Start Values: " << endl
      //      << "- fullSearchPattern: " << fullSearchPattern << endl
      //      << "- assignmentNumber: " << assignmentNumber << endl
      //      << "- assignmentIdentifier: " << assignmentIdentifier << endl << endl;
      fullSearchPattern = searchPattern + " ";
      if (!assignmentIdentifier.empty() && to_string(assignmentNumber) != assignmentIdentifier) fullSearchPattern += assignmentIdentifier;
      else fullSearchPattern += to_string(assignmentNumber);
      // clog << endl << "End Values: " << endl
      //      << "- fullSearchPattern: " << fullSearchPattern << endl
      //      << "- assignmentNumber: " << assignmentNumber << endl
      //      << "- assignmentIdentifier: " << assignmentIdentifier << endl << endl;
    }
  } info; 
  struct UploadData {
    unsigned targetFieldID, draftItemID;
  } upload;
  bool verifyAssignment(char* originalInputs[], const string& token) {
    bool incorrectAssigmentsMade = false; vector<string> emojis; const unsigned labelWidth = 40, valueWidth = 50;
    string cleanedFilePath = [&]{
      string temp(originalInputs[5]);
      temp.erase(remove(temp.begin(), temp.end(), '\\'), temp.end());
      return temp;
    }();

    for (size_t i = 0; i < REQUIRED_ARGUMENT_AMOUNT; ++i) emojis.push_back((i == 0 ? "" : "✅"));
    if (token != string(originalInputs[1])) { incorrectAssigmentsMade = true; emojis.at(1) = "❌"; }
    if (to_string(info.courseID) != string(originalInputs[2])) { incorrectAssigmentsMade = true; emojis.at(2) = "❌"; }
    if (info.fullSearchPattern != (string(originalInputs[3]) + " " + string(originalInputs[4]))) { incorrectAssigmentsMade = true; emojis.at(3) = "❌"; }
    if (AssignmentData::file.string() != cleanedFilePath) { incorrectAssigmentsMade = true; emojis.at(4) = "❌"; }

    cout << "\n                  === STEP 0: Assigning Variables ===" << endl << "Proceeding With: " << endl;
    cout << left << setw(labelWidth) << "- Moodle Token: " << setw(valueWidth) << token 
         << " | Identical To Passed Variable: " << emojis.at(1) << endl;
    cout << left << setw(labelWidth) << "- Course ID: " << setw(valueWidth) << info.courseID 
         << " | Identical To Passed Variable: " << emojis.at(2) << endl;
    cout << left << setw(labelWidth) << "- Assignment Upload Target: " << setw(valueWidth) << info.fullSearchPattern 
         << " | Identical To Passed Variable: " << emojis.at(3) << endl;
    cout << left << setw(labelWidth) << "- File To Upload: " << setw(valueWidth) << file.filename()
         << " | Identical To Passed Variable: " << emojis.at(4) << endl;
    if (file.filename().string() != file.string()) cout << "Full File Path: " << file << endl;
    return !incorrectAssigmentsMade;
  }
};
class MoodleUploader {
  private:
    const string URL = MOODLE_URL;
    string authorizationToken, apiRequest;

    AssignmentData assignment;
    CURL* curl; CURLcode responseStatusCode; curl_mime* form; curl_mimepart* field;
    string responseContent; json parsedResponse; 
    bool gotSuccessfulStatusCode() {
      responseStatusCode = curl_easy_perform(curl);
      if (responseStatusCode != CURLE_OK) {
        cerr << "\n❌ REQUEST FAILED: Got Bad Response Code, Cannot Proceed - " << curl_easy_strerror(responseStatusCode) << endl;
        fullCurlCleanup();
        return false;
      }
      return true;
    }
    bool establishCurlConnection() {
      curl = curl_easy_init();
      if (!curl) {
        cerr << "❌ Failed To Initialize 'curl' Connection" << endl;
        return false;
      }
      return true;
    }
    void cleanUpCurlConnection() {
      curl_easy_cleanup(curl);
    }
    void cleanUpCurlForm() {
      curl_mime_free(form);
    }
    void fullCurlCleanup() {
      cleanUpCurlConnection();
      cleanUpCurlForm();
    }
    public:
    MoodleUploader(const string& tempValue = "") { 
      if (tempValue != "") throw runtime_error("Set Token Using Setter Function"); 
      else                 this->authorizationToken = tempValue;
    }
    void setConfiguration(AssignmentData& data, const string& token) {
      // TODO Add Checking Before Setting
      assignment = data;
      data.info.constructFullSearchPattern();
      setToken(token);
    }
    void setToken(const string& passedToken) {
      unsigned length = passedToken.length();
      if (authorizationToken.empty()) cout << "Setting Token For The First Time" << endl;
      else cout << "Resetting Token From: \"" << authorizationToken << "\" To: \"" << passedToken << "\"" << endl;
      if (passedToken.empty())            throw runtime_error("Passed Token Is Empty");
      else if (length < TOKEN_MIN_LENGTH) throw runtime_error("Passed Token Does Not Match Length Specification: Too Short - " + to_string(length));
      else if (length > TOKEN_MAX_LENGTH) throw runtime_error("Passed Token Does Not Match Length Specification: Too Long - " + to_string(length)); 
      else                                this->authorizationToken = passedToken;
      cout << "\n ✅ Token Set Successfully: "; for (const auto& elem: authorizationToken) cout << "X"; cout << endl; 
    }
    json uploadFileToDraftArea() noexcept {
      string destinationURLAdress = URL + UPLOAD_URL, tempStorage;

      cout << "\n                  === STEP 1: Uploading File ===" << endl
           << "File: " << assignment.file << endl;

      if (!establishCurlConnection()) return json::parse("{\"error\": \"curl init failed\"}");
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
          curl_mime_name(field, "filename"); tempStorage = assignment.file.filename().string();
          curl_mime_data(field, tempStorage.c_str(), CURL_ZERO_TERMINATED);
        field = curl_mime_addpart(form);
          curl_mime_name(field, "file"); tempStorage = assignment.file.string();
          curl_mime_filedata(field, tempStorage.c_str());
      // Set URL to send request to
      curl_easy_setopt(curl, CURLOPT_URL, destinationURLAdress.c_str());
       // Attach multipart form
      curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
      // Set callback function (where response data goes)
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      // Set pointer to response string (callback will fill this)
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContent);

      if (!gotSuccessfulStatusCode()) return json::parse("{\"error\": \"upload failed\"}");
      fullCurlCleanup();
      cout << "Raw Response From API: " << endl << responseContent << endl << "\n                  === STEP 1.5: Parsing Response ===" << endl;

      try { parsedResponse = json::parse(responseContent); return parsedResponse; }
      catch (const json::parse_error& e) {
        cerr << "ERROR: Failed to parse JSON - " << e.what() << endl;
        return json::parse("{\"error\": \"json parse failed\", \"raw\": \"" + responseContent + "\"}");
      }
    }
    unsigned findTargetUploadField() noexcept {
      vector<AssignmentInfo> allAssignments, patternMatches;
      string patternInLowerCase, nameInLowerCase; int padding = 68 - 32 - assignment.info.searchPattern.length();

      cout << "\n                  === STEP 2: Finding Assignment ===" << endl
           << "Course ID: " << assignment.info.courseID << endl
           << "Search Pattern: \"" << assignment.info.searchPattern << " X" << endl
           << "Specific Entry: \"" << assignment.info.fullSearchPattern << "\"" << endl;

      if (!establishCurlConnection()) return 0;
      apiRequest = URL + API_URL + "?" + "wstoken=" + authorizationToken 
                                                       + "&wsfunction=mod_assign_get_assignments" 
                                                       + "&moodlewsrestformat=json" 
                                                       + "&courseids[0]=" + to_string(assignment.info.courseID);
      curl_easy_setopt(curl, CURLOPT_URL, apiRequest.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContent);
      
      if (!gotSuccessfulStatusCode()) return 0;
      cleanUpCurlConnection(); 
      cout << "Raw API Response:" << endl << responseContent << endl << "\n                  === STEP 2.5: Searching For Match ===" << endl;

      try {
        parsedResponse = json::parse(responseContent);
        if (!parsedResponse.contains("courses") || !parsedResponse["courses"].is_array()) {
          cerr << "\n ❌ERROR: Unexpected Response Format - Course Array Is Absent" << endl;
          return 0;
        }
        
        for (const auto& course : parsedResponse["courses"]) {
          if (!course.contains("assignments")) { cerr << "⚠️ Course (" << course << ") Has No Assignments Field" << endl; continue; }
          
          for (const auto& assignmentJSON : course["assignments"]) {
            AssignmentInfo info;
              info.id = assignmentJSON["id"].get<unsigned>();
              info.name = assignmentJSON["name"].get<string>();
              info.courseName = (course.contains("fullname") ? course["fullname"].get<string>() : "Unknown Course");
            allAssignments.push_back(info);
          }
        }
        cout << "\n✅ Found " << allAssignments.size() << "Total Assignments" << endl;
      }
      catch (const json::parse_error& e) {
        cerr << "ERROR: JSON parsing failed - " << e.what() << endl;
        return 0;
      }
      cout << "\n                  === STEP 2.5: Filtering Fetched Assignments ===" << endl
           << "- By Pattern: \"" << assignment.info.searchPattern << "\"" << endl;

      patternInLowerCase = assignment.info.searchPattern; transform(patternInLowerCase.begin(), patternInLowerCase.end(), patternInLowerCase.begin(), ::tolower);
      for (const auto& assignmentInfo : allAssignments) {
        nameInLowerCase = assignmentInfo.name; transform(nameInLowerCase.begin(), nameInLowerCase.end(), nameInLowerCase.begin(), ::tolower);
        if (nameInLowerCase.find(patternInLowerCase) != string::npos) patternMatches.push_back(assignmentInfo);
      }
      if (patternMatches.empty()) {
        cerr << "\n❌ No Assignments Found Matching Pattern \"" << assignment.info.searchPattern << "\"" << endl << "Here Were The Checked Options:" << endl;
        for (size_t i = 0; i < allAssignments.size(); ++i) allAssignments.at(i).display(i+1);
        return 0;
      }

      cout << "\n╔════════════════════════════════════════════════════════════════════╗" << endl
           << "║  UPLOAD OPTIONS (matching \"" << assignment.info.searchPattern << "\")";
      for (int i = 0; i < padding; i++) cout << " ";
      cout << "║" << endl
           << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    for (size_t i = 0; i < patternMatches.size(); ++i) patternMatches[i].display(i + 1);
    cout << endl;

    cout << "--- Searching for Exact Match: \"" << assignment.info.fullSearchPattern << "\" ---" << endl;
    patternInLowerCase = assignment.info.fullSearchPattern; transform(patternInLowerCase.begin(), patternInLowerCase.end(), patternInLowerCase.begin(), ::tolower); 
    for (const auto& assignmentInfo : patternMatches) {
      nameInLowerCase = assignmentInfo.name; transform(nameInLowerCase.begin(), nameInLowerCase.end(), nameInLowerCase.begin(), ::tolower);
      if (nameInLowerCase.find(patternInLowerCase) != string::npos) {
        cout << "\n✅ EXACT MATCH FOUND!" << endl
             << " - Assignment: \"" << assignmentInfo.name << "\"" << endl
             << " - ID: " << assignmentInfo.id << endl
             << " - Course: \"" << assignmentInfo.courseName << "\"" << endl;
      return assignmentInfo.id;
      }
    }
    cout << "\n⚠️  No Exact Match Found, Trying Alternative Patterns..." << endl
         << "Attempt 1: Using Alternative fullSearchPattern Construction: String <--> Number";
    string alternativePattern = assignment.info.searchPattern + " " ;
    if (assignment.info.fullSearchPattern == (alternativePattern + assignment.info.assignmentIdentifier)) alternativePattern += to_string(assignment.info.assignmentNumber);
    else if (assignment.info.fullSearchPattern == (alternativePattern + to_string(assignment.info.assignmentNumber))) alternativePattern += assignment.info.assignmentIdentifier;
    else { cerr << "\n❌ ERROR: Exception Encountered Constructing Alternative Search Pattern" << endl; return 0; }
    string alternativePatterninLowerCase = alternativePattern; transform(alternativePatterninLowerCase.begin(), alternativePatterninLowerCase.end(), alternativePatterninLowerCase.begin(), ::tolower);
    for (const auto& assignmentInfo : patternMatches) {
      nameInLowerCase = assignmentInfo.name; transform(nameInLowerCase.begin(), nameInLowerCase.end(), nameInLowerCase.begin(), ::tolower);
      if (nameInLowerCase.find(alternativePatterninLowerCase) != string::npos) {
        cout << "\n✅ ALTERNATIVE MATCH FOUND (After String <--> Number Switch)!" << endl
             << " - Assignment: \"" << assignmentInfo.name << "\"" << endl
             << " - ID: " << assignmentInfo.id << endl
             << " - Course: \"" << assignmentInfo.courseName << "\"" << endl;
        return assignmentInfo.id;
      }
    }
    cout << "\n⚠️  No Exact Match Found, Trying Alternative Patterns..." << endl
         << "Attempt 2: Using Both fullSearchPattern Construction: Without Spaces";
    string compactPattern1 = assignment.info.fullSearchPattern, compactPattern2 = alternativePattern;
           compactPattern1.erase(remove(assignment.info.fullSearchPattern.begin(), assignment.info.fullSearchPattern.end(), ' '), assignment.info.fullSearchPattern.end());
           compactPattern2.erase(remove(alternativePattern.begin(), alternativePattern.end(), ' '), alternativePattern.end()); 
    string compactPatternLower1 = compactPattern1, compactPatternLower2 = compactPattern2; 
    transform(compactPatternLower1.begin(), compactPatternLower1.end(), compactPatternLower1.begin(), ::tolower);
    transform(compactPatternLower2.begin(), compactPatternLower2.end(), compactPatternLower2.begin(), ::tolower);
    for (const auto& assignmentInfo : patternMatches) {
      nameInLowerCase = assignmentInfo.name; transform(nameInLowerCase.begin(), nameInLowerCase.end(), nameInLowerCase.begin(), ::tolower);
      if (nameInLowerCase.find(compactPatternLower1) != string::npos || nameInLowerCase.find(compactPatternLower2) != string::npos) {
        cout << "\n✅ ALTERNATIVE MATCH FOUND (No Space)!" << endl
             << " - Assignment: \"" << assignmentInfo.name << "\"" << endl
             << " - ID: " << assignmentInfo.id << endl
             << " - Course: \"" << assignmentInfo.courseName << "\"" << endl;
        return assignmentInfo.id;
      }
    }
  cerr << "\n❌ Could Not Find Exact Match For: \"" << assignment.info.fullSearchPattern << "\"" << endl
       << "\nAvailable Options (shown above):" << endl
       << "Please Verify:" << endl
       << "  1. Assignment Identifier Is Correct" << endl
       << "  2. Assignment Exists in Moodle" << endl
       << "  3. Pattern Matches Assignment Name Format" << endl;
  return 0;
}
    bool attemptFileUpload() noexcept {

      cout << "\n                  === STEP 3: Submitting Assignment ===" << endl
           << "Assignment ID: " << assignment.upload.targetFieldID << endl
           << "Draft Item ID: " << assignment.upload.draftItemID << endl;

      if (!establishCurlConnection()) return false;
      apiRequest = URL + API_URL + "?" + "wstoken=" + authorizationToken
                                                       + "&wsfunction=mod_assign_save_submission"
                                                       + "&moodlewsrestformat=json"
                                                       + "&assignmentid=" + to_string(assignment.upload.targetFieldID)
                                                       + "&plugindata[files_filemanager]=" + to_string(assignment.upload.draftItemID)
                                                       + "&plugindata[onlinetext_editor][text]="
                                                       + "&plugindata[onlinetext_editor][format]=1";
      curl_easy_setopt(curl, CURLOPT_URL, apiRequest.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContent);

      if (!gotSuccessfulStatusCode()) return false;
      cleanUpCurlConnection();
      cout << "Raw Submission Response: " << endl << responseContent << endl;

      try {
        parsedResponse = json::parse(responseContent);
        
        if (parsedResponse.contains("exception") || parsedResponse.contains("error")) {
          cerr << "\n ❌ ERROR: Moodle Returned an Error:" << endl;
          cerr << "- Code: " << parsedResponse["errorcode"] << endl;
          cerr << "- Message: " << parsedResponse["message"] << endl;
          return false;
        }
        else {
          cout << "\n✅ SUCCESS: Submission Successful!" << endl;
          return true;
        }
      }
      catch (const json::parse_error& e) {
        if (responseContent.empty() || responseContent == "null" || responseContent == "[]" || responseContent == "") {
          cout << "\n✅ SUCCESS: Submission Successful (Empty Response)!" << endl;
          return true;
        }
        else {
          cerr << "\n ❌ ERROR: Failed to Parse Response - " << e.what() << endl;
          return false;
        }
      }
    }
};

int main(int amountOfArguments, char* arrayOfArguments[]) {
  AssignmentData assignment; MoodleUploader uploader;
  string moodleToken; json uploadResult; 

  system("clear");

  //* Step 0: Verify + Assign Passed Arguments
  if (amountOfArguments != REQUIRED_ARGUMENT_AMOUNT) {
    cerr << " ❌ ERORR: Invalid Executable Envocation" << endl << "Execution MUST Look Like This: " << endl
         << "- 0. ./executable-name" << endl
         << "- 1. \"MOODLE_TOKEN\"" << endl
         << "- 2. COURSE_ID" << endl
         << "- 3. \"TARGET_FOR_FILE_UPLOAD\"" << endl
         << "- 4. ASSIGNMENT_NUMBER\\\"ASSIGNMENT_IDENTIFIER\"" << endl
         << "- 5. \"PATH_TO_UPLOAD_FILE\"" << endl
         << "FULL: " << "./a \"1\" 2 \"3\" 4\\\"4\" \"5\"" << endl
         << endl << " - EXAMPLE 1: " << endl << "./moodle-api-check \"1esh4a432esh2ash2av5aehsa3hs\" 12345 \"Blatt\" 5 \"test.pdf\""
         << endl << " - EXAMPLE 2: " << endl << "./moodle-api-check \"1esh25he245ah4a54a43aehsa3hs\" 63554 \"Exercise -\" \"Automata\" \"some-file.pdf\"" 
         << endl << " - EXAMPLE 3: " << endl << "./moodle-api-check \"1esh25he245ah4a54a43aehsa3hs\" 32431 \"Semesteraufgabe\" 3 \"another-file.pdf\"" << endl;
    return 1;
  }
  else {
    moodleToken = arrayOfArguments[1];
    try { assignment.info.courseID = stoi(arrayOfArguments[2]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[2] << "\" Into An Integer: " << e.what() << endl; 
      return 1;
    }
    assignment.info.searchPattern = arrayOfArguments[3];
    try { assignment.info.assignmentNumber = stoi(arrayOfArguments[4]); }
    catch (const invalid_argument& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[4] << "\" Into An Integer: " << e.what() << endl;  // return 1;
    }
    catch (const out_of_range& e) {
      cerr << "Unable To Convert \"" << arrayOfArguments[4] << "\" Into An Integer: " << e.what() << endl;  // return 1;
    }
    if (to_string(assignment.info.assignmentNumber) != string(arrayOfArguments[4])) {
      assignment.info.assignmentIdentifier = string(arrayOfArguments[4]);
      cout << "Truncation Encountered By String -> Integer Conversion, Using String For Better Accuracy" << endl
           << "- Using: \"" << assignment.info.searchPattern << " " << assignment.info.assignmentIdentifier << "\"" << endl
           << "- Instead Of: \"" << assignment.info.searchPattern << " " << assignment.info.assignmentNumber << "\"" << endl;
    }
    // clog << "Path Value Before Cleaning: " << string(arrayOfArguments[5]) << endl;
    assignment.file = [&]{
      string temp(arrayOfArguments[5]);
      temp.erase(remove(temp.begin(), temp.end(), '\\'), temp.end());
      return temp;
    }();
    // clog << "Path Value After Cleaning: " << assignment.file.string() << endl;
    if (!fs::exists(assignment.file)) {
      cerr << assignment.file << " Does Not Exist" << endl;
      return 1;
    }
    try { uploader.setConfiguration(assignment, moodleToken); }
    catch (const runtime_error& e) { 
      cerr << "Error Encountered While Setting Token: " << e.what() << endl; 
      return 1;
    }
    if (!assignment.verifyAssignment(arrayOfArguments, moodleToken)) {
      cerr << "\n❌ Mistake Made While Assigning Variables" << endl;
      return 1;
    }
  }

  //* Step 1: Upload File To Draft Area
  uploadResult = uploader.uploadFileToDraftArea();
  if (uploadResult.contains("error")) {
    cerr << "\n ❌ UPLOAD FAILED: " << endl << "- Error Type: " << uploadResult["error"] << endl << "- Error Reason: " << uploadResult["errorcode"] << endl;
    return 1;
  }
  try {
    if (!uploadResult.empty() && uploadResult.is_array()) {
      assignment.upload.draftItemID = uploadResult.at(0).at("itemid").get<int>();
      cout << "\n ✅ File Upload To Draft Area Completed" << endl
           << "Draft Item Identification Number: " << assignment.upload.draftItemID << endl;
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
  assignment.upload.targetFieldID = uploader.findTargetUploadField();
  if (assignment.upload.targetFieldID == 0) {
    cerr << "\n❌ Could Not Find Upload Target Matching: " << assignment.info.fullSearchPattern << endl;
    return 1;
  }

  //* Step 3: Attempt Upload + Handle Result
    try {
      if (uploader.attemptFileUpload()) {
        cout << "\n╔════════════════════════════════════════╗" << endl
             << "║               ✅ SUCCESS!               ║" << endl
             << "╚════════════════════════════════════════╝" << endl
             << "File successfully submitted to Moodle!" << endl
             << "- Upload URL: https://moodle.univie.ac.at/mod/assign/view.php?id=" << assignment.upload.targetFieldID << endl
             << "- File Uploaded: " << assignment.file.filename() << endl;
        return 0;
      }
      else {
        cerr << "\n╔════════════════════════════════════════╗" << endl
             << "║               ❌ FAILURE!               ║" << endl
             << "╚════════════════════════════════════════╝" << endl;
        return 1;
      }
    }
    catch (const runtime_error& e){
      cerr << e.what() << endl;
      return 1;
    }
}