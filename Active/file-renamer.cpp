#include <iostream> // For output and input
#include <string> // For strings
#include <vector> // For vectors
#include <iomanip>
#include <thread>
#include <chrono>
#include <regex>
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <fstream> // For reading/writing to files
#include <filesystem> // For manipulating files
#include <sstream> // For reading/writing to strings

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;
namespace fs = filesystem;

int MAX_INT = numeric_limits<int>::max();
bool stopPromptingUser = false;

struct userConfig;
struct namingScheme;
class renamer;

void displayOptions(vector<string> options, string* highlightedTitle = nullptr, userConfig* config = nullptr);
bool validateInput(bool& stopPrompting, string userInput = "", int* largestAvaliableOption = nullptr, string expectedDataType = "int"); // TODO Create this function
string replaceSubstring (string& superString, const string& substringIndex, const string& replacementString, bool returnString = false);
void cleanInputBuffer();
void chastiseIncorrectInput(string dataType = "", int& maxValidNumber = MAX_INT);
vector<string> separatePaths(const string& input);

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

// classes/structs
struct namingScheme {
  vector<string> fileTypes;
  string courseTitle, pattern, example; // fileType divided by | in the string (if/when there are multiple)
};
struct userConfig {
  int selectedSchemeIndex = 0; // the first one by default
  string surname, studentID; // since @studentID will be used in the string  - i don't see a problem with storing it this way
  vector<namingScheme> schemes;

  string createTitle(int* consistentWorksheetNumber = nullptr){
    string finalTitle = schemes[selectedSchemeIndex].pattern, userInput; bool errorCaught = false;
    int amountOfFileTypes = schemes[selectedSchemeIndex].fileTypes.size(), backup = 1;
    if (finalTitle.find("[Matrikelnummer]") != string::npos) { replaceSubstring(finalTitle, "[Matrikelnummer]", studentID); }
    if (finalTitle.find("[Nachname]") != string::npos) { replaceSubstring(finalTitle, "[Nachname]", surname); }
    if (finalTitle.find("[AufgabenblattNr]") != string::npos) {
      if (consistentWorksheetNumber != nullptr) {
         userInput = to_string(*consistentWorksheetNumber);
      }
      else {
        do {
          if (stopPromptingUser) { return ""; }
          cout << "What Is The Number Of This Worksheet: ";
          cin >> userInput; // TODO add error checking function
          if (userInput == "q" || userInput == "exit") { return ""; }
          try { stoi(userInput); }  
          catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("string"); }; continue; } // want to check if it is an integer
        } while (!validateInput(stopPromptingUser, userInput, &MAX_INT));
      }
      replaceSubstring(finalTitle, "[AufgabenblattNr]", userInput);
    }
    if (finalTitle.find("[BeispielNr]") != string::npos) {
      do {
        if (stopPromptingUser) { return ""; }
        cout << "What Is The Number Of This Exercise: ";
        cin >> userInput; // TODO add error checking function
        if (userInput == "q" || userInput == "exit") { return ""; }
         try { stoi(userInput); }  
         catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("string"); }; continue; } // want to check if it is an integer
      } while (!validateInput(stopPromptingUser, userInput, &MAX_INT));
      replaceSubstring(finalTitle, "[BeispielNr]", userInput);  
    }
    userInput = "1"; // if there is only one choice do not even ask (index 0, so set to 1 since it is decrimented later)
    if (amountOfFileTypes > 1) {
      do {
        if (stopPromptingUser) { return ""; }
        cout << "Select File Type: " << endl;
        displayOptions(schemes[selectedSchemeIndex].fileTypes);
        cin >> userInput; // TODO add error checking function
        if (userInput == "q" || userInput == "exit") { return ""; }
        try { stoi(userInput); }  
        catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("string"); }; continue; } // want to check if it is an integer
      } while (!validateInput(stopPromptingUser, userInput, &amountOfFileTypes));
    } 
    try { stoi(userInput); } // double check for single extension type case
    catch (const exception&) { errorCaught = true; } 
    // TODO fix the double dot ..extension when renaming TGI
    replaceSubstring(finalTitle, "[Extension]", schemes[selectedSchemeIndex].fileTypes[(errorCaught ? backup : stoi(userInput)) - 1]); 
    return finalTitle;
  }
};
class renamer {
  private:
    userConfig config;
    const string CONFIG_DIRECTORY = ".renamer-config";
    const string CONFIG_FILE = "config.txt";
    const fs::path directoryPath = CONFIG_DIRECTORY;
    const fs::path configPath = directoryPath / CONFIG_FILE;

