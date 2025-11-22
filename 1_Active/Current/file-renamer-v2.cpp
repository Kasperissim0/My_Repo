// =================================================================================================
// file-renamer-v2.cpp
//
// A completely refactored version of the file renamer utility.
//
// Key Improvements:
// - JSON Configuration: Replaced the fragile custom text config with robust JSON.
// - Separation of Concerns: Logic is split into three distinct parts:
//   1. Config: Manages loading/saving of user data.
//   2. UI: Handles all console input and output.
//   3. Renamer: Contains the core application logic, orchestrating the other two.
// - Robust Input: A centralized, template-based prompt system handles all user input,
//   preventing common errors and drastically reducing code duplication.
// - Modern C++: Uses std::optional, range-based for loops, and other modern
//   features for safer and more readable code.
// - Maintainability: The clean structure makes the code easier to understand, debug, and extend.
//
// How to Compile:
// You need the nlohmann::json single-header file.
// 1. Download '''json.hpp''' from here: https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp
// 2. Place it in your include path or in the same directory as this file.
// 3. Compile with a C++17 (or newer) compatible compiler:
//    clang++ -std=c++17 file-renamer-v2.cpp -o renamer_v2
// =================================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <filesystem>
#include <fstream>
#include <limits>
#include <iomanip>
#include <functional>
#include <regex>
#include <chrono>
#include <thread>
#include <algorithm>

// Assumes nlohmann/json.hpp is in the include path or same directory.
// You can get it from: https://github.com/nlohmann/json
#include "json.hpp"

// Forward declarations
namespace UI {
    void clearScreen();
}

// =================================================================================================
// CONFIGURATION COMPONENT
// - Handles data structures and JSON serialization/deserialization.
// =================================================================================================
namespace Config {

namespace fs = std::filesystem;
using json = nlohmann::json;

// Data structure for a single naming scheme
struct NamingScheme {
    std::string courseTitle;
    std::string pattern;
    std::string example;
    std::vector<std::string> fileTypes;
};

// Data structure for the user's entire configuration
struct UserConfig {
    std::string surname;
    std::string studentID;
    int selectedSchemeIndex = 0;
    std::vector<NamingScheme> schemes;
};

// Allow nlohmann::json to automatically convert to/from our structs
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NamingScheme, courseTitle, pattern, example, fileTypes)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UserConfig, surname, studentID, selectedSchemeIndex, schemes)


class Manager {
public:
    Manager() {
        fs::path configDir = ".renamer-config";
        m_configPath = configDir / "config.json";
        if (!fs::exists(m_configPath)) {
            std::cout << "Configuration file not found. Creating a default one..." << std::endl;
            createDefaultConfig();
            save();
            std::cout << "Default configuration created at: " << m_configPath << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            load();
        }
    }

    void load() {
        try {
            std::ifstream f(m_configPath);
            json data = json::parse(f);
            m_userConfig = data.get<UserConfig>();
        } catch (const json::exception& e) {
            std::cerr << "Error parsing config file: " << e.what() << std::endl;
            std::cerr << "Reverting to default configuration." << std::endl;
            createDefaultConfig();
        }
    }

    void save() {
        try {
            if (!fs::exists(m_configPath.parent_path())) {
                fs::create_directories(m_configPath.parent_path());
            }
            std::ofstream o(m_configPath);
            json data = m_userConfig;
            o << std::setw(4) << data << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving config file: " << e.what() << std::endl;
        }
    }
    
    void deleteConfig() {
        try {
            if (fs::exists(m_configPath)) {
                fs::remove(m_configPath);
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error deleting config file: " << e.what() << std::endl;
        }
        createDefaultConfig();
    }

    UserConfig& getConfig() { return m_userConfig; }
    const UserConfig& getConfig() const { return m_userConfig; }

private:
    void createDefaultConfig() {
        m_userConfig = {
            "YourSurname",
            "12345678",
            0,
            {
                {
                    "TGI",
                    "a[Matrikelnummer]_UE[AufgabenblattNr]_BSP[BeispielNr][Extension]",
                    "a12345678_UE1_BSP2.pdf",
                    {".jpg", ".jpeg", ".png", ".pdf", ".txt"}
                },
                {
                    "MGI",
                    "[Nachname]_[Matrikelnummer]_B[AufgabenblattNr]_A[BeispielNr][Extension]",
                    "Archimedes_31415926_B5_A3.PDF",
                    {".PDF"}
                }
            }
        };
    }

    fs::path m_configPath;
    UserConfig m_userConfig;
};

} // namespace Config


