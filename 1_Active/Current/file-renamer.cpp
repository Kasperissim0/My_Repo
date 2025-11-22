#include <iostream> // For output and input
#include <string> // For strings
#include <vector> // For vectors
#include <map> // For hash tables
#include <iomanip> // for clearing the screen
#include <thread> // for time manipulation
#include <chrono> // for time manipulation
#include <cstdlib> // For clearing the terminal
#include <limits> // For clearing the input buffer
#include <fstream> // For reading/writing to files
#include <filesystem> // For manipulating files
#include <sstream> // For reading/writing to strings
#include <curl/curl.h> // For http/api calls
#include <nlohmann/json.hpp> // For better organized config file
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
using namespace std;
namespace fs = filesystem;

const int MAX_INT = numeric_limits<int>::max();
bool stopPromptingUser = false;
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
//* Bundle Of Relevant Data For Each Course Template Type
struct NamingScheme;
//* User Information That Is Stored In Persistent File
  // + As Well As A Method For Creating The Final Title For The Rename
struct UserConfig;
//* The Object For The Terminal UI 
  // + Loads/Saves User Info
  // + Requests Input
  // + Executes Command Chosen
class Renamer;

//* Displays Options Given From A Vector Of Strings
  // + By Default Yes/No.
  // + Optional Arguments Allow To Add A Higlighted Title And Display @UserConfig Contents
void displayOptions(vector<string> options = {"Yes", "No"}, string* highlightedTitle = nullptr, UserConfig* config = nullptr, bool fileExensions = false);
//* Checks For A Valid Input Based On Passed Data Type("string"/"path"/"int")
  // + Modifies A Global Boolean Value(1st arg) 
  // + If Set To True - Means User Wants To Exit The Input Process
  // + Expects "int" By Default
bool validateInput(bool& stopPrompting, string userInput = "", const int* largestAvaliableOption = nullptr, string expectedDataType = "int");
//* Replaces A Substring(2nd arg) In The String Passed(1st arg) For A Different Passed String(3rd arg)
  // + If Specified Returns The Modified String
  // + By Default Returns ""
string replaceSubstring (string& superString, const string& stringToReplace, const string& replacementString, bool returnString = false);
//* Informs User Of Incorrect Input Based On The Data Type("string"/"path"/"int")
  // + And Requests A Valid Input
  // + Clears Screen After
void chastiseIncorrectInput(string dataType = "", const int& maxValidInput = MAX_INT);
//* Given A Single Concateneted String Of Paths Separates Them And Returns A Vector Of Individual Paths
  // + Escapes Illegal Charachters
vector<string> separatePaths(const string& input); // TODO Make Cross-OS Compatible (handle both / and \ based on OS)
//* Cross-OS Compatible Function For Clearing The Terminal
void clearScreen ();
//* Gets User Confirmation Whether To Erase An Existing File After Title Collision
  // + Appends String To File Title If Chosen (For Valid Rename Without Overwriting)
bool overwriteExistingFile(fs::path& file);
//* Returns A String (Path) After Having Replaced All Instances Of " " With "\ "
// + Necessary for Executing Command 'magick some\ folder/file \ 1.heic some\ folder/file \ 1.pdf'
string breakWhiteSpaces(string input);
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
struct NamingScheme {
  vector<string> fileTypes;
  string courseTitle, pattern, example; // fileType divided by | in the string (if/when there are multiple)
  unsigned short lastWorksheet;
};
struct UserConfig {
  private:
    enum PatternsToReplace {
      STUDENT_ID,
      SURNAME,
      NUMBER_OF_EXERCISE_SHEET,
      NUMBER_OF_PROBLEM,
      FILE_EXTENSION
    };
    map<PatternsToReplace, string> patternValues {
      {STUDENT_ID, "[Matrikelnummer]"},
      {SURNAME, "[Nachname]"},
      {NUMBER_OF_EXERCISE_SHEET, "[AufgabenblattNr]"},
      {NUMBER_OF_PROBLEM, "[BeispielNr]"},
      {FILE_EXTENSION, "[Extension]"}
    };
  
  public: 
    int selectedSchemeIndex = MAX_INT; // the first one by default
    string surname, studentID; // since @studentID will be used in the string  - i don't see a problem with storing it as a string instead of int
    vector<NamingScheme> schemes;

