#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

struct NamingSchema {
    std::string name;
    std::string pattern;
    std::string example;
};

struct UserConfig {
    std::string matrikel;
    std::string surname;
    std::vector<NamingSchema> schemas;
    int defaultSchemaIndex;
};

class FileRenamer {
private:
    UserConfig config;
    const std::string CONFIG_FILE = "renamer_config.txt";
    
    void initDefaultSchemas() {
        NamingSchema tgi;
        tgi.name = "TGI";
        tgi.pattern = "{surname}_{matrikel}_B{sheet}_A{exercise}.{ext}";
        tgi.example = "Archimedes_31415926_B5_A3.PDF";
        
        NamingSchema mgi;
        mgi.name = "MGI";
        mgi.pattern = "a{matrikel}_UE{sheet}_BSP{exercise}.{ext}";
        mgi.example = "a12345678_UE1_BSP2.pdf";
        
        config.schemas.push_back(tgi);
        config.schemas.push_back(mgi);
        config.defaultSchemaIndex = 0;
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }
    
    bool loadConfig() {
        if (!fs::exists(CONFIG_FILE)) {
            return false;
        }
        
        std::ifstream file(CONFIG_FILE);
        if (!file.is_open()) return false;
        
        std::string line;
        
        // Read matrikel
        if (!std::getline(file, line)) return false;
        config.matrikel = trim(line);
        
        // Read surname
        if (!std::getline(file, line)) return false;
        config.surname = trim(line);
        
        // Read default schema index
        if (!std::getline(file, line)) return false;
        config.defaultSchemaIndex = std::stoi(trim(line));
        
        // Read number of schemas
        if (!std::getline(file, line)) return false;
        int schemaCount = std::stoi(trim(line));
        
        config.schemas.clear();
        for (int i = 0; i < schemaCount; i++) {
            NamingSchema schema;
            
            if (!std::getline(file, line)) return false;
            schema.name = trim(line);
            
            if (!std::getline(file, line)) return false;
            schema.pattern = trim(line);
            
            if (!std::getline(file, line)) return false;
            schema.example = trim(line);
            
            config.schemas.push_back(schema);
        }
        
        return true;
    }
    
    void saveConfig() {
        std::ofstream file(CONFIG_FILE);
        
        file << config.matrikel << "\n";
        file << config.surname << "\n";
        file << config.defaultSchemaIndex << "\n";
        file << config.schemas.size() << "\n";
        
        for (const auto& schema : config.schemas) {
            file << schema.name << "\n";
            file << schema.pattern << "\n";
            file << schema.example << "\n";
        }
        
        file.close();
    }
    
    void firstTimeSetup() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    First Time Setup                ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "\nEnter your matriculation number: ";
        std::getline(std::cin, config.matrikel);
        
        std::cout << "Enter your surname: ";
        std::getline(std::cin, config.surname);
        
        initDefaultSchemas();
        saveConfig();
        
        std::cout << "\n✓ Setup complete! Configuration saved to " << CONFIG_FILE << std::endl;
    }
    
    std::string applyPattern(const NamingSchema& schema, int sheet, int exercise, const std::string& extension) {
        std::string result = schema.pattern;
        
        // Replace placeholders
        size_t pos;
        while ((pos = result.find("{matrikel}")) != std::string::npos) {
            result.replace(pos, 10, config.matrikel);
        }
        while ((pos = result.find("{surname}")) != std::string::npos) {
            result.replace(pos, 9, config.surname);
        }
        while ((pos = result.find("{sheet}")) != std::string::npos) {
            result.replace(pos, 7, std::to_string(sheet));
        }
        while ((pos = result.find("{exercise}")) != std::string::npos) {
            result.replace(pos, 10, std::to_string(exercise));
        }
        while ((pos = result.find("{ext}")) != std::string::npos) {
            result.replace(pos, 5, extension);
        }
        
        return result;
    }
    
