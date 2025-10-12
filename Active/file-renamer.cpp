#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <thread>
#include <chrono>
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <fstream> // For reading/writing to files
#include <filesystem> // For manipulating files
#include <sstream> // For reading/writing to strings
#include <SFML/Graphics.hpp> // For graphics

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;
namespace fs = filesystem;

const int MAX_INT = numeric_limits<int>::max();

struct userConfig;
struct namingScheme;
class renamer;

void displayOptions(vector<string> options, string* highlightedTitle = nullptr, userConfig* config = nullptr);
bool validateInput(int* integerInput = nullptr, int* largestAvaliableOption = nullptr, string expectedDataType = "int", string stringInput = "", bool& stopPrompting = false); // TODO Create this function
void replaceSubstring (string& superString, const string& substringIndex, const string& replacementString);
void cleanInputBuffer();
void chastiseIncorrectInput();

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
    string finalTitle = schemes[selectedSchemeIndex].pattern;
    int amountOfFileTypes = schemes[selectedSchemeIndex].fileTypes.size();
    int userInput;
    if (finalTitle.find("[Matrikelnummer]") != string::npos) { replaceSubstring(finalTitle, "[Matrikelnummer]", studentID); }
    if (finalTitle.find("[Nachname]") != string::npos) { replaceSubstring(finalTitle, "[Nachname]", surname); }
    if (finalTitle.find("[AufgabenblattNr]") != string::npos) {
      if (consistentWorksheetNumber != nullptr) {
         userInput = *consistentWorksheetNumber;
      }
      else {
        do {
          cout << "What Is The Number Of This Worksheet: ";
          cin >> userInput; // TODO add error checking function
        } while (!validateInput(&userInput, &MAX_INT));
      }
      replaceSubstring(finalTitle, "[AufgabenblattNr]", to_string(userInput));
    }
    if (finalTitle.find("[BeispielNr]") != string::npos) {
      do {
        cout << "What Is The Number Of This Exercise: ";
        cin >> userInput; // TODO add error checking function
      } while (!validateInput(&userInput, &MAX_INT));
      replaceSubstring(finalTitle, "[BeispielNr]", to_string(userInput));  
    }
    userInput = 1; // if there is only one choice do not even ask (index 0, so set to 1 since it is decrimented later)
    if (amountOfFileTypes > 1) {
      do {
        cout << "Select File Type: " << endl;
        displayOptions(schemes[selectedSchemeIndex].fileTypes);
        cin >> userInput; // TODO add error checking function
      } while (!validateInput(&userInput, &amountOfFileTypes));
    }
      // TODO fix the double dot ..extension when renaming TGI
      replaceSubstring(finalTitle, "[Extension]", schemes[selectedSchemeIndex].fileTypes[userInput - 1]); 
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
        vector<string> tempStorage;  namingScheme transitionStorage; int amountOfSchemes = config.schemes.size();
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
        // TODO Create a major validation loop
        bool correctSurname = false, correctStudentID = false, correctCourse = false;
        do {
          cout << "Insert Your Surname: ";
          cin >> config.surname; // TODO add error checking function
          if (validateInput(nullptr, nullptr, "string", config.surname)) { correctSurname = true; } else { chastiseIncorrectInput(); continue; }
          cout << "Insert StudentID: ";
          cin >> config.studentID; // TODO add error checking function
          if (validateInput(nullptr, nullptr, "string", config.studentID)) { correctStudentID = true; } else { chastiseIncorrectInput(); continue; }
          tempStorage.clear();
          for (auto& course : config.schemes) {
            tempStorage.push_back(course.courseTitle);
          }
          cout << "Select Course:" << endl;
          displayOptions(tempStorage, nullptr, nullptr);
          cin >> config.selectedSchemeIndex; // TODO add error checking function
          if (validateInput(&config.selectedSchemeIndex, &amountOfSchemes)) { correctCourse = true; } else { chastiseIncorrectInput(); continue; }
        } while (!correctSurname || !correctStudentID || !correctCourse);
        config.selectedSchemeIndex--;
        saveConfig();
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
      vector<string> options = {}; int userInput; int amountOfOptions = options.size();
      string tempTitle = "Automatic Worksheet Titler"; // currently works better if the length of the string is even
        options.push_back("Rename Single File");
        options.push_back("Rename Multiple Files\n");
        options.push_back("Select Schema");
        options.push_back("Edit User Information\n");
        // options.push_back("Edit Avaliable Schema(s)"); // optional add later
        options.push_back("Delete Configuration File");
        options.push_back("Exit");
      do {
          displayOptions(options, &tempTitle, &config);
          cin >> userInput; 
        } while (!validateInput(&userInput, &amountOfOptions));
      processUserChoice(userInput);
    }
    void processUserChoice (int selectedOption) {
      //! Minimize (remove) specific variable initializations inside case statements ⬇️
      int userChoice; bool stopPrompting = false;
      switch (selectedOption) {
        case 1: {
          fs::path originalFilePath = {}, finalFilePath = {};
          //! Add "" for the path (during user input) manually does not work otherwise
          // TODO ⬆️ Figure out how to do that automatically
          do {
            system("clear");
            if (stopPrompting) { cleanInputBuffer(); return; } // TODO Verifty that this acually works/escapes the prompting
            cout << "Insert The Path To The File You Want To Rename: ";
            //! IMPORTANT: Troubleshoot how to error check + properly process
            cin >> originalFilePath; // TODO add error checking function
            //! IMPORTANT: Troubleshoot how to error check + properly process
          } while(!validateInput(nullptr, nullptr, "path", to_string(originalFilePath), stopPrompting));
          finalFilePath = originalFilePath.parent_path() / config.createTitle();
          try { fs::rename(originalFilePath, finalFilePath); }
          catch(const std::exception& error) { // TODO Fix infinite loop and input blocking after error
            cout << "\nERROR Incorrect Path Formatting" << endl;
            std::cerr << error.what() << endl;
            this_thread::sleep_for(chrono::seconds(2));
            processUserChoice(1);
          }
        break; } //? {} required for some reason
        case 2: {
          // multiple file rename
          int fileAmount; bool correctFileAmount = false, correctWorksheetNumber = false;
          //! Add "" for the path (during user input) manually does not work otherwise
          // TODO ⬆️ Figure out how to do that automatically
          do {
            system("clear");
            cout << "How Many Files Do You Want To Rename: ";
            cin >> userChoice; // TODO add error checking function
            if (validateInput(&userChoice, &MAX_INT)) { correctFileAmount = true; } else { chastiseIncorrectInput(); continue; }
            if (userChoice == 1) { processUserChoice(1); }
            vector<fs::path> originalFilePaths(userChoice), finalFilePaths(userChoice);
            fileAmount = userChoice;
            cout << "What Is The Number Of This Worksheet: ";
            cin >> userChoice; // TODO add error checking function
            if (validateInput(&userChoice, &MAX_INT)) { correctWorksheetNumber = true; } else { chastiseIncorrectInput(); continue; }
          } while(!correctFileAmount || !correctWorksheetNumber);
          //! Change control flow: ⬇️
          /*
          1. input amount of files
          2. input worksheet number
          3. drag all files into terminal
          repeat for all files {
            4. display
              - remaining amount of files
              - worksheet number (constant)
              - current path (parse the concactenated string from step 3)
            5. input exercises number
            6. rename file
          }
          */
          for (int i = 0; i < fileAmount; i++) {
            do {
              system("clear");
              if (stopPrompting) { cleanInputBuffer(); return; } // TODO Verifty that this acually works/escapes the prompting
              cout << (i == (fileAmount - 1) ? ("Rename The Last File ⬇️") : ("Files Left To Rename: " + to_string(fileAmount - i))) << endl;
              cout << "Worksheet Number: " << userChoice << endl;
              cout << endl << "Insert The Path To File #" << (i + 1) << ": ";
              cin >> originalFilePaths[i]; // TODO add error checking function
            } while(!validateInput(nullptr, nullptr, "path", to_string(originalFilePaths[i]), stopPrompting)); 
            finalFilePaths[i] = originalFilePaths[i].parent_path() / config.createTitle(&userChoice);
            try { fs::rename(originalFilePaths[i], finalFilePaths[i]); }
            catch(const std::exception& error) { // TODO Fix infinite loop and input blocking after error
              cout << "\nERROR Incorrect Path Formatting" << endl;
              std::cerr << error.what() << endl;
              this_thread::sleep_for(chrono::seconds(2));
              processUserChoice(2);
            }
          }
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
          } while(!validateInput(&config.selectedSchemeIndex, &amonutOfSchemes));
          config.selectedSchemeIndex--;
          saveConfig();
        break; } //? {} required for some reason
        case 4: {
          // edit user information
          bool correctSurname = false, correctStudentID = false;
          do {
          cout << "The Current Surname Saved Is: " << config.surname << endl
               << "Change To: ";
          cin >> config.surname; // TODO add error checking function
          if (validateInput(nullptr, nullptr, "string", config.surname)) { correctSurname = true; } else { chastiseIncorrectInput(); continue; }
          cout << "The Current StudentID Saved Is: " << config.studentID << endl
               << "Change To: ";
          cin >> config.studentID; // TODO add error checking function
          if (validateInput(nullptr, nullptr, "string", config.studentID)) { correctStudentID = true; } else { chastiseIncorrectInput(); continue; }
          } while (!correctSurname || !correctStudentID);
          saveConfig();
        break; }
        case 5: {
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
          // TODO add error checking response
        break; }
      displayStartMenu();
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
void replaceSubstring (string& superString, const string& stringToReplace, const string& replacementString) {
  if (superString.empty() || stringToReplace.empty() || replacementString.empty()) { return; }
  int positionCount = 0;
  while ((positionCount = superString.find(stringToReplace, positionCount)) != string::npos) {
    superString.replace(positionCount, stringToReplace.length(), replacementString);
    positionCount += stringToReplace.length();
  }
}
void cleanInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void chastiseIncorrectInput() {
    cleanInputBuffer();
    system("clear");
    cout << setw(30) << "Please Insert A Valid Input" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
  }
bool validateInput(int integerInput, int largestAvaliableOption, string expectedDataType, string stringInput, bool& stopPrompting){
  bool successfulInput = false;
  if (expectedDataType == "int") {
    if (integerInput == numeric_limits<int>::max() || largestAvaliableOption == numeric_limits<int>::max()) { cerr << "\nERROR: Function Called Without Specifying (Integer) Arguments" << endl; }
    else if (cin.fail() || integerInput < 0 || integerInput > largestAvaliableOption) { chastiseIncorrectInput(); }
    else { successfulInput = true; }
  }
  else if (expectedDataType == "string") {
    if (stringInput.empty()) { cerr << "\nERROR: Function Called Without Specifying (String) Arguments" << endl; }
    else if (cin.fail() || stringInput.find('\\') != string::npos || stringInput.find('\'') != string::npos || stringInput.find('\"') != string::npos) { chastiseIncorrectInput(); }
    else if (stringInput == "exit" || stringInput == "q") { stopPrompting = true; } //! Figure out how to break out using this function
  }
  else if (expectedDataType == "path") {
    //! validate here + fix the "" requirement
    fs::path chosenPath(stringInput);
    //TODO here
  }
  else { cerr << "\nERROR: Unedfined Data Type During Input Validation" << endl; }
  return successfulInput;
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
  0.0. 🚧 infinite loop after exiting ("exit" or "q") in case 2 (multiple rename)
  0.1. ❌ infinite loop after catching an error
  0.2. ❌ incorrect input reading if not inside ""
1. 🚧 Add an input verifier function
2. 🚧 Add a possibility to exit at EVERY cin (q/exit) function check
3. ❌ Work through all comments
4. ❌ Minimize variable usage
5. ❌ Minimize code repition (functions)
*/