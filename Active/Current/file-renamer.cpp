#include <iostream> // For output and input
#include <string> // For strings
#include <vector> // For vectors
#include <iomanip> // for clearing the screen
#include <thread> // for time manipulation
#include <chrono> // for time manipulation
#include <regex> // for pattern manipulation
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

void displayOptions(vector<string> options = {"Yes", "No"}, string* highlightedTitle = nullptr, userConfig* config = nullptr);
bool validateInput(bool& stopPrompting, string userInput = "", int* largestAvaliableOption = nullptr, string expectedDataType = "int");
string replaceSubstring (string& superString, const string& substringIndex, const string& replacementString, bool returnString = false);
void cleanInputBuffer();
void chastiseIncorrectInput(string dataType = "", int& maxValidNumber = MAX_INT);
vector<string> separatePaths(const string& input);
void clearScreen ();
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
struct namingScheme {
  vector<string> fileTypes;
  string courseTitle, pattern, example; // fileType divided by | in the string (if/when there are multiple)
};
struct userConfig {
  int selectedSchemeIndex = 0; // the first one by default
  string surname, studentID; // since @studentID will be used in the string  - i don't see a problem with storing it this way
  vector<namingScheme> schemes;

  string createTitle(int* consistentWorksheetNumber = nullptr,int* consistentFileExtension = nullptr, int* exerciseNumberRange = nullptr){
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
          cin >> userInput;
          if (userInput == "q" || userInput == "exit") { return ""; }
          try { stoi(userInput); }  
          catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("int", MAX_INT); }; continue; } // want to check if it is an integer
        } while (!validateInput(stopPromptingUser, userInput, &MAX_INT));
      }
      replaceSubstring(finalTitle, "[AufgabenblattNr]", userInput);
    }
    if (finalTitle.find("[BeispielNr]") != string::npos) {
      do {
        if (stopPromptingUser) { return ""; }
        cout << "What Is The Number Of This Exercise" << (exerciseNumberRange == nullptr ? ": " : (" (1-" + to_string(*exerciseNumberRange) + "): "));
        cin >> userInput;
        if (userInput == "q" || userInput == "exit") { return ""; }
         try { stoi(userInput); }  
         catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("int", MAX_INT); }; continue; } // want to check if it is an integer
      } while (!validateInput(stopPromptingUser, userInput, &MAX_INT));
      replaceSubstring(finalTitle, "[BeispielNr]", userInput);  
    }
    userInput = "1"; // if there is only one choice do not even ask (index 0, so set to 1 since it is decrimented later)
    if (amountOfFileTypes > 1 && consistentFileExtension == nullptr) {
      do {
        if (stopPromptingUser) { return ""; }
        cout << "Select File Type: " << endl;
        displayOptions(schemes[selectedSchemeIndex].fileTypes);
        cin >> userInput;
        if (userInput == "q" || userInput == "exit") { return ""; }
        try { stoi(userInput); }  
        catch (const exception&) { if (!stopPromptingUser) { chastiseIncorrectInput("int", amountOfFileTypes); }; continue; } // want to check if it is an integer
      } while (!validateInput(stopPromptingUser, userInput, &amountOfFileTypes));
    try { stoi(userInput); } // double check for single extension type case
    catch (const exception&) { errorCaught = true; } 
    }
    // TODO fix the double dot ..extension when renaming TGI AND the extension not getting appended
    if (consistentFileExtension != nullptr) { replaceSubstring(finalTitle, "[Extension]", schemes[selectedSchemeIndex].fileTypes[*consistentFileExtension]); }
    else { replaceSubstring(finalTitle, "[Extension]", schemes[selectedSchemeIndex].fileTypes[(errorCaught ? backup : stoi(userInput)) - 1]); }
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
      clearScreen();
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
        bool correctSurname = false, correctStudentID = false, correctCourse = false, incorrectInput = false;
        do {
          if (!correctSurname) {
            cout << "Insert Your Surname: ";
            cin >> config.surname;
            try { stoi(config.surname); incorrectInput = true; } 
            catch (const exception& e) { // want to check that it is NOT an integer
              if (validateInput(stopPromptingUser, config.surname, nullptr, "string") && !incorrectInput) { correctSurname = true; }
              else { chastiseIncorrectInput("string"); continue; } } 
          } 
          if (!correctStudentID) {
            cout << "Insert StudentID: ";
            cin >> config.studentID;
            try { stoi(config.studentID); }  
            catch (const exception& e) { chastiseIncorrectInput("string"); continue; } // want to check if it is an integer
            if (validateInput(stopPromptingUser, config.studentID, &MAX_INT, "int")) { correctStudentID = true; } else { chastiseIncorrectInput("string"); continue; }
            tempStorage.clear();
            for (auto& course : config.schemes) {
              tempStorage.push_back(course.courseTitle);
            }
          }
          cout << "Select Course:" << endl;
          displayOptions(tempStorage, nullptr, nullptr);
          cin >> config.selectedSchemeIndex;
          if (validateInput(stopPromptingUser, to_string(config.selectedSchemeIndex), &amountOfSchemes)) { correctCourse = true; } 
          else { chastiseIncorrectInput("int", amountOfSchemes); continue; }
        } while (!correctSurname || !correctStudentID || !correctCourse);
        if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--;  saveConfig();}
    }
  }
    void processUserChoice (int selectedOption) {
      string userChoice, tempTitleStorage, pathInput, cleanedPath;
      switch (selectedOption) {
        case 1: {
          fs::path originalFilePath = {}, finalFilePath = {}; 
          do {
            clearScreen();
            if (stopPromptingUser) { displayStartMenu(); return; }
            cout << "Insert The Path To The File You Want To Rename: ";
            cleanInputBuffer();
            getline(cin, pathInput);
            if (pathInput.back() == ' ') {  pathInput.pop_back(); }
            cleanedPath = replaceSubstring(pathInput, "\\ ", " ", true); // avoiding string corruption
          } while(!validateInput(stopPromptingUser, pathInput, nullptr, "path"));
          originalFilePath = cleanedPath;
          tempTitleStorage = config.createTitle();
          if (tempTitleStorage.empty()) { displayStartMenu(); return; }
          finalFilePath = originalFilePath.parent_path() / tempTitleStorage;
          try { fs::rename(originalFilePath, finalFilePath); }
          catch(const std::exception& error) {
            cout << "\nERROR Incorrect Path Formatting" << endl;
            std::cerr << error.what() << endl;
            this_thread::sleep_for(chrono::seconds(2));
            displayStartMenu();
            return;
          }
        break; } //? {} required for some reason
        case 2: {
          // multiple file rename
          int fileAmount, worsheetNumber, exerciseNumber, fileExtension, maxExtensionAmount = config.schemes[config.selectedSchemeIndex].fileTypes.size(); 
          bool correctFileAmount = false, correctWorksheetNumber = false, correctFilePaths = false, correctExerciseNumber = false, correctFileExtension = false, consistentFileExtension = true;
          vector<fs::path> originalFilePaths, finalFilePaths; string filePath;
          do {
            clearScreen();
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
            if (!correctWorksheetNumber) {
              cout << "What Is The Number Of This Worksheet: ";
              cin >> userChoice;
              if (validateInput(stopPromptingUser, userChoice, &MAX_INT)) { correctWorksheetNumber = true; } 
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("int", MAX_INT); continue; } 
              }
              worsheetNumber = stoi(userChoice);
            }
            // TODO Add an option to have a consistent file extension type (to not reprompt during the title creation)
            //! 1. do you want a consistent file extension
            //! 2. choose it
            if (maxExtensionAmount != 1) {
              if (consistentFileExtension) {
                int maxOptions = 2; // store value for pointer
                //! N. 1
                cout << "Do You Want All Your Files To Have The Same Extension?" << endl;
                displayOptions();
                cin >> userChoice;
                // error check here, options 1 - yes, 2 - no.
                if (validateInput(stopPromptingUser, userChoice, &maxOptions)) { consistentFileExtension = true; } 
                else {
                  if (stopPromptingUser) { displayStartMenu(); return; } 
                  else { chastiseIncorrectInput("int", maxExtensionAmount); continue; } 
                }
                if (userChoice != "1") { consistentFileExtension = false; correctFileExtension = true; }
              }
              if (!correctFileExtension && consistentFileExtension) { // only runs if answer to the previous block was 1 (positive)
                //! N. 2
                cout << "Select File Type: " << endl;
                displayOptions(config.schemes[config.selectedSchemeIndex].fileTypes);
                cin >> userChoice;
                if (validateInput(stopPromptingUser, userChoice, &maxExtensionAmount)) { correctFileExtension = true; } 
                else {
                  if (stopPromptingUser) { displayStartMenu(); return; } 
                  else { chastiseIncorrectInput("int", maxExtensionAmount); continue; } 
                }
                fileExtension = stoi(userChoice);
                fileExtension--;
              }
            }
            else { fileExtension = 0; correctFileExtension = true; consistentFileExtension = true; }

            cout << "Drag All Of The Files You Want To Rename Here: ";
            cleanInputBuffer();
            getline(cin, userChoice);
            vector<string> parsedPaths = separatePaths(userChoice);
            if (parsedPaths.size() == fileAmount) { correctFilePaths = true; } 
            else { cout << "\nERROR: Expected " << fileAmount << " files, but found " << parsedPaths.size() << ".\n" << endl; correctFilePaths = false; }
            for (int i = 0; i < parsedPaths.size(); i++) {
              if (parsedPaths[i].empty() || !fs::exists(parsedPaths[i])) { correctFilePaths = false; } 
              else if (stopPromptingUser) { displayStartMenu(); return; }
            }
            for (int i = 0; i < fileAmount && i < parsedPaths.size(); i++) {
              originalFilePaths[i] = parsedPaths[i];
            }
          } while(!correctFileAmount || !correctWorksheetNumber || !correctFilePaths || !correctFileExtension);
            for (int i = 0; i < fileAmount; i++) {
              clearScreen();
              if (stopPromptingUser) { displayStartMenu(); return; }
              cout << (i == (fileAmount - 1) ? ("Rename The Last File ⬇️") : ("Files Left To Rename: " + to_string(fileAmount - i))) << endl;
              cout << "Worksheet Number: " << worsheetNumber << endl;
              cout << endl << "Current File Path #" << (i + 1) << ": " << endl
                    << originalFilePaths[i] << endl << endl;
              tempTitleStorage = config.createTitle(&worsheetNumber, (consistentFileExtension ? &fileExtension : nullptr) , &fileAmount);
              if (tempTitleStorage.empty()) { displayStartMenu(); return; }
              finalFilePaths[i] = originalFilePaths[i].parent_path() / tempTitleStorage;
                try { fs::rename(originalFilePaths[i], finalFilePaths[i]); }
                catch(const std::exception& error) {
                  cout << "\nERROR Incorrect Path Formatting" << endl;
                  std::cerr << error.what() << endl;
                  this_thread::sleep_for(chrono::seconds(2));
                  displayStartMenu();
                  return;
                } 
            }
        break; }
        case 3: {
          vector<string> tempStorage; int amonutOfSchemes = config.schemes.size();
          for (auto& course : config.schemes) {
          tempStorage.push_back(course.courseTitle);
          }
          do {
            clearScreen(); // TODO replace all used 'system("clear")' (as a function)
            cout << "Select Course:" << endl;
            displayOptions(tempStorage, nullptr, nullptr);
            cin >> config.selectedSchemeIndex;
            // if (cin.fail()) { cleanInputBuffer();  continue; }
          } while(!validateInput(stopPromptingUser, to_string(config.selectedSchemeIndex), &amonutOfSchemes));
          if (stopPromptingUser) { return; }
          if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--; saveConfig(); }
        break; } //? {} required for some reason
        case 4: {
          bool correctSurname = false, correctStudentID = false; string newSurname, newStudentID;
          do {
            clearScreen();
            if (!correctSurname) {
              cout << "The Current Surname Saved Is: " << config.surname << endl
                  << "Change To: ";
              cin >> newSurname;
              if (validateInput(stopPromptingUser, newSurname, nullptr, "string")) { correctSurname = true; }  
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("string"); continue; } 
              }
            }
            cout << "The Current StudentID Saved Is: " << config.studentID << endl
               << "Change To: ";
            cin >> newStudentID;
            if (validateInput(stopPromptingUser, newStudentID, nullptr, "string")) { correctStudentID = true; }  
              else {
                if (stopPromptingUser) { displayStartMenu(); return; } 
                else { chastiseIncorrectInput("string"); continue; } 
              }
          } while (!correctSurname || !correctStudentID);
          saveConfig();
        break; }
        case 5: {
          clearScreen();
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
        default:
          // TODO Add error checking responses
        break;
      }
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
      if (!fs::exists(configPath)) { return false; }
      ifstream cachedConfig(configPath);
      int lineCount = 0, schemeIndexCount = 0;
      namingScheme tempBundle;
      string lineContent;
      if (!cachedConfig.is_open()) { cerr << "\nERROR: Failed To Open File: " << configPath << endl; return false; }
        config.surname.clear();
        config.schemes.clear();
        config.studentID.clear();
      while (getline(cachedConfig, lineContent)) {
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
              catch (const exception& error) { config.selectedSchemeIndex = 0; }
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
              tempBundle = {};
              tempBundle.courseTitle = lineContent;
              break;
            case 1:
              tempBundle.pattern = lineContent;
              break;
            case 2:
              tempBundle.example = lineContent;
              break;
              case 3: { 
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

  public:
    renamer() {
      if(!fs::exists(configPath)) { initialSetUp(); }
      else { loadConfig(); }
      displayStartMenu();
    }
    void displayStartMenu() {
      clearScreen();
      string userInput, tempTitle = "Automatic Worksheet Titler"; // currently works better if the length of the string is even 
      vector<string> options = {}; int amountOfOptions; stopPromptingUser = false;
        options.push_back("Rename Single File");
        options.push_back("Rename Multiple Files\n");
        options.push_back("Select Schema");
        options.push_back("Edit User Information\n");
        // options.push_back("Edit Avaliable Schema(s)"); //* optional add later
        // options.push_back("Add Additional Schema(s)"); //* optional add later
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
};

//!------------------------------------------------------------------------------------------------------------------------------------------------------------
void displayOptions(vector<string> options, string* highlightedTitle, userConfig* config){
  if (highlightedTitle != nullptr) {
    string padding, spaces;
    for (int i = 0; i < highlightedTitle->length(); i++) { 
      padding += "══";
      if (i % 2 == 0) { spaces += " "; } //  aproximated dynamic scaling
    } // TODO make dynamic scaling work for both even AND odd numbers
    if (highlightedTitle->length() % 2 != 0) {
      padding.pop_back();
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
  int positionCount = 0;
  if (superString.empty() || stringToReplace.empty()) { return ""; }
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
    // cleanInputBuffer(); // not always necessary, sometimes detrimental
    clearScreen();
    cout << "Please ";  
    if (dataType == "int") { cout << "Select Insert A Number In Allowed Range: " << "(1–" << maxValidInput << ")";}
    else if (dataType == "string") { cout << "Do Not Use Forbidden Characters"; }
    else if (dataType == "path") { cout << "Insert A Path To An Existing File"; }
    else { cout << "Insert A Valid Input"; }
    cout << endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen();
  }
bool validateInput(bool& stopPrompting, string userInput, int* largestAvaliableOption, string expectedDataType){
  bool successfulInput = true; int integerInput;
  if (userInput == "exit" || userInput == "q") { stopPrompting = true; successfulInput = false; }
  else if (userInput.empty()) { successfulInput = false; }
  else if (expectedDataType == "int") {
    try { integerInput = stoi(userInput); }
    catch (const exception& error) { successfulInput = false; }
    if (largestAvaliableOption == nullptr) { cerr << "\nERROR: Function Called Without Specifying (Integer) Arguments" << endl; successfulInput = false; }
    if (successfulInput) { if (integerInput < 0 || integerInput > *largestAvaliableOption) { successfulInput = false; } } // avoid accessing if stoi() failed
  }
  else if (expectedDataType == "string") {
    if (userInput.find('\\') != string::npos || userInput.find('\'') != string::npos || userInput.find('\"') != string::npos) { successfulInput = false; }
  }
  else if (expectedDataType == "path") {
    fs::path chosenPath(userInput);
    if (!fs::exists(chosenPath)) { successfulInput = false; }
  }
  else { cerr << "\nERROR: Unedfined Data Type During Input Validation" << endl; successfulInput = false; }
  if (!successfulInput && !stopPrompting) {
    if (largestAvaliableOption != nullptr) {
      chastiseIncorrectInput(expectedDataType, *largestAvaliableOption); // for integers
    } else {
      chastiseIncorrectInput(expectedDataType); // for string/path-(s)
    }
  }
  return successfulInput;
}
vector<string> separatePaths(const string& input) {
  vector<string> paths; string result = input;
  //? Regex: find dot followed by 2-5 letters (extensions), then capture until end of line or next space
  regex pathPattern(R"(([^ ]*(?:\\ |[^ ])*\.[a-zA-Z0-9]{2,5}))"); smatch match;
  while (regex_search(result, match, pathPattern)) {
    string path = match[1].str();
    replaceSubstring(path, "\\ ", " ");
    paths.push_back(path);
    result = match.suffix();
  }
  return paths;
}
void clearScreen () {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------
int main () {
  clearScreen();
  renamer instance;
  clearScreen();
  return 0;
}
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
  0. ✅ Fix bugs in renaming process
    0.0. ✅ infinite loop after exiting ("exit" or "q") in case 2 (multiple rename)
    0.1. ✅ infinite loop after catching an error
    0.2. ✅ incorrect input reading if not inside ""
  1. ✅ Add an input verifier function
  2. ✅ Add a possibility to exit at EVERY cin (q/exit) function check
    2.1. ✅ for strings
    2.2. ✅ for integers
  3. 🚧 Work through all comments
  3.1 ✅ Fix multiline rename
  4. ❌ Minimize variable usage
  5. ❌ Minimize code repition (functions)
    5.1. ❌ verification for "q" || "exit" as a function
  6. 🚧 Add cross platform compatibility 
*/