    void initialSetUp() {
      system("clear");
      if (!loadConfig()) {
        vector<string> tempStorage;  namingScheme transitionStorage; int amountOfSchemes;
        tempStorage.push_back(".jpg");
        tempStorage.push_back(".jpeg");
        tempStorage.push_back(".png");
        tempStorage.push_back(".pdf");
        tempStorage.push_back(".txt");
        transitionStorage.fileTypes = tempStorage;
        transitionStorage.courseTitle = "TGI";
        transitionStorage.pattern = "a[Matrikelnummer]_UE[AufgabenblattNr]_BSP[BeispielNr][Extension]";
        transitionStorage.example = "a12345678_UE1_BSP2.pdf";
        config.schemes.push_back({transitionStorage});
        transitionStorage = {};
        tempStorage.clear();
        tempStorage.push_back(".PDF");
        transitionStorage.fileTypes = tempStorage;
        transitionStorage.courseTitle = "MGI";
        transitionStorage.pattern = "[Nachname]_[Matrikelnummer]_B[AufgabenblattNr]_A[BeispielNr][Extension]";
        transitionStorage.example = "Archimedes_31415926_B5_A3.PDF";
        config.schemes.push_back({transitionStorage});
        amountOfSchemes = config.schemes.size();
        // TODO Create a major validation loop
        bool correctSurname = false, correctStudentID = false, correctCourse = false;
        do {
          if (!correctSurname) {
            cout << "Insert Your Surname: ";
            cin >> config.surname; // TODO add error checking function
            if (validateInput(stopPromptingUser, config.surname, nullptr, "string")) { correctSurname = true; } else { chastiseIncorrectInput("string"); continue; } 
          } 
          if (!correctStudentID) {
            cout << "Insert StudentID: ";
            cin >> config.studentID; // TODO add error checking function
            try { stoi(config.studentID); }  
            catch (const exception&) { chastiseIncorrectInput("string"); continue; } // want to check if it is an integer
            if (validateInput(stopPromptingUser, config.studentID, &MAX_INT, "int")) { correctStudentID = true; } else { chastiseIncorrectInput("string"); continue; }
            tempStorage.clear();
            for (auto& course : config.schemes) {
              tempStorage.push_back(course.courseTitle);
            }
          }
          cout << "Select Course:" << endl;
          displayOptions(tempStorage, nullptr, nullptr);
          cin >> config.selectedSchemeIndex; // TODO add error checking function
          if (validateInput(stopPromptingUser, to_string(config.selectedSchemeIndex), &amountOfSchemes)) { correctCourse = true; } else { chastiseIncorrectInput("int", amountOfSchemes); continue;; }
        } while (!correctSurname || !correctStudentID || !correctCourse);
        if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--;  saveConfig();}
    }
  }
  public:
    renamer() {
      if(!fs::exists(configPath)) { initialSetUp(); }
      else { loadConfig(); }
      displayStartMenu();
    }
    void displayStartMenu() {
      system("clear");
      string userInput, tempTitle = "Automatic Worksheet Titler"; // currently works better if the length of the string is even 
      vector<string> options = {}; int amountOfOptions; stopPromptingUser = false;
        options.push_back("Rename Single File");
        options.push_back("Rename Multiple Files\n");
        options.push_back("Select Schema");
        options.push_back("Edit User Information\n");
        // options.push_back("Edit Avaliable Schema(s)"); // optional add later
        options.push_back("Delete Configuration File");
        options.push_back("Exit");
        amountOfOptions = options.size();
      do {
          displayOptions(options, &tempTitle, &config);
          cin >> userInput;
          if (userInput == "q" || userInput == "exit") { break; }
        } while (!validateInput(stopPromptingUser, userInput, &amountOfOptions));
      if (userInput == "q" || userInput == "exit") { processUserChoice(6); }
      else { processUserChoice(stoi(userInput)); }
      
    }
    void processUserChoice (int selectedOption) {
      //! Minimize (remove) specific variable initializations inside case statements ⬇️
      string userChoice, tempTitleStorage, pathInput, copy;
      switch (selectedOption) {
        case 1: {
          fs::path originalFilePath = {}, finalFilePath = {}; 
          //! Add "" for the path (during user input) manually does not work otherwise
          // TODO ⬆️ Figure out how to do that automatically
          do {
            system("clear");
            if (stopPromptingUser) { displayStartMenu(); return; } // TODO Verifty that this acually works/escapes the prompting
            cout << "Insert The Path To The File You Want To Rename: ";
            //! IMPORTANT: Troubleshoot how to error check + properly process
            getline(cin, pathInput); // cleanInputBuffer(); //! FIX, DOES NOT WORK
            pathInput.pop_back(); 
            copy = replaceSubstring(pathInput, "\\", "", true); originalFilePath = copy; // avoiding string corruption
cout << "DEBUG: originalFilePath content = " << originalFilePath << endl;
cout << "DEBUG: Checking path existence..." << endl;
cout << "DEBUG: pathInput/copy = " << pathInput << endl << copy << endl; 
cout << "DEBUG: originalFilePath = " << originalFilePath << endl;
cout << "DEBUG: fs::exists(originalFilePath) = " << fs::exists(originalFilePath) << endl;

// Try to get info about the path
try {
  auto status = fs::status(originalFilePath);
  cout << "DEBUG: fs::status succeeded" << endl;
  cout << "DEBUG: is_regular_file = " << fs::is_regular_file(originalFilePath) << endl;
} catch (const exception& e) {
  cout << "DEBUG: fs::status exception: " << e.what() << endl;
}

// Also check the parent directory
cout << "DEBUG: parent path = " << originalFilePath.parent_path() << endl;
cout << "DEBUG: parent exists = " << fs::exists(originalFilePath.parent_path()) << endl;
cout << "DEBUG: filename = " << originalFilePath.filename() << endl;
this_thread::sleep_for(chrono::seconds(2));
            //! IMPORTANT: Troubleshoot how to error check + properly process
          } while(!validateInput(stopPromptingUser, pathInput, nullptr, "path"));
          tempTitleStorage = config.createTitle();
          if (tempTitleStorage.empty()) { displayStartMenu(); return; }
          finalFilePath = originalFilePath.parent_path() / tempTitleStorage;
          try { fs::rename(originalFilePath, finalFilePath); }
          catch(const std::exception& error) { // TODO Fix infinite loop and input blocking after error
            cout << "\nERROR Incorrect Path Formatting" << endl;
            std::cerr << error.what() << endl;
            this_thread::sleep_for(chrono::seconds(2));
            displayStartMenu();
            return;
          }
        break; } //? {} required for some reason
        case 2: {
          // multiple file rename
          int fileAmount, worsheetNumber; bool correctFileAmount = false, correctWorksheetNumber = false, correctFilePaths = false;
          vector<fs::path> originalFilePaths, finalFilePaths; string filePath;
          do {
            system("clear");
            if (stopPromptingUser) { return; }
            if (!correctFileAmount) {
              cout << "How Many Files Do You Want To Rename: ";
              cin >> userChoice;
              if (validateInput(stopPromptingUser, userChoice, &MAX_INT)) { correctFileAmount = true; }  
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("int", MAX_INT); continue; } 
              }
              if (stoi(userChoice) == 1) { processUserChoice(1); }
              originalFilePaths.resize(stoi(userChoice)); finalFilePaths.resize(stoi(userChoice));
              fileAmount = stoi(userChoice);
            }
            cout << "What Is The Number Of This Worksheet: ";
            cin >> userChoice;
            if (validateInput(stopPromptingUser, userChoice, &MAX_INT)) { correctWorksheetNumber = true; } 
            else {
              if (stopPromptingUser) { displayStartMenu(); return; } 
              else { chastiseIncorrectInput("int", MAX_INT); continue; } 
            }
            worsheetNumber = stoi(userChoice);
            cout << "Drag All Of The Files You Want To Rename Here: ";
            // cin.ignore();
            getline(cin, userChoice);

            // Parse paths using regex
            vector<string> parsedPaths = separatePaths(userChoice);

            // DEBUG
            cout << "DEBUG: Input string: " << userChoice << endl;
            cout << "DEBUG: Parsed " << parsedPaths.size() << " paths" << endl;
            for (int i = 0; i < parsedPaths.size(); i++) {
              cout << "DEBUG: Path " << i << ": " << parsedPaths[i] << endl;
              cout << "DEBUG: Exists? " << fs::exists(parsedPaths[i]) << endl;
            }
            this_thread::sleep_for(chrono::seconds(3));

            // Validate that we got the right number of files
            if (parsedPaths.size() == fileAmount && !parsedPaths[0].empty() && fs::exists(parsedPaths[0])) {
              correctFilePaths = true;
            } else {
              if (stopPromptingUser) { displayStartMenu(); return; } 
              else { chastiseIncorrectInput("path"); continue; } 
            }

            // Assign parsed paths
            for (int i = 0; i < fileAmount && i < parsedPaths.size(); i++) {
              originalFilePaths[i] = parsedPaths[i];
            }
          } while(!correctFileAmount || !correctWorksheetNumber || !correctFilePaths);

            for (int i = 0; i < fileAmount; i++) {
              do {
                system("clear");
                if (stopPromptingUser) { displayStartMenu(); return; }
                cout << (i == (fileAmount - 1) ? ("Rename The Last File ⬇️") : ("Files Left To Rename: " + to_string(fileAmount - i))) << endl;
                cout << "Worksheet Number: " << worsheetNumber << endl;
                cout << endl << "Current File Path #" << (i + 1) << ": " << endl
                    << originalFilePaths[i] << endl << endl;
                tempTitleStorage = config.createTitle(&worsheetNumber);
                if (tempTitleStorage.empty()) { displayStartMenu(); return; }
                finalFilePaths[i] = originalFilePaths[i].parent_path() / tempTitleStorage;
                  try { fs::rename(originalFilePaths[i], finalFilePaths[i]);  break; }
                  catch(const std::exception& error) {
                    cout << "\nERROR Incorrect Path Formatting" << endl;
                    std::cerr << error.what() << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    displayStartMenu();
                    return;
                  } 
              }
            }
          /*  deprecated, ignore
          for (int i = 0; i < fileAmount; i++) {
            do {
              system("clear");
              if (stopPromptingUser) { displayStartMenu(); return; } // TODO Verifty that this acually works/escapes the prompting
              cout << (i == (fileAmount - 1) ? ("Rename The Last File ⬇️") : ("Files Left To Rename: " + to_string(fileAmount - i))) << endl;
              cout << "Worksheet Number: " << userChoice << endl;
              cout << endl << "Insert The Path To File #" << (i + 1) << ": ";
              cin >> originalFilePaths[i]; // TODO add error checking function
            } while(!validateInput(stopPromptingUser, originalFilePaths[i].string(), nullptr, "path")); 
            tempStorage = stoi(userChoice);
            tempTitleStorage = config.createTitle(&tempStorage);
            if (tempTitleStorage.empty()) { displayStartMenu(); return; }
            finalFilePaths[i] = originalFilePaths[i].parent_path() / tempTitleStorage;
            try { fs::rename(originalFilePaths[i], finalFilePaths[i]); }
            catch(const std::exception& error) { // TODO Fix infinite loop and input blocking after error
              cout << "\nERROR Incorrect Path Formatting" << endl;
              std::cerr << error.what() << endl;
              this_thread::sleep_for(chrono::seconds(2));
              displayStartMenu();
              return;
            }
          }
          */
          /* //? if you want to collect all file paths and then rename them separately use two separate loops
          for (int i = 0; i < originalFilePaths.size(); i++) {
            finalFilePaths[i] = originalFilePaths[i].parent_path() / config.createTitle(userChoice);
            fs::rename(originalFilePath[i], finalFilePath[i]);
          }
          */

        break; }
        case 3: {
          //! modularize + remove duplication ↕️
          vector<string> tempStorage; int amonutOfSchemes = config.schemes.size();
          for (auto& course : config.schemes) {
          tempStorage.push_back(course.courseTitle);
          }
          do {
            system("clear"); // TODO replace all used 'system("clear")' (as a function)
            cout << "Select Course:" << endl;
            displayOptions(tempStorage, nullptr, nullptr);
            cin >> config.selectedSchemeIndex; // TODO add error checking function
            // if (cin.fail()) { cleanInputBuffer();  continue; }
          } while(!validateInput(stopPromptingUser, to_string(config.selectedSchemeIndex), &amonutOfSchemes));
          if (stopPromptingUser) { return; }
          if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--; saveConfig(); }
        break; } //? {} required for some reason
        case 4: {
          // edit user information
          bool correctSurname = false, correctStudentID = false; string newSurname, newStudentID;
          do {
            system("clear");
            if (!correctSurname) {
              cout << "The Current Surname Saved Is: " << config.surname << endl
                  << "Change To: ";
              cin >> newSurname; // TODO add error checking function
              if (validateInput(stopPromptingUser, newSurname, nullptr, "string")) { correctSurname = true; }  
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("string"); continue; } 
              }
            }
            cout << "The Current StudentID Saved Is: " << config.studentID << endl
               << "Change To: ";
            cin >> newStudentID; // TODO add error checking function
            if (validateInput(stopPromptingUser, newStudentID, nullptr, "string")) { correctStudentID = true; }  
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("string"); continue; } 
              }
          } while (!correctSurname || !correctStudentID);
          saveConfig();
        break; }
        case 5: {
          // TODO add request confirmation before deleting
          system("clear");
          cout << "Are you sure you want to delete your configuration? (yes/no): ";
          string confirm;
          cin >> confirm;
          if (confirm != "yes") { displayStartMenu(); return; }
          config.surname.clear();
          config.studentID.clear();
          config.schemes.clear();
          config.selectedSchemeIndex = 0;
          fs::remove(configPath);
          initialSetUp();
        break; } //? {} required for some reason
        case 6:
        return;
        default: {
          // TODO add error checking response
        break; }
      displayStartMenu();
      return;
    }
    void saveConfig() {
      if (!(fs::exists(directoryPath) && fs::is_directory(directoryPath))) { fs::create_directories(directoryPath); }
      fstream cachedConfig(configPath, ios::out | ios::trunc);
      if (!(cachedConfig.is_open())) { cerr << "\nERROR: Failed To Open File: " << configPath << endl; }
      cachedConfig << "--START--" << endl
                   << config.surname << endl
                   << config.studentID << endl
                   << config.selectedSchemeIndex << endl;
      for (auto& data : config.schemes) {
        cachedConfig << "----" << endl
                     << data.courseTitle << endl
                     << data.pattern << endl
                     << data.example << endl;
                     for (int i = 0; i < data.fileTypes.size(); i++) {
                        cachedConfig << data.fileTypes[i] << ((i < data.fileTypes.size() - 1) ? "|" : "");
                        if (i == data.fileTypes.size() - 1) {
                          cachedConfig << endl;
                        }
                      }
      }
      cachedConfig << "--END--" << endl;
    }
    bool loadConfig () {
      // read from the file and push into the info vector, return false if file does not exist
      if (!fs::exists(configPath)) { return false; }
      ifstream cachedConfig(configPath);
      int lineCount = 0, schemeIndexCount = 0;
      namingScheme tempBundle;
      string lineContent;
      if (!cachedConfig.is_open()) { cerr << "\nERROR: Failed To Open File: " << configPath << endl; return false; }
      // delete saved information
        config.surname.clear();
        config.schemes.clear();
        config.studentID.clear();
      while (getline(cachedConfig, lineContent)) { // TODO add error checking function
        if (lineContent.empty() || lineContent == "----" || lineContent == "--START--" || lineContent == "--END--") { continue; }
        if (lineCount < 3) {
          switch (lineCount) {
            case 0:
              config.surname = lineContent;
              break;
            case 1:
              config.studentID = lineContent;
              break;
            case 2:
              try { config.selectedSchemeIndex = stoi(lineContent); }
              catch (const exception& error) {
                cerr << error.what() << endl;
                cout << "\nERROR: During String to Integer Conversion. Setting To 1st Avaliable Scheme\n" << endl;
                config.selectedSchemeIndex = 0;
              }
              break;
            default:
              cerr << "\nERROR: Incorrect File Reading During Scheme Extraction" << endl;
              return false;
          }
        }
        else {
          schemeIndexCount = (lineCount - 3) % 4;
          switch (schemeIndexCount) {
            case 0:
              tempBundle = {}; // reset the data bundle
              tempBundle.courseTitle = lineContent;
              break;
            case 1:
              tempBundle.pattern = lineContent;
              break;
            case 2:
              tempBundle.example = lineContent;
              break;
              case 3: { 
                  //! FIX FOR MULTIPLE LINES
                stringstream tempStorage(lineContent);
                string token = "";
                while (getline(tempStorage, token, '|')) {
                  tempBundle.fileTypes.push_back(token);
                }
                config.schemes.push_back(tempBundle); // save the data bundle
                break; 
              }
            default:
              cerr << "\nERROR: Incorrect File Reading During Scheme Extraction" << endl;
              return false;
          }
        }
        lineCount++;
      }
      return true;
    }
};

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