public:
    FileRenamer() {
        if (!loadConfig()) {
            firstTimeSetup();
        }
    }
    
    void showMenu() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Academic File Renamer           ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "User: " << config.surname << " (Matrikel: " << config.matrikel << ")" << std::endl;
        std::cout << "Default: " << config.schemas[config.defaultSchemaIndex].name << std::endl;
        std::cout << "\n[1] Quick Rename (use default schema)" << std::endl;
        std::cout << "[2] Rename with schema selection" << std::endl;
        std::cout << "[3] Batch rename multiple files" << std::endl;
        std::cout << "[4] Manage schemas" << std::endl;
        std::cout << "[5] Edit user information" << std::endl;
        std::cout << "[6] Exit" << std::endl;
        std::cout << "\n→ Choice: ";
    }
    
    void quickRename() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Quick Rename Mode               ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "Schema: " << config.schemas[config.defaultSchemaIndex].name << std::endl;
        std::cout << "Example: " << config.schemas[config.defaultSchemaIndex].example << std::endl;
        
        renameFiles(config.schemas[config.defaultSchemaIndex]);
    }
    
    void renameWithSchemaSelection() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Select Schema                   ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        
        for (size_t i = 0; i < config.schemas.size(); i++) {
            std::cout << "[" << i + 1 << "] " << config.schemas[i].name;
            if (i == config.defaultSchemaIndex) {
                std::cout << " ★";
            }
            std::cout << std::endl;
            std::cout << "    Example: " << config.schemas[i].example << std::endl;
        }
        
        int choice;
        std::cout << "\n→ Choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice > 0 && choice <= config.schemas.size()) {
            renameFiles(config.schemas[choice - 1]);
        } else {
            std::cout << "✗ Invalid choice!" << std::endl;
        }
    }
    
    void batchRename() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Batch Rename Mode               ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        
        // Select schema
        for (size_t i = 0; i < config.schemas.size(); i++) {
            std::cout << "[" << i + 1 << "] " << config.schemas[i].name << std::endl;
        }
        
        int schemaChoice;
        std::cout << "\n→ Select schema: ";
        std::cin >> schemaChoice;
        std::cin.ignore();
        
        if (schemaChoice < 1 || schemaChoice > config.schemas.size()) {
            std::cout << "✗ Invalid choice!" << std::endl;
            return;
        }
        
        NamingSchema& schema = config.schemas[schemaChoice - 1];
        
        int sheet;
        std::cout << "→ Sheet number: ";
        std::cin >> sheet;
        std::cin.ignore();
        
        std::cout << "\nEnter exercise numbers and file paths (type 'done' when finished)" << std::endl;
        std::cout << "Format: <exercise_number> <file_path>" << std::endl;
        
        while (true) {
            std::cout << "\n→ ";
            std::string line;
            std::getline(std::cin, line);
            
            if (line == "done" || line == "exit") break;
            
            std::istringstream iss(line);
            int exercise;
            std::string filePath;
            
            if (!(iss >> exercise)) {
                std::cout << "✗ Invalid format!" << std::endl;
                continue;
            }
            
            std::getline(iss >> std::ws, filePath);
            
            if (!fs::exists(filePath)) {
                std::cout << "✗ File not found: " << filePath << std::endl;
                continue;
            }
            
            std::string extension = fs::path(filePath).extension().string();
            if (extension[0] == '.') {
                extension = extension.substr(1);
            }
            
            std::string newName = applyPattern(schema, sheet, exercise, extension);
            std::string newPath = fs::path(filePath).parent_path() / newName;
            
            try {
                fs::rename(filePath, newPath);
                std::cout << "✓ Renamed to: " << newName << std::endl;
            } catch (const std::exception& e) {
                std::cout << "✗ Error: " << e.what() << std::endl;
            }
        }
        
        std::cout << "\n✓ Batch rename complete!" << std::endl;
    }
    
    void renameFiles(const NamingSchema& schema) {
        int sheet, exercise;
        std::string sourceFile;
        
        std::cout << "\n→ Sheet number: ";
        std::cin >> sheet;
        std::cout << "→ Exercise number: ";
        std::cin >> exercise;
        std::cin.ignore();
        
        std::cout << "→ Source file path (or drag & drop): ";
        std::getline(std::cin, sourceFile);
        
        // Remove quotes if present (from drag & drop)
        if (sourceFile.front() == '"' && sourceFile.back() == '"') {
            sourceFile = sourceFile.substr(1, sourceFile.length() - 2);
        }
        if (sourceFile.front() == '\'' && sourceFile.back() == '\'') {
            sourceFile = sourceFile.substr(1, sourceFile.length() - 2);
        }
        
        // Handle escaped spaces (remove backslashes before spaces)
        std::string cleanPath;
        for (size_t i = 0; i < sourceFile.length(); i++) {
            if (sourceFile[i] == '\\' && i + 1 < sourceFile.length() && sourceFile[i + 1] == ' ') {
                continue; // Skip the backslash
            }
            cleanPath += sourceFile[i];
        }
        sourceFile = cleanPath;
        
        if (!fs::exists(sourceFile)) {
            std::cout << "✗ Error: File not found!" << std::endl;
            return;
        }
        
        // Get file extension
        std::string extension = fs::path(sourceFile).extension().string();
        if (extension[0] == '.') {
            extension = extension.substr(1);
        }
        
        // Generate new name
        std::string newName = applyPattern(schema, sheet, exercise, extension);
        std::string newPath = fs::path(sourceFile).parent_path() / newName;
        
        std::cout << "\n─────────────────────────────────────" << std::endl;
        std::cout << "Old: " << fs::path(sourceFile).filename() << std::endl;
        std::cout << "New: " << newName << std::endl;
        std::cout << "─────────────────────────────────────" << std::endl;
        std::cout << "\nConfirm rename? (y/n): ";
        
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();
        
        if (confirm == 'y' || confirm == 'Y') {
            try {
                fs::rename(sourceFile, newPath);
                std::cout << "✓ File renamed successfully!" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "✗ Error: " << e.what() << std::endl;
            }
        } else {
            std::cout << "✗ Rename cancelled." << std::endl;
        }
    }
    
    void manageSchemas() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Schema Management               ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "[1] View all schemas" << std::endl;
        std::cout << "[2] Add new schema" << std::endl;
        std::cout << "[3] Set default schema" << std::endl;
        std::cout << "[4] Delete schema" << std::endl;
        std::cout << "[5] Back to main menu" << std::endl;
        std::cout << "\n→ Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                viewSchemas();
                break;
            case 2:
                addSchema();
                break;
            case 3:
                setDefaultSchema();
                break;
            case 4:
                deleteSchema();
                break;
            default:
                break;
        }
    }
    
    void viewSchemas() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Current Schemas                 ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        
        for (size_t i = 0; i < config.schemas.size(); i++) {
            std::cout << "\n[" << i + 1 << "] " << config.schemas[i].name;
            if (i == config.defaultSchemaIndex) {
                std::cout << " ★ DEFAULT";
            }
            std::cout << std::endl;
            std::cout << "    Pattern:  " << config.schemas[i].pattern << std::endl;
            std::cout << "    Example:  " << config.schemas[i].example << std::endl;
        }
    }
    
    void addSchema() {
        NamingSchema schema;
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Add New Schema                  ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "Available placeholders:" << std::endl;
        std::cout << "  {matrikel}  {surname}  {sheet}  {exercise}  {ext}" << std::endl;
        std::cout << "\n→ Schema name: ";
        std::getline(std::cin, schema.name);
        std::cout << "→ Pattern: ";
        std::getline(std::cin, schema.pattern);
        std::cout << "→ Example: ";
        std::getline(std::cin, schema.example);
        
        config.schemas.push_back(schema);
        saveConfig();
        std::cout << "\n✓ Schema added successfully!" << std::endl;
    }
    
    void setDefaultSchema() {
        viewSchemas();
        std::cout << "\n→ Select default schema: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice > 0 && choice <= config.schemas.size()) {
            config.defaultSchemaIndex = choice - 1;
            saveConfig();
            std::cout << "✓ Default schema updated!" << std::endl;
        } else {
            std::cout << "✗ Invalid choice!" << std::endl;
        }
    }
    
    void deleteSchema() {
        if (config.schemas.size() <= 1) {
            std::cout << "✗ Cannot delete - at least one schema is required!" << std::endl;
            return;
        }
        
        viewSchemas();
        std::cout << "\n→ Select schema to delete: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice > 0 && choice <= config.schemas.size()) {
            std::cout << "Delete '" << config.schemas[choice - 1].name << "'? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                config.schemas.erase(config.schemas.begin() + choice - 1);
                if (config.defaultSchemaIndex >= config.schemas.size()) {
                    config.defaultSchemaIndex = 0;
                }
                saveConfig();
                std::cout << "✓ Schema deleted!" << std::endl;
            }
        } else {
            std::cout << "✗ Invalid choice!" << std::endl;
        }
    }
    
    void editUserInfo() {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║    Edit User Information           ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "Current: " << config.surname << " (Matrikel: " << config.matrikel << ")" << std::endl;
        std::cout << "\n→ New matriculation number (Enter to keep): ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            config.matrikel = input;
        }
        
        std::cout << "→ New surname (Enter to keep): ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            config.surname = input;
        }
        
        saveConfig();
        std::cout << "\n✓ User information updated!" << std::endl;
    }
    
    void run() {
        while (true) {
            showMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1:
                    quickRename();
                    break;
                case 2:
                    renameWithSchemaSelection();
                    break;
                case 3:
                    batchRename();
                    break;
                case 4:
                    manageSchemas();
                    break;
                case 5:
                    editUserInfo();
                    break;
                case 6:
                    std::cout << "\nGoodbye!\n" << std::endl;
                    return;
                default:
                    std::cout << "✗ Invalid choice!" << std::endl;
                    break;
            }
        }
    }
};

int main() {
    FileRenamer renamer;
    renamer.run();
    return 0;
}