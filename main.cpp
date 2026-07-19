#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int userChoise = 0;

    cout << "What would you like to do?\n";
    cout << "1: Enter a first name\n";
    cout << "2: Enter a last name\n";
    cout << "3: get a first name\n";
    cout << "4: get a last name\n";
    cout << "0: exit the program\n";
    cout << " Enter your choice:";
    cin >> userChoise;

    switch(userChoise) {
        case 1:
        cout << "You want to enter a first name!";
        break;
        case 2:
        cout << "You want to enter a first name!";
        break;
        case 3:
        cout << "Here is a first name: " << "Marf";
        break;
        case 4:
        cout << "Here is a last name: " << "Dwarf";
        break;
        case 0:
        return 0;
        default:
        cout << "Your choise doesn't exist!";
    }

    return 0;
}