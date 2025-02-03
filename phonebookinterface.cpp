// phonebook_interface.cpp
#include <iostream>
#include "phonebook.h"  // Include the C functions
using namespace std;

extern "C" {

    #include "phonebook.h"  // Ensure C functions are recognized



}

// Function to display the menu
void display_menu() {
    cout << "----------------------------------------\n";
    cout << "       Welcome to Phonebook App\n";
    cout << "----------------------------------------\n";
    cout << "1. List all records\n";
    cout << "2. Add a person\n";
    cout << "3. Search for a person\n";
    cout << "4. Remove a person\n";
    cout << "5. Update a person's details\n";
    cout << "6. Delete all contacts\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    
    while (true) {
        display_menu();
        cin >> choice;

        switch (choice) {
            case 1:
                list_record();
                break;
            case 2:
                add_person();
                break;
            case 3:
                search_person();
                break;
            case 4:
                remove_person();
                break;
            case 5:
                update_person();
                break;
            case 6:
                remove_all();
                break;
            case 7:
                cout << "Thank you for using the Phonebook app!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();  // Wait for user input
        system("cls");  // Clear the screen (Linux/macOS), use "cls" on Windows
    }

    return 0;
}