// functions
void displayOptions(vector<string> options, string* highlightedTitle, userConfig* config){
  if (highlightedTitle != nullptr) {
    string padding, spaces;
    for (int i = 0; i < highlightedTitle->length(); i++) {
      padding += "══";
      if (i % 2 == 0) { spaces += " "; } // aproximated dynamic scaling (tweak later)
    }
    if (highlightedTitle->length() % 2 != 0) { //! fix this (sign corruption)
      padding.pop_back(); //! here
      spaces.pop_back();
    }
    cout << setw((highlightedTitle->length()) * 0.5) << '\n' // aproximated dynamic scaling (tweak later)
         << "╔" << padding << "╗" << endl
         << "║" << spaces << *highlightedTitle << spaces << "║" << endl
         << "╚" << padding << "╝" << endl;
  }
  if (config != nullptr) {
    cout << "Surname: " << config->surname << endl
         << "StudentID: " << config->studentID << endl
         << "Selected Schema: " << config->schemes[config->selectedSchemeIndex].courseTitle << '\n' << endl;
  }
  for (int i = 1; i <= options.size(); i++) {
    cout << "[ " << i << " ] " << options[i - 1] << endl;
  }
  cout << "\n→ Choice: ";
}
string replaceSubstring (string& superString, const string& stringToReplace, const string& replacementString, bool returnString) {
  if (superString.empty() || stringToReplace.empty()) { return ""; }
  int positionCount = 0;
  while ((positionCount = superString.find(stringToReplace, positionCount)) != string::npos) {
    superString.replace(positionCount, (replacementString.empty() ? 1 : stringToReplace.length()), replacementString);
    positionCount += (replacementString.empty() ? 1 : replacementString.length());
  }
  return returnString ? superString : "";
}
void cleanInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void chastiseIncorrectInput(string dataType, int& maxValidInput) {
    cleanInputBuffer();
    system("clear");
    cout << "Please ";
    if (dataType == "int") { cout << "Select Insert A Number In Allowed Range: " << "(0–" << maxValidInput << ")";}
    else if (dataType == "string") { cout << "Do Not Use Forbidden Characters"; }
    else if (dataType == "path") { cout << "Insert A Path To An Existing File"; }
    else { cout << "Insert A Valid Input"; }
    cout << endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
  }