// =================================================================================================
// UI COMPONENT
// - Handles all console input and output.
// =================================================================================================
namespace UI {

// A generic, safe, and reusable function for prompting the user for input.
// It handles validation, error messages, and re-prompting.
// Returns an optional, which is empty if the user quits.
template<typename T>
std::optional<T> prompt(const std::string& prompt_text, std::function<bool(const T&)> validator = [](const T&){ return true; }, const std::string& error_text = "Invalid input.") {
    std::string input;
    while (true) {
        std::cout << prompt_text;
        std::getline(std::cin, input);

        if (input == "q" || input == "exit") {
            return std::nullopt;
        }

        T value;
        if constexpr (std::is_same_v<T, std::string>) {
            value = input;
        } else if constexpr (std::is_same_v<T, std::filesystem::path>) {
            value = std::filesystem::path(input);
        }
        else {
            std::stringstream ss(input);
            ss >> value;
            if (ss.fail() || !ss.eof()) {
                clearScreen();
                std::cout << "Invalid format. " << error_text << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                clearScreen();
                continue;
            }
        }

        if (validator(value)) {
            return value;
        } else {
            clearScreen();
            std::cout << error_text << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            clearScreen();
        }
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI escape code for clearing screen and moving cursor to top-left
    std::cout << "[2J[1;1H";
#endif
}

void displayHeader(const std::string& title) {
    if (title.empty()) return;
    std::string padding(title.length() * 2, '═');
    std::string spaces(title.length(), ' ');
    
    std::cout << "
╔" << padding << "╗
"
              << "║" << spaces << title << spaces << "║
"
              << "╚" << padding << "╝
" << std::endl;
}

void displayMenu(const std::string& title, const std::vector<std::string>& options, const Config::UserConfig* config = nullptr) {
    clearScreen();
    displayHeader(title);

    if (config) {
        std::cout << "Surname: " << config->surname << std::endl
                  << "StudentID: " << config->studentID << std::endl
                  << "Selected Schema: " << config->schemes[config->selectedSchemeIndex].courseTitle << "
" << std::endl;
    }

    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "[ " << i + 1 << " ] " << options[i] << std::endl;
    }
}

void pause(const std::string& message) {
    std::cout << std::endl << message << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

} // namespace UI


// =================================================================================================
// RENAMER COMPONENT
// - Contains the core application logic.
// =================================================================================================
class Renamer {
public:
    Renamer() : m_running(true) {
        // Config is loaded in its constructor
    }

    void run() {
        while (m_running) {
            displayMainMenu();
            auto choice = UI::prompt<int>(
                "
→ Choice: ",
                [this](int c){ return c >= 1 && c <= m_mainMenuOptions.size(); },
                "Please select a valid option."
            );

            if (choice) {
                processMainMenuChoice(*choice);
            } else {
                m_running = false; // User chose to quit
            }
        }
        UI::clearScreen();
        std::cout << "Exiting program. Goodbye!" << std::endl;
    }

private:
    void displayMainMenu() {
        UI::displayMenu("Automatic Worksheet Titler", m_mainMenuOptions, &m_config.getConfig());
    }

    void processMainMenuChoice(int choice) {
        switch (choice) {
            case 1: renameSingleFile(); break;
            case 2: renameMultipleFiles(); break;
            case 3: selectSchema(); break;
            case 4: editUserInfo(); break;
            case 5: deleteConfig(); break;
            case 6: m_running = false; break;
            default: break; // Should not happen due to validation
        }
    }

