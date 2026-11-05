// main.cpp
// Compileren: g++ -std=c++17 -Wall -Wextra -o dnd_namegen main.cpp
// Of met MSVC: cl /EHsc /std:c++17 main.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>



// ---------- function for input ----------

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt, int minVal, int maxVal) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            clearInput();
            return value;
        }
        std::cout << "Incorrect choice, try again.\n";
        clearInput();
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    // Trim spaces at the beginning and end
    const auto start = line.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    const auto end = line.find_last_not_of(" \t");
    return line.substr(start, end - start + 1);
}

// ---------- Saving and Loading ----------

const std::string FIRSTNAME_FILE = "firstnames.txt";
const std::string LASTNAME_FILE = "lastnames.txt";

// Load a list of names from a text file, one name per line
std::vector<std::string> loadNames(const std::string& filename) {
    std::vector<std::string> names;
    std::ifstream in(filename);
    std::string name;
    while (std::getline(in, name)) {
        if (!name.empty()) {
            names.push_back(name);
        }
    }
    return names;
}

// Save a list of names to a text file, one name per line
void saveNames(const std::string& filename, const std::vector<std::string>& names) {
    std::ofstream out(filename, std::ios::trunc);
    for (const auto& name : names) {
        out << name << '\n';
    }
}

// ---------- Menu actions ----------

void addFirstName(std::vector<std::string>& firstNames) {
    std::string name = readLine("Enter a first name: ");
    if (!name.empty()) {
        firstNames.push_back(name);
        saveNames(FIRSTNAME_FILE, firstNames);
        std::cout << "First name saved.\n";
    } else {
        std::cout << "No first name entered.\n";
    }
}

void addLastName(std::vector<std::string>& lastNames) {
    std::string name = readLine("Enter a last name: ");
    if (!name.empty()) {
        lastNames.push_back(name);
        saveNames(LASTNAME_FILE, lastNames);
        std::cout << "Last name saved.\n";
    } else {
        std::cout << "No last name entered.\n";
    }
}

void listNames(const std::vector<std::string>& names, const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
    if (names.empty()) {
        std::cout << "No names available.\n";
        return;
    }
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout << (i + 1) << ". " << names[i] << '\n';
    }
}

void deleteName(const std::string& title, std::vector<std::string>& names, const std::string& filename) {
    listNames(names, title);
    if (names.empty()) return;

    int index = readInt("Enter the number of the name to delete (0 to cancel): ", 0, names.size());
    if (index == 0) {
        std::cout << "Deletion canceled.\n";
        return;
    }
    names.erase(names.begin() + (index - 1));
    saveNames(filename, names);
    std::cout << "Name deleted.\n";
}

void generateRandomName(const std::vector<std::string>& firstNames, const std::vector<std::string>& lastNames) {
    if (firstNames.empty() || lastNames.empty()) {
        std::cout << "Not enough names to generate a random name.\n";
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> firstDist(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDist(0, lastNames.size() - 1);

    std::string randomFirstName = firstNames[firstDist(gen)];
    std::string randomLastName = lastNames[lastDist(gen)];

    std::cout << "Randomly generated name: " << randomFirstName << " " << randomLastName << '\n';
}

// ---------- Hoofdmenu ----------

void printMenu() {
    std::cout << "\n=== DnD Naamgenerator ===\n"
              << "1. Add First Name\n"
              << "2. Add Last Name\n"
              << "3. List First Names\n"
              << "4. List Last Names\n"
              << "5. Delete First Name\n"
              << "6. Delete Last Name\n"
              << "7. Generate Random Name\n"
              << "0. Exit\n";
}

int main() {
    std::vector<std::string> firstNames = loadNames(FIRSTNAME_FILE);
    std::vector<std::string> lastNames = loadNames(LASTNAME_FILE);

    while (true) {
        printMenu();
        int choice = readInt("Choose an option: ", 0, 7);

        switch (choice) {
            case 1: addFirstName(firstNames); break;
            case 2: addLastName(lastNames); break;
            case 3: listNames(firstNames, "First Names"); break;
            case 4: listNames(lastNames, "Last Names"); break;
            case 5: deleteName("First Names", firstNames, FIRSTNAME_FILE); break;
            case 6: deleteName("Last Names", lastNames, LASTNAME_FILE); break;
            case 7: generateRandomName(firstNames, lastNames); break;
            case 0:
                std::cout << "Tot ziens!\n";
                return 0;
        }
    }
}