bool validateInput(bool& stopPrompting, string userInput, int* largestAvaliableOption, string expectedDataType){
  bool successfulInput = true; int integerInput;
  if (userInput == "exit" || userInput == "q") { stopPrompting = true; successfulInput = false; }
  else if (userInput.empty()) { successfulInput = false; }
  else if (expectedDataType == "int") {
    try { integerInput = stoi(userInput); }
    catch (const exception& error) {
      cerr << error.what() << endl;
      cout << "\nERROR: During String to Integer Conversion, While Validating Input" << endl;
    }
    if (userInput.empty() || largestAvaliableOption == nullptr) { cerr << "\nERROR: Function Called Without Specifying (Integer) Arguments" << endl; }
    else if (integerInput < 0 || integerInput > *largestAvaliableOption) { successfulInput = false; }
  }
  else if (expectedDataType == "string") {
    if (userInput.empty()) { cerr << "\nERROR: Function Called Without Specifying (String) Arguments" << endl; }
    else if (userInput.find('\\') != string::npos || userInput.find('\'') != string::npos || userInput.find('\"') != string::npos) { successfulInput = false; }
  }
  else if (expectedDataType == "path") {
    //! validate here + fix the "" requirement
    fs::path chosenPath(userInput);
    if (!fs::exists(chosenPath)) { successfulInput = false; }
  }
  else { cerr << "\nERROR: Unedfined Data Type During Input Validation" << endl; successfulInput = false; }
  if (!successfulInput && !stopPrompting) { chastiseIncorrectInput(expectedDataType, MAX_INT); } // might want to add cleanInputBuffer() here
  return successfulInput;
}
vector<string> separatePaths(const string& input) {
  vector<string> paths; string result = input;
  //? Regex: find dot followed by 2-5 letters (extensions), then capture until end of line or next space
  regex pathPattern(R"(([^ ]*\.[a-zA-Z]{2,5})(?:\s|$))"); smatch match;
  while (regex_search(result, match, pathPattern)) {
    string path = match[1].str();
    replaceSubstring(path, "\\", "");
    paths.push_back(path);
    result = match.suffix();
  }
  return paths;
}


//!------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () {
  system("clear");
  renamer instance;
  system("clear");
  return 0;
}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
0. 🚧 Fix bugs in renaming process
  0.0. ✅ infinite loop after exiting ("exit" or "q") in case 2 (multiple rename)
  0.1. ✅ infinite loop after catching an error
  0.2. 🚧 incorrect input reading if not inside ""
1. ✅ Add an input verifier function
2. ✅ Add a possibility to exit at EVERY cin (q/exit) function check
  2.1. ✅ for strings
  2.2. ✅ for integers
3. 🚧 Work through all comments
 3.1 🚧 Fix multiline rename
4. ❌ Minimize variable usage
5. ❌ Minimize code repition (functions)
*/