    string createTitle(int* consistentWorksheetNumber = nullptr,int* consistentFileExtension = nullptr, int* exerciseNumberRange = nullptr) {
      string finalTitle = schemes.at(selectedSchemeIndex).pattern, userInput; bool errorCaught = false;
      int amountOfFileTypes = schemes.at(selectedSchemeIndex).fileTypes.size(), backup = 1, tempStorage;
      if (finalTitle.find(patternValues[STUDENT_ID]) != string::npos) { replaceSubstring(finalTitle, patternValues[STUDENT_ID], studentID); }
      if (finalTitle.find(patternValues[SURNAME]) != string::npos) { replaceSubstring(finalTitle, patternValues[SURNAME], surname); }
      if (finalTitle.find(patternValues[NUMBER_OF_EXERCISE_SHEET]) != string::npos) {
        if (consistentWorksheetNumber != nullptr) {
          userInput = to_string(*consistentWorksheetNumber);
        }
        else {
          do {
            if (::stopPromptingUser) return "";
            cout << "What Is The Number Of This Worksheet: ";
            cin >> userInput;
            if (userInput == "q" || userInput == "exit") { return ""; }
            try { tempStorage = stoi(userInput); }  
            catch (const exception&) { if (!::stopPromptingUser) { chastiseIncorrectInput("int", MAX_INT); }; continue; } // want to check if it is an integer
          } while (!validateInput(::stopPromptingUser, userInput, &MAX_INT));
        }
        replaceSubstring(finalTitle, patternValues[NUMBER_OF_EXERCISE_SHEET], to_string(tempStorage));
      }
      if (finalTitle.find(patternValues[NUMBER_OF_PROBLEM]) != string::npos) {
        do {
          if (::stopPromptingUser) return "";
          cout << "What Is The Number Of This Exercise" << (exerciseNumberRange == nullptr ? ": " : (" (1-" + to_string(*exerciseNumberRange) + "): "));
          cin >> userInput;
          if (userInput == "q" || userInput == "exit") return "";
          try { tempStorage = stoi(userInput); }  
          catch (const exception&) { continue; } // want to check if it is an integer
        } while (!validateInput(::stopPromptingUser, userInput, &MAX_INT));
        replaceSubstring(finalTitle, patternValues[NUMBER_OF_PROBLEM], to_string(tempStorage));  
      }
      userInput = "1"; // if there is only one choice do not even ask (index 0, so set to 1 since it is decrimented later)
      if (amountOfFileTypes > 1 && consistentFileExtension == nullptr) {
        do {
          if (::stopPromptingUser) return "";
          cout << "Select File Type: " << endl;
          displayOptions(schemes.at(selectedSchemeIndex).fileTypes, nullptr, nullptr, true);
          cin >> userInput;
          if (userInput == "q" || userInput == "exit") return "";
          try { tempStorage = stoi(userInput); }  
          catch (const exception&) { if (!::stopPromptingUser) { chastiseIncorrectInput("int", amountOfFileTypes); }; continue; } // want to check if it is an integer
        } while (!validateInput(::stopPromptingUser, userInput, &amountOfFileTypes));
      try { tempStorage = stoi(userInput); } // double check for single extension type case
      catch (const exception&) { errorCaught = true; } 
      }
      if (consistentFileExtension != nullptr) { replaceSubstring(finalTitle, patternValues[FILE_EXTENSION], schemes.at(selectedSchemeIndex).fileTypes[*consistentFileExtension]); }
      else { replaceSubstring(finalTitle, patternValues[FILE_EXTENSION], schemes.at(selectedSchemeIndex).fileTypes[(errorCaught ? backup : tempStorage) - 1]); }
      return finalTitle;
    }
};
class Renamer {
  private:
    UserConfig config;
    const string CONFIG_DIRECTORY = ".renamer-config";
    const string CONFIG_FILE = "config.txt";
    const fs::path directoryPath = CONFIG_DIRECTORY;
    const fs::path configPath = directoryPath / CONFIG_FILE;

