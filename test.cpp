
#include "tree.h"
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    
    AVLtree<string> guestList;

    while (true) {
        cout << "Enter a command (add/search/delete/print/exit): ";
        string command;
        getline(cin, command);

        if (command == "add") {
            cout << "Enter guest name: ";
            string guest;
            getline(cin, guest);
            transform(guest.begin(), guest.end(), guest.begin(), ::tolower); // Convert to lowercase

            if (guestList.search(guest)) {
                cout << "Guest already in the list.\n";
            } else {
                guestList.insert(guest);
                cout << "Guest added.\n";
            }
        }
        else if (command == "search") {
            cout << "Enter guest name: ";
            string guest;
            getline(cin, guest);
            transform(guest.begin(), guest.end(), guest.begin(), ::tolower); // Convert to lowercase

            if (guestList.search(guest)) {
                cout << "Guest found in the list.\n";
            } else {
                cout << "Guest not found.\n";
            }
        }
        else if (command == "delete") {
            cout << "Enter guest name: ";
            string guest;
            getline(cin, guest);
            transform(guest.begin(), guest.end(), guest.begin(), ::tolower); // Convert to lowercase

            guestList.deleteNode(guest);
            cout << "Guest removed.\n";
        }
        else if (command == "print") {
            cout << "Current guest list:\n";
            guestList.print();
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}
   
