// dnd_namegen.cpp
// Compileren: g++ -std=c++17 -Wall -Wextra -o dnd_namegen dnd_namegen.cpp
// Of met MSVC: cl /EHsc /std:c++17 dnd_namegen.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

struct Character {
    std::string firstName;
    std::string lastName;
};

// ---------- Hulpfuncties voor invoer ----------

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
        std::cout << "Ongeldige keuze, probeer opnieuw.\n";
        clearInput();
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    // Trim spaties aan begin en eind
    const auto start = line.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    const auto end = line.find_last_not_of(" \t");
    return line.substr(start, end - start + 1);
}

// ---------- Opslag ----------

const std::string SAVE_FILE = "characters.txt";

std::vector<Character> loadCharacters() {
    std::vector<Character> chars;
    std::ifstream in(SAVE_FILE);
    std::string first, last;
    while (std::getline(in, first, '\t') && std::getline(in, last)) {
        chars.push_back({first, last});
    }
    return chars;
}

void saveCharacters(const std::vector<Character>& chars) {
    std::ofstream out(SAVE_FILE, std::ios::trunc);
    for (const auto& c : chars) {
        out << c.firstName << '\t' << c.lastName << '\n';
    }
}

// ---------- Menu-acties ----------

void addCharacter(std::vector<Character>& chars) {
    std::cout << "\n--- Nieuw character toevoegen ---\n";
    std::string first = readLine("Voornaam: ");
    std::string last = readLine("Achternaam: ");
    if (first.empty() || last.empty()) {
        std::cout << "Voor- en achternaam mogen niet leeg zijn.\n";
        return;
    }
    chars.push_back({first, last});
    saveCharacters(chars);
    std::cout << "Character opgeslagen: " << first << " " << last << "\n";
}

void listCharacters(const std::vector<Character>& chars) {
    std::cout << "\n--- Opgeslagen characters ---\n";
    if (chars.empty()) {
        std::cout << "(Geen characters opgeslagen)\n";
        return;
    }
    for (size_t i = 0; i < chars.size(); ++i) {
        std::cout << i + 1 << ". " << chars[i].firstName << " "
                  << chars[i].lastName << "\n";
    }
}

void deleteCharacter(std::vector<Character>& chars) {
    listCharacters(chars);
    if (chars.empty()) return;
    int idx = readInt("Nummer van character om te verwijderen (0 = annuleren): ",
                      0, static_cast<int>(chars.size()));
    if (idx == 0) return;
    chars.erase(chars.begin() + (idx - 1));
    saveCharacters(chars);
    std::cout << "Character verwijderd.\n";
}

void generateRandomName(const std::vector<Character>& chars) {
    std::cout << "\n--- Random nieuw character ---\n";
    if (chars.size() < 2) {
        std::cout << "Voeg eerst minstens 2 characters toe; er worden voornamen\n"
                     "en achternamen uit de opgeslagen lijst gecombineerd.\n";
        return;
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> pick(0, chars.size() - 1);

    // Voornaam en achternaam uit willekeurige (mogelijk verschillende) entries
    const std::string first = chars[pick(rng)].firstName;
    const std::string last = chars[pick(rng)].lastName;

    std::cout << "Nieuwe naam: " << first << " " << last << "\n";

    std::cout << "Opslaan? (j/n): ";
    std::string answer;
    std::getline(std::cin, answer);
    if (!answer.empty() && (answer[0] == 'j' || answer[0] == 'J')) {
        // Opslaan als nieuw character
        Character c{first, last};
        auto& mutableChars = const_cast<std::vector<Character>&>(chars);
        mutableChars.push_back(c);
        saveCharacters(mutableChars);
        std::cout << "Character opgeslagen.\n";
    }
}

// ---------- Hoofdmenu ----------

void printMenu() {
    std::cout << "\n=== DnD Naamgenerator ===\n"
              << "1. Character toevoegen\n"
              << "2. Characters tonen\n"
              << "3. Character verwijderen\n"
              << "4. Random naam genereren\n"
              << "0. Afsluiten\n";
}

int main() {
    std::vector<Character> chars = loadCharacters();

    while (true) {
        printMenu();
        int choice = readInt("Kies een optie: ", 0, 4);

        switch (choice) {
            case 1: addCharacter(chars); break;
            case 2: listCharacters(chars); break;
            case 3: deleteCharacter(chars); break;
            case 4: generateRandomName(chars); break;
            case 0:
                std::cout << "Tot ziens!\n";
                return 0;
        }
    }
}