    enum MenuOptions {
      RENAME = 1,
      SWITCH_TO_DIFFERENT_SCHEMA,
      EDIT_USER_INFO,
      // EDIT_EXISTING_SCHEMA, //? optional add later
      // ADD_NEW_SCHEMA, //? optional add later
      DELETE_USER_CONFIG,
      EXIT_PROGRAMM
    }; 
    map<MenuOptions, string> optionValues {
      {RENAME, "Rename File(s)"},
      {SWITCH_TO_DIFFERENT_SCHEMA, "Select Schema"},
      {EDIT_USER_INFO, "Edit User Information\n"},
      // {EDIT_EXISTING_SCHEMA, "Edit Avaliable Schema(s)"},   //? optional add later
      // {ADD_NEW_SCHEMA, "Add Additional Schema(s)"},         //? optional add later
      {DELETE_USER_CONFIG, "Delete Configuration File"},
      {EXIT_PROGRAMM, "Exit"}
    };

    void initialSetUp() {
      clearScreen();
      if (!loadConfig()) {
        vector<string> tempStorage; int amountOfSchemes;
        bool correctSurname = false, correctStudentID = false, correctCourse = false, incorrectInput = false;

        updateConfig();
        amountOfSchemes = config.schemes.size();

        do {
          if (!correctSurname) {
            cout << "Insert Your Surname: ";
            cin >> config.surname;
            try { stoi(config.surname); incorrectInput = true; } 
            catch (const exception& e) { // want to check that it is NOT an integer
              if (validateInput(::stopPromptingUser, config.surname, nullptr, "string") && !incorrectInput) { correctSurname = true; }
              else { chastiseIncorrectInput("string"); continue; } } 
          } 
          if (!correctStudentID) {
            cout << "Insert StudentID: ";
            cin >> config.studentID;
            try { stoi(config.studentID); }  
            catch (const exception& e) { chastiseIncorrectInput("string"); continue; } // want to check if it is an integer
            if (validateInput(::stopPromptingUser, config.studentID, &MAX_INT, "int")) { correctStudentID = true; } else { chastiseIncorrectInput("string"); continue; }
            tempStorage.clear();
            for (auto& course : config.schemes) {
              tempStorage.push_back(course.courseTitle);
            }
          }
          cout << "Select Course:" << endl;
          displayOptions(tempStorage, nullptr, nullptr);
          cin >> config.selectedSchemeIndex;
          if (validateInput(::stopPromptingUser, to_string(config.selectedSchemeIndex), &amountOfSchemes)) { correctCourse = true; } 
          else { chastiseIncorrectInput("int", amountOfSchemes); continue; }
        } while (!correctSurname || !correctStudentID || !correctCourse);
        if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--;  saveConfig();}
    }
  }
    void processUserChoice(MenuOptions selectedOption) {
      string userChoice, tempTitleStorage, pathInput, cleanedPath;
      try { // Attempt To Process User Input, Catch Invalid Values
        switch (selectedOption) {
          case RENAME: { // TODO ADD .heic conversion using 'system("magick file.heic file.pdf")' in the command line
            vector<fs::path> originalFilePaths, finalFilePaths; vector<string> parsedPaths;
            int fileAmount, worksheetNumber, fileExtension, maxExtensionAmount, maxOptions;
            bool pathsInCorrectForm, consistentFileExtension;
            string userChoice, tempTitleStorage;

            while (true) {
              if (::stopPromptingUser) return;
              clearScreen();
              cout << "Drag The File(s) You Want To Rename Here: ";
              getline(cin >> ws, userChoice);
              if (userChoice == "q" || userChoice == "exit") { break; }

              parsedPaths = separatePaths(userChoice);
              
              pathsInCorrectForm = !parsedPaths.empty();
              for (const auto& p : parsedPaths) {
                  if (p.empty() || !fs::exists(p)) {
                      pathsInCorrectForm = false;
                      break;
                  }
              }

              if (pathsInCorrectForm) {
                  for (const auto& p : parsedPaths) {
                      originalFilePaths.push_back(p);
                  }
                  break; // Exit path input loop
              } else {
                  chastiseIncorrectInput("path");
              }
            }

            fileAmount = originalFilePaths.size();
            if (fileAmount == 0) break;

            // Handle single file case
            if (fileAmount == 1) {
                fs::path originalFilePath = originalFilePaths.at((fileAmount - 1));
                clearScreen();
                cout << "File: " << originalFilePath << endl << endl;

                tempTitleStorage = config.createTitle();
                if (tempTitleStorage.empty()) { break; } // User quit in createTitle
                fs::path finalFilePath = originalFilePath.parent_path() / tempTitleStorage;
                string command = "magick " + breakWhiteSpaces(originalFilePath.string()) + " " + breakWhiteSpaces(finalFilePath.string()) + " && rm " + breakWhiteSpaces(originalFilePath.string());
                // clog << command; this_thread::sleep_for(chrono::seconds(3));
                if (!fs::exists(finalFilePath) || (fs::exists(finalFilePath) && overwriteExistingFile(finalFilePath))) {
                  // TODO make sure q (i.e. ::stopPromptingUser) exits without hitting the 'else' block
                  if (::stopPromptingUser) return;
                  try { ((originalFilePath.string().find("heic") != string::npos) ? (void)system(command.c_str()) : fs::rename(originalFilePath, finalFilePath)); } 
                  catch(const std::exception& error) {
                      cout << "\nERROR Incorrect Path Formatting" << endl;
                      std::cerr << error.what() << endl;
                      this_thread::sleep_for(chrono::seconds(2));
                  }
                }
                else {
                  clearScreen();
                  cout << "Rename Of File " << finalFilePath.filename() << " Cancelled." << endl;
                  this_thread::sleep_for(chrono::seconds(2));
                }
              break; // Back to main menu
            }

            // We have multiple files. Get other info.
            while (true) {
                if (::stopPromptingUser) return;
                clearScreen();
                cout << fileAmount << " files to be renamed." << endl;
                for (size_t i = 0; i < originalFilePaths.size(); ++i) { cout << "[ " << (i + 1) << " ] " << originalFilePaths.at(i) << endl; }
                cout << "What Is The Number Of This Worksheet: ";
                cin >> userChoice;
                if (validateInput(::stopPromptingUser, userChoice, &MAX_INT)) {
                    worksheetNumber = stoi(userChoice);
                    break;
                }
            }

            fileExtension = 0;
            consistentFileExtension = false;
            maxExtensionAmount = config.schemes.at(config.selectedSchemeIndex).fileTypes.size();

            if (maxExtensionAmount > 1) {
                while (true) {
                    if (::stopPromptingUser) break;
                    clearScreen();
                    cout << "Do You Want All Your Files To Have The Same Extension?" << endl;
                    displayOptions();
                    maxOptions = 2;
                    cin >> userChoice;
                    if (validateInput(::stopPromptingUser, userChoice, &maxOptions)) {
                        if (userChoice == "1") {
                            consistentFileExtension = true;
                            // Now ask for which extension
                            while (true) {
                                if (::stopPromptingUser) break;
                                clearScreen();
                                cout << "Select File Type: " << endl;
                                displayOptions(config.schemes.at(config.selectedSchemeIndex).fileTypes, nullptr, nullptr, true);
                                cin >> userChoice;
                                if (validateInput(::stopPromptingUser, userChoice, &maxExtensionAmount)) {
                                    fileExtension = stoi(userChoice) - 1;
                                    break; // from inner extension choice loop
                                }
                            }
                        } else {
                            consistentFileExtension = false;
                        }
                        break; // Exit outer extension choice loop
                    }
                }
            } 
            else { consistentFileExtension = true; fileExtension = 0; }

            // Rename loop
            finalFilePaths.resize(fileAmount);
            for (int i = 0; i < fileAmount; i++) {
                if (::stopPromptingUser) break;
                clearScreen();
                cout << (i == (fileAmount - 1) ? ("Rename The Last File ⬇️") : ("Files Left To Rename: " + to_string(fileAmount - i))) << endl;
                cout << "Worksheet Number: " << worksheetNumber << endl;
                cout << endl << "Current File Path #" << (i + 1) << ": " << endl
                     << originalFilePaths[i] << endl << endl;
                tempTitleStorage = config.createTitle(&worksheetNumber, (consistentFileExtension ? &fileExtension : nullptr), &fileAmount);
                if (tempTitleStorage.empty()) { break; }
                finalFilePaths[i] = originalFilePaths[i].parent_path() / tempTitleStorage;

                if (!fs::exists(finalFilePaths.at(i)) || (fs::exists(finalFilePaths.at(i)) && overwriteExistingFile(finalFilePaths.at(i)))) {
                  // TODO make sure q (i.e. ::stopPromptingUser) exits without hitting the 'else' block
                  string command = "magick " + breakWhiteSpaces(originalFilePaths.at(i).string()) + " " + breakWhiteSpaces(finalFilePaths.at(i).string()) + " && rm " + breakWhiteSpaces(originalFilePaths.at(i).string());
                  // clog << command; this_thread::sleep_for(chrono::seconds(3));
                  if (::stopPromptingUser) return;
                  try { ((originalFilePaths.at(i).string().find("heic") != string::npos) ? (void)system(command.c_str()) : fs::rename(originalFilePaths.at(i), finalFilePaths.at(i))); }
                  catch(const std::exception& error) {
                      cout << "\nERROR Incorrect Path Formatting" << endl;
                      std::cerr << error.what() << endl;
                      this_thread::sleep_for(chrono::seconds(2));
                      break;
                  } 
                }
                else {
                  clearScreen();
                  cout << "Rename Of File " << originalFilePaths.at(i).filename() << " Cancelled." << endl;
                  this_thread::sleep_for(chrono::seconds(2));
                  continue; // Skip to the next file in the loop
                }
            }
          break; }
          case SWITCH_TO_DIFFERENT_SCHEMA: {
            vector<string> tempStorage; int amountOfSchemes = config.schemes.size();
            for (auto& course : config.schemes) {
            tempStorage.push_back(course.courseTitle);
            }
            do {
              clearScreen();
              cout << "Select Course:" << endl;
              displayOptions(tempStorage, nullptr, nullptr);
              cin >> config.selectedSchemeIndex;
            } while(!validateInput(::stopPromptingUser, to_string(config.selectedSchemeIndex), &amountOfSchemes));
            if (::stopPromptingUser) return;
            if (config.selectedSchemeIndex > 0) { config.selectedSchemeIndex--; saveConfig(); }
          break; } 
          case EDIT_USER_INFO: {
            bool correctSurname = false, correctStudentID = false; string newSurname, newStudentID;
            do {
              clearScreen();
              if (!correctSurname) {
                cout << "The Current Surname Saved Is: " << config.surname << endl
                    << "Change To: ";
                cin >> newSurname;
                if (validateInput(::stopPromptingUser, newSurname, nullptr, "string")) { correctSurname = true; config.surname = newSurname; }  
                else {
                  if (::stopPromptingUser) { displayStartMenu(); return; } 
                  else { chastiseIncorrectInput("string"); continue; } 
                }
              }
              cout << "The Current StudentID Saved Is: " << config.studentID << endl
                << "Change To: ";
              cin >> newStudentID;
              if (validateInput(::stopPromptingUser, newStudentID, nullptr, "string")) { correctStudentID = true; config.studentID = newStudentID; }  
                else {
                  if (::stopPromptingUser) { displayStartMenu(); return; } 
                  else { chastiseIncorrectInput("string"); continue; } 
                }
            } while (!correctSurname || !correctStudentID);
            saveConfig();
          break; }
          case DELETE_USER_CONFIG: {
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
          break; } 
          case EXIT_PROGRAMM: {
            updateConfig();
            return;
          break; } // is redundant but included for symmetry
          default: {
            throw runtime_error("Invalid Input Passed To processUserChoice() Function");
          break; }
        }
      } catch (const runtime_error& e) { // Should Never Be Reached, But Added Just In Case
          cerr << e.what() << endl << "Passed Value: " << selectedOption << endl;
          return;
        }
      displayStartMenu();
      return;
    }
    void saveConfig() {
      fs::remove(configPath); // TODO Replace This With Just Truncating The Contents Of The File (semantically equivalent currently)
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
      NamingScheme tempBundle;
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
    void displayStartMenu() {
      clearScreen();
      string userInput, tempTitle = "Automatic Worksheet Titler";
      vector<string> options = {}; int amountOfOptions; ::stopPromptingUser = false;

      // Workaround with the type conversions since you cannot increment an enum
      for(int i = static_cast<int>(MenuOptions::RENAME); i <= static_cast<int>(MenuOptions::EXIT_PROGRAMM); ++i) { options.push_back(optionValues[static_cast<MenuOptions>(i)]); }
      amountOfOptions = options.size();
      do {
          displayOptions(options, &tempTitle, &config);
          cin >> userInput;
          if (userInput == "q" || userInput == "exit") { break; }
        } while (!validateInput(::stopPromptingUser, userInput, &amountOfOptions));
      if (userInput == "q" || userInput == "exit") { processUserChoice(EXIT_PROGRAMM); }
      else { MenuOptions choice = static_cast<MenuOptions>(stoi(userInput)); processUserChoice(choice);
      }
      
    }

  public:
    Renamer() {
      if(!fs::exists(configPath)) { initialSetUp(); }
      else { loadConfig(); }
      displayStartMenu();
    }
    void updateConfig() {
      vector<string> tempStorage; NamingScheme transitionStorage;

      config.schemes.clear(); // Clear Old Variables
      
      // Set The New Config
      transitionStorage.courseTitle = "TGI";
          transitionStorage.lastWorksheet = 0; //! TODO Create An Auto-Saving Tracker Of The Last Rename
          transitionStorage.pattern = "a[Matrikelnummer]_UE[AufgabenblattNr]_BSP[BeispielNr].[Extension]";
          transitionStorage.example = "a12345678_UE1_BSP2.png";
          tempStorage.push_back("jpg");
          tempStorage.push_back("jpeg");
          tempStorage.push_back("png");
          tempStorage.push_back("pdf");
          tempStorage.push_back("txt");
        transitionStorage.fileTypes = tempStorage;
        config.schemes.push_back({transitionStorage});
        transitionStorage = {};
        tempStorage.clear();
      transitionStorage.courseTitle = "MGI";
          transitionStorage.lastWorksheet = 0; //! TODO Create An Auto-Saving Tracker Of The Last Rename
          transitionStorage.pattern = "[Nachname]_[Matrikelnummer]_B[AufgabenblattNr]_A[BeispielNr].[Extension]";
          transitionStorage.example = "Archimedes_31415926_B5_A3.PDF";
          tempStorage.push_back("PDF");
        transitionStorage.fileTypes = tempStorage;
        config.schemes.push_back({transitionStorage});
        transitionStorage = {};
        tempStorage.clear();
      transitionStorage.courseTitle = "TGI (special)";
          transitionStorage.lastWorksheet = 0; //! TODO Create An Auto-Saving Tracker Of The Last Rename
          transitionStorage.pattern = "a[Matrikelnummer]_S[AufgabenblattNr].[Extension]";
          transitionStorage.example = "a12345678_S1.pdf";
          tempStorage.push_back("pdf");
          tempStorage.push_back("ac");
        transitionStorage.fileTypes = tempStorage;
        config.schemes.push_back({transitionStorage});
        transitionStorage = {};
        tempStorage.clear();

        saveConfig();
    }   
};