    std::string generateTitle(const Config::NamingScheme& scheme, int worksheetNum, int exerciseNum, int extensionIndex) {
        std::string title = scheme.pattern;
        
        title = std::regex_replace(title, std::regex("\[Matrikelnummer\]"), m_config.getConfig().studentID);
        title = std::regex_replace(title, std::regex("\[Nachname\]"), m_config.getConfig().surname);
        title = std::regex_replace(title, std::regex("\[AufgabenblattNr\]"), std::to_string(worksheetNum));
        title = std::regex_replace(title, std::regex("\[BeispielNr\]"), std::to_string(exerciseNum));
        
        std::string extension = "";
        if (extensionIndex >= 0 && extensionIndex < scheme.fileTypes.size()) {
            extension = scheme.fileTypes[extensionIndex];
        }
        title = std::regex_replace(title, std::regex("\[Extension\]"), extension);

        return title;
    }

    void renameSingleFile() {
        UI::clearScreen();
        auto path = UI::prompt<std::filesystem::path>(
            "Enter the full path to the file you want to rename:
> ",
            [](const auto& p){ return std::filesystem::exists(p) && std::filesystem::is_regular_file(p); },
            "File does not exist. Please provide a valid path."
        );
        if (!path) return;

        auto worksheetNum = UI::prompt<int>("Worksheet Number: ", [](int n){ return n > 0; });
        if (!worksheetNum) return;

        auto exerciseNum = UI::prompt<int>("Exercise Number: ", [](int n){ return n > 0; });
        if (!exerciseNum) return;

        const auto& scheme = m_config.getConfig().schemes[m_config.getConfig().selectedSchemeIndex];
        int extensionIndex = 0;
        if (scheme.fileTypes.size() > 1) {
            std::vector<std::string> extOptions = scheme.fileTypes;
            UI::displayMenu("Select File Type", extOptions);
            auto extChoice = UI::prompt<int>(
                "
→ Choice: ",
                [&](int c){ return c >= 1 && c <= extOptions.size(); },
                "Please select a valid option."
            );
            if (!extChoice) return;
            extensionIndex = *extChoice - 1;
        }

        std::string newName = generateTitle(scheme, *worksheetNum, *exerciseNum, extensionIndex);
        std::filesystem::path newPath = path->parent_path() / newName;

        try {
            std::filesystem::rename(*path, newPath);
            UI::pause("File renamed successfully to:
" + newPath.string());
        } catch (const std::filesystem::filesystem_error& e) {
            UI::pause("ERROR: Could not rename file.
" + std::string(e.what()));
        }
    }

    void renameMultipleFiles() {
        UI::clearScreen();
        auto fileCount = UI::prompt<int>("How many files to rename? ", [](int n){ return n > 0; });
        if (!fileCount) return;

        if (*fileCount == 1) {
            renameSingleFile();
            return;
        }

        std::vector<std::filesystem::path> paths;
        paths.reserve(*fileCount);
        for (int i = 0; i < *fileCount; ++i) {
            UI::clearScreen();
            auto path = UI::prompt<std::filesystem::path>(
                "Enter path for file " + std::to_string(i + 1) + " of " + std::to_string(*fileCount) + ":
> ",
                [](const auto& p){ return std::filesystem::exists(p) && std::filesystem::is_regular_file(p); },
                "File does not exist. Please provide a valid path."
            );
            if (!path) return; // User quit
            paths.push_back(*path);
        }

        auto worksheetNum = UI::prompt<int>("Common Worksheet Number for all files: ", [](int n){ return n > 0; });
        if (!worksheetNum) return;

        const auto& scheme = m_config.getConfig().schemes[m_config.getConfig().selectedSchemeIndex];
        std::optional<int> consistentExtIndex;
        if (scheme.fileTypes.size() > 1) {
            auto choice = UI::prompt<std::string>("Use the same file extension for all files? (y/n): ", [](const auto& s){ return s == "y" || s == "n"; });
            if (!choice) return;
            if (*choice == "y") {
                UI::displayMenu("Select File Type", scheme.fileTypes);
                auto extChoice = UI::prompt<int>(
                    "
→ Choice: ",
                    [&](int c){ return c >= 1 && c <= scheme.fileTypes.size(); },
                    "Please select a valid option."
                );
                if (!extChoice) return;
                consistentExtIndex = *extChoice - 1;
            }
        } else {
            consistentExtIndex = 0;
        }

        for (size_t i = 0; i < paths.size(); ++i) {
            UI::clearScreen();
            std::cout << "Renaming file " << i + 1 << " of " << paths.size() << ":
" << paths[i].string() << std::endl;
            
            auto exerciseNum = UI::prompt<int>("Exercise Number for this file: ", [](int n){ return n > 0; });
            if (!exerciseNum) return;

            int extensionIndex = 0;
            if (consistentExtIndex) {
                extensionIndex = *consistentExtIndex;
            } else {
                 UI::displayMenu("Select File Type", scheme.fileTypes);
                 auto extChoice = UI::prompt<int>(
                    "
→ Choice: ",
                    [&](int c){ return c >= 1 && c <= scheme.fileTypes.size(); },
                    "Please select a valid option."
                );
                if (!extChoice) return;
                extensionIndex = *extChoice - 1;
            }

            std::string newName = generateTitle(scheme, *worksheetNum, *exerciseNum, extensionIndex);
            std::filesystem::path newPath = paths[i].parent_path() / newName;

            try {
                std::filesystem::rename(paths[i], newPath);
                std::cout << " -> Renamed to " << newName << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            } catch (const std::filesystem::filesystem_error& e) {
                UI::pause("ERROR: Could not rename file.
" + std::string(e.what()));
            }
        }
        UI::pause("Finished renaming all files.");
    }

    void selectSchema() {
        UI::clearScreen();
        const auto& schemes = m_config.getConfig().schemes;
        std::vector<std::string> schemeTitles;
        for(const auto& s : schemes) {
            schemeTitles.push_back(s.courseTitle + " (e.g., " + s.example + ")");
        }

        UI::displayMenu("Select a Naming Schema", schemeTitles);
        auto choice = UI::prompt<int>(
            "
→ Choice: ",
            [&](int c){ return c >= 1 && c <= schemes.size(); },
            "Please select a valid option."
        );

        if (choice) {
            m_config.getConfig().selectedSchemeIndex = *choice - 1;
            m_config.save();
            UI::pause("Schema selected successfully.");
        }
    }

    void editUserInfo() {
        UI::clearScreen();
        std::cout << "Current Surname: " << m_config.getConfig().surname << std::endl;
        auto newSurname = UI::prompt<std::string>("Enter new surname: ", [](const auto& s){ return !s.empty(); });
        if (!newSurname) return;

        std::cout << "
Current Student ID: " << m_config.getConfig().studentID << std::endl;
        auto newStudentID = UI::prompt<std::string>("Enter new student ID: ", [](const auto& s){ return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit); }, "Student ID must contain only digits.");
        if (!newStudentID) return;

        m_config.getConfig().surname = *newSurname;
        m_config.getConfig().studentID = *newStudentID;
        m_config.save();
        UI::pause("User info updated successfully.");
    }
    
    void deleteConfig() {
        UI::clearScreen();
        auto choice = UI::prompt<std::string>("Are you sure you want to delete the config file and reset all settings? (y/n): ", [](const auto& s){ return s == "y" || s == "n"; });
        if (choice && *choice == "y") {
            m_config.deleteConfig();
            UI::pause("Configuration has been deleted and reset to default.");
        }
    }

    Config::Manager m_config;
    bool m_running;
    const std::vector<std::string> m_mainMenuOptions = {
        "Rename Single File",
        "Rename Multiple Files",
        "Select Schema",
        "Edit User Information",
        "Delete Configuration File",
        "Exit"
    };
};


// =================================================================================================
// MAIN
// =================================================================================================
int main() {
    try {
        UI::clearScreen();
        Renamer app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "An unexpected critical error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
