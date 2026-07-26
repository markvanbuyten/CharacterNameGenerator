#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

void meunSelect()
{
    int userChoise = 0;

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
        // 41 = Red Backgorund, 33 = Yellow text, 0 = Reset
        cout << "\n\033[41;33m Exiting... \n\n";
        cout << "Exiting in 6 seconds.. \033[0m\n";
        sleep(6);
        exit(1);
        default:
        cout << "Your choise doesn't exist!";
    }
}

void menuPrint()
{
    // Set the output color to green
    // background and blue foreground
    //system("color 1");
    cout << "\n\033[42;34m";


    cout << "What would you like to do?\n";
    cout << "1: Enter a first name\n";
    cout << "2: Enter a last name\n";
    cout << "3: get a first name\n";
    cout << "4: get a last name\n";
    cout << "0: exit the program\n";
}



int main()
{
   

    menuPrint();

    return 0;
}