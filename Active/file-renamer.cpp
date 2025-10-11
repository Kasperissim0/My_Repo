#include <iostream> // For output and input
#include <iomanip> // For formatting output nicely
#include <string> // For strings
#include <vector> // For vectors
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <fstream> // For reading/writing to files
#include <filesystem> // For manipulating files
#include <sstream> // For reading/writing to strings
#include <SFML/Graphics.hpp> // For graphics

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;

struct userConfig;
struct namingScheme;
class renamer;

void displayOptions(vector<string> options, string* highlightedTitle = nullptr, userConfig* config = nullptr);
bool validateInput(); // TODO Create this function
void replaceSubstring (string& superString, const string& substringIndex, const string& replacementString);

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

// classes/structs
struct namingScheme {
  vector<string> fileTypes;
  string courseTitle, pattern, example, ; // fileType divided by | in the string (if/when there are multiple)
};

struct userConfig {
  int selectedSchemeIndex = 0; // the first one by default
  string surname, studentID; // since @studentID will be used in the string  - i don't see a problem with storing it this way
  vector<namingScheme> schemes;

  string createTitle() {
    string finalTitle = schemes[selectedSchemeIndex].pattern;
    int userInput;
    if (finalTitle.find("[Matrikelnummer]") != string::npos) { replaceSubstring(finalTitle, "[Matrikelnummer]", studentID); }
    if (finalTitle.find("[Nachname]") != string::npos) { replaceSubstring(finalTitle, "[Nachname]", surname); }
    if (finalTitle.find("[AufgabenblattNr]") != string::npos) {
      cout << endl << "What Is The Number Of This Worksheet: ";
      cin >> userInput; // TODO add error checking function
      replaceSubstring(finalTitle, "[AufgabenblattNr]", to_string(userInput));
      }
    if (finalTitle.find("[BeispielNr]") != string::npos) {
      cout << "What Is The Number Of This Exercise: ";
      cin >> userInput; // TODO add error checking function
      replaceSubstring(finalTitle, "[BeispielNr]", to_string(userInput));  
      }
    if (schemes[selectedSchemeIndex].fileTypes.find("|") != string::npos) {
      vector<string> fileTypeOptions;
      int chosenFileType;
      stringstream tempHelperStream(schemes[selectedSchemeIndex].fileTypes);
      string tempHelper;
      //! fill fileTypeOptions by going through schemes[selectedSchemeIndex].fileTypes and getting each type between the | pipes
      while (getline(tempHelperStream, tempHelper, '|')) {
        fileTypeOptions.push_back(tempHelper);
      }
      cout << "Select File Type: " << endl;
      displayOptions(fileTypeOptions);
      cin >> chosenFileType; // TODO add error checking function
      //TODO fix the double dot ..extension when renaming TGI
      replaceSubstring(finalTitle, "[Extension]", fileTypeOptions[chosenFileType - 1]); 
    }
    return finalTitle;
  }
};

class renamer {
  private:
    userConfig config;
    const string CONFIG_DIRECTORY = ".renamer-config";
    const string CONFIG_FILE = "config.txt";
    const filesystem::path directoryPath = CONFIG_DIRECTORY;
    const filesystem::path configPath = directoryPath / CONFIG_FILE;

    void initialSetUp() {
      system("clear");
      if (!loadConfig()) {
        vector<string> tempStorage;
        config.schemes.push_back({"TGI", "a[Matrikelnummer]_UE[AufgabenblattNr]_BSP[BeispielNr].[Extension]", "a12345678_UE1_BSP2.pdf", "jpg|jpeg|png|pdf|txt"});
        config.schemes.push_back({"MGI", "[Nachname]_[Matrikelnummer]_B[AufgabenblattNr]_A[BeispielNr].[Extension]", "Archimedes_31415926_B5_A3.PDF", "PDF"});
        cout << "Insert Your Surname: ";
        cin >> config.surname; // TODO add error checking function
        cout << "Insert StudentID: ";
        cin >> config.studentID; // TODO add error checking function
        for (auto& course : config.schemes) {
          tempStorage.push_back(course.courseTitle);
        }
        cout << "Select Course:" << endl;
        displayOptions(tempStorage, nullptr, nullptr);
        cin >> config.selectedSchemeIndex; // TODO add error checking function
        config.selectedSchemeIndex--;
        saveConfig();
      }
    }
  public:
    renamer() {
      if(!filesystem::exists(configPath)) { initialSetUp(); }
      else { loadConfig(); }
      displayStartMenu();
    }
    void displayStartMenu() {
      system("clear");    
      vector<string> options;
      string tempTitle = "Automatic Worksheet Titler"; // currently works better if the length of the string is even
        options.push_back("Rename Single File");
        // options.push_back("Rename Multiple Files"); //* add later
        options.push_back("Select Schema");
        // options.push_back("Edit User Information"); //* add later
        // options.push_back("Edit Avaliable Schema(s)"); // optional add later
        options.push_back("Delete Configuration File");
        options.push_back("Exit");
      displayOptions(options, &tempTitle, &config);
      processUserChoice();
    }
    void processUserChoice () {
      int userChoice;
      cin >> userChoice; // TODO add error checking function
      switch (userChoice) {
        case 1: {
          filesystem::path originalFilePath, finalFilePath;
          //! Add "" for the path (during user input) does not work otherwise
          system("clear");
          cout << "Insert The Path To The File You Want To Rename: ";
          cin >> originalFilePath; // TODO add error checking function
          finalFilePath = originalFilePath.parent_path() / config.createTitle();
          filesystem::rename(originalFilePath, finalFilePath);
        break; } //? {} required for some reason
        case 2: {
          //! modularize + remove duplication ↕️
          system("clear"); // TODO replace all used 'system("clear")' (as a function)
          vector<string> tempStorage;
          for (auto& course : config.schemes) {
          tempStorage.push_back(course.courseTitle);
          }
          cout << "Select Course:" << endl;
          displayOptions(tempStorage, nullptr, nullptr);
          cin >> config.selectedSchemeIndex; // TODO add error checking function
          config.selectedSchemeIndex--;
          saveConfig();
        break; } //? {} required for some reason
        case 3: {
          config.surname.clear();
          config.studentID.clear();
          config.schemes.clear();
          config.selectedSchemeIndex = 0;
          filesystem::remove(configPath);
          initialSetUp();
        break; } //? {} required for some reason
        case 4:
          return;
        default:
          // TODO add error checking response
        break;
      }
      displayStartMenu();
    }
    void saveConfig() {
      if (!(filesystem::exists(directoryPath) && filesystem::is_directory(directoryPath))) { filesystem::create_directories(directoryPath); }
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
                     << data.example << endl
                     << data.fileTypes << endl;
      }
      cachedConfig << "--END--" << endl;
    }
    bool loadConfig () {
      // read from the file and push into the info vector, return false if file does not exist
      if (!filesystem::exists(configPath)) { return false; }
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
              case 3:
              tempBundle.fileTypes = lineContent;
              config.schemes.push_back(tempBundle); // save the data bundle
              break;
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

//!------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () {
  system("clear");
  renamer instance;
  system("clear");
  return 0;
}

//!------------------------------------------------------------------------------------------------------------------------------------------------------------