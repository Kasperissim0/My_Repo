#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

// The function we are testing
std::vector<std::string> separatePaths(const std::string& input) {
  // Sanitize the input string to prevent regex_error.
  // Replace every '\\' with '\\' so the regex engine sees literal backslashes.
  std::string sanitized_input;
  for (char c : input) {
    if (c == '\\') {
      sanitized_input += "\\\\";
    } else {
      sanitized_input += c;
    }
  }

  std::vector<std::string> paths;
  std::string result = sanitized_input;

  std::regex pathPattern(R"((.*?\.[a-zA-Z0-9]{2,5})(?=\s|\Z))");
  std::smatch match;

  while (std::regex_search(result, match, pathPattern)) {
    std::string path = match[0].str(); // Use match[0] which is the full match

    // Trim leading whitespace
    if (!path.empty() && (path.front() == ' ' || path.front() == '\t')) {
      path.erase(0, path.find_first_not_of(" \t\n\r\f\v"));
    }

    // Un-escape the sanitized path to get the real path
    std::string unescaped_path;
    for (size_t i = 0; i < path.length(); ++i) {
      if (path[i] == '\\' && i + 1 < path.length() && path[i+1] == '\\') {
        i++; // We found the double backslash '\\'
        if (i + 1 < path.length()) {
          i++; // Move to the character that was originally escaped
          unescaped_path += path[i]; // Add its literal value
        }
      } else {
        unescaped_path += path[i];
      }
    }
    paths.push_back(unescaped_path);
    result = match.suffix();
  }
  return paths;
}

int main() {
    // The exact string from your last attempt, correctly escaped for a C++ string literal
    std::string test_input = "/Users/kornienkodaniel/Documents/0\\ -\\ Inbox/a12429280_S12\\ \\,\\ \\ copy.pdf /Users/kornienkodaniel/Documents/0\\ -\\ Inbox/a12429280_S12\\ \\,\\ \\ copy\\ 2.pdf";

    std::cout << "--- REGEX SANITY TEST ---" << std::endl;
    std::cout << "Testing with input string:\n" << test_input << std::endl;
    std::cout << "------------------------------------" << std::endl;

    try {
        std::vector<std::string> found_paths = separatePaths(test_input);

        if (found_paths.empty()) {
            std::cout << "RESULT: Could not find any paths." << std::endl;
        } else {
            std::cout << "RESULT: Successfully parsed " << found_paths.size() << " paths:" << std::endl;
            for (size_t i = 0; i < found_paths.size(); ++i) {
                std::cout << "  Path " << i + 1 << ": \"" << found_paths[i] << "\"" << std::endl;
            }
        }
    } catch (const std::regex_error& e) {
        std::cerr << "ERROR: Caught a std::regex_error!" << std::endl;
        std::cerr << "  What: " << e.what() << std::endl;
        std::cerr << "  Code: " << e.code() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Caught a general exception: " << e.what() << std::endl;
    }

    return 0;
}