void displayOptions(vector<string> options, string* highlightedTitle, UserConfig* config, bool fileExtensions) {
  if (highlightedTitle != nullptr) {
    string padding, spaces;
    for (int i = 0; i < highlightedTitle->length(); i++) { 
      padding += "══";
      if (i % 2 == 0) { spaces += " "; } //  aproximated dynamic scaling
    } // // TODO make dynamic scaling work for both even AND odd numbers
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
         << "Selected Schema: " << config->schemes.at(config->selectedSchemeIndex).courseTitle << '\n' << endl;
  }
  for (int i = 1; i <= options.size(); i++) {
    cout << "[ " << i << " ] " << (fileExtensions ? "." : "") << options[i - 1] << endl;
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
void chastiseIncorrectInput(string dataType, const int& maxValidInput) {
    clearScreen();
    cout << "Please ";  
    if (dataType == "int") { cout << "Select Insert A Number In Allowed Range: " << "(1–" << maxValidInput << ")";}
    else if (dataType == "string") { cout << "Do Not Use Forbidden Characters"; }
    else if (dataType == "path") { cout << "Insert A Path To An Existing File"; }
    else { cout << "Insert A Valid Input"; }
    cout << endl;
    this_thread::sleep_for(chrono::seconds(1));
    clearScreen();
  }
bool validateInput(bool& stopPrompting, string userInput, const int* largestAvaliableOption, string expectedDataType) {
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
    vector<string> paths; string currentPath;
    bool isEscaped = false;

    // TODO Add #ifdef _WIN32 ... (handle windows path formatting)
    for (char token : input) {
      if (isEscaped) { currentPath += token; isEscaped = false; } 
      else if (token == '\\') { isEscaped = true; } 
      else if (isspace(token)) {
        if (!currentPath.empty()) { paths.push_back(currentPath); currentPath.clear(); }
      } 
      else { currentPath += token; }
    }
    if (!currentPath.empty()) { paths.push_back(currentPath); }
    return paths;
}
void clearScreen () {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
bool overwriteExistingFile(fs::path& file) {
  string userInput;
  
  clearScreen();
  cout << "A File by the Name " << file.filename() << " Already Exists at This Location." << endl
       << endl << "Do You Want to Overwrite It?" << endl;
  displayOptions();
  cin >> userInput;
  if (validateInput(::stopPromptingUser, userInput, nullptr, "string")) {
    if (userInput == "1") return true;
    else {
      system("clear");
      cout << "Do You Want To Append Something To The File Name?" << endl;
      displayOptions();
      cin >> userInput;
      if (userInput != "1") return false;
      else {
        system("clear");
        cout << "Add Something To The File To Complete The Rename" << endl << endl
             << file.stem().string();
        cin >> userInput;
        if (validateInput(::stopPromptingUser, userInput, nullptr, "string")) {
          fs::path newPath = file.parent_path() / (file.stem().string() + userInput + file.extension().string());
          file = newPath;
          return true;
        }
        else if (!::stopPromptingUser) { chastiseIncorrectInput("string"); return overwriteExistingFile(file); }
        else return false;
      }
    }
  }
  else if (!::stopPromptingUser) { chastiseIncorrectInput("string"); return overwriteExistingFile(file); }
  else return false;
}
string breakWhiteSpaces(string input) {
  for (size_t i = 0; i < input.size(); ++i) { if (input.at(i) == ' ') input.insert((input.begin() + i++), '\\'); } return input;
}
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
//* Clear Terminal + Start Process By Creating A 'Renamer' instance
int main () {
  clearScreen();
  Renamer instance;
  clearScreen();
  instance.updateConfig(); // Should Be Called Automatically, But Call Manually Just In Case
  return 0;
}
//!------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
  0. 🚧 Fix bugs in renaming process
    // 0.0. ✅ infinite loop after exiting ("exit" or "q") in case 2 (multiple rename)
    // 0.1. ✅ infinite loop after catching an error
    // 0.2. ✅ incorrect input reading if not inside ""
    // 0.3. ✅ add a time delay for error of incorrect path amonut (multiple rename)
      // 0.3.1. ✅ if fewer paths than requested still complete the rename (if user agrees)
    // 0.4. ✅ add a double check before deleting a file (renaming to an existing file name)
    // 0.5. ✅ Handle " " breaking for command rename 'magick some\ folder/file\ 3.heic some\ folderfile\ 3.pdf
  // 1. ✅ Add an input verifier function
  // 2. ✅ Add a possibility to exit at EVERY cin (q/exit) function check
    // 2.1. ✅ for strings
    // 2.2. ✅ for integers
  3. 🚧 Handle all comments
    // 3.1 ✅ Fix multiline rename
    // 3.2. ✅ add documentation for all functions/classes
    3.3. 🚧 remove all actionable comments
      3.3.1. 🚧 todos
      3.3.2. 🚧 new features
      3.3.3. 🚧 remember to ...
  5. ❌ Minimize code repition (functions + separate files)
    // 5.1. ✅ verification for "q" || "exit" as a function
    // 5.2. ✅ merge the single-multi Renamer options into 1
  6. ❌ Add cross platform compatibility 
    // 6.1. ✅ clearing the terminal
    6.2. ❌ parsing "/" and "\" from paths based on OS
    // 6.3. ✅ invividual terminal formatting (when dragging files)
  7. 🚧 Refactor + review code
    // 7.0. ✅ replace the case 'int' with an enum
    7.1. ❌ replace the .txt config file with a .json one
    7.2. ❌ minimize redundant variable usage
  8. 🚧 Add automatic file upload to corresponding moodle course
  // 9. ✅ Add append options for name collisions
  10. ❌ Create iPhone App
*/