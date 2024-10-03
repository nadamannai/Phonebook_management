/*
    Author : Rohit Singh
    Project Name : Phonebook
    Date created : 16/07/2021
    Description : By using this file we can save contacts and do these operations in it.
        1) view all contacts.
        2) add a contact.
        3) remove a contact.
        4) search details of any contact number.
        5) update details of any contact.
        6) delete whole phonebook (delete all contacts present in phonebook).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char name[30];
    char country_code[4];
    long int mble_no;
    char sex[8];
    char mail[100];
};

// Defining person data type.
typedef struct person person;

// All function declaration.
void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(person *p);
void start();

// Program starts here.
/*int main() {
    start();
    return 0;
}*/

// This function will start our program.
void start() {
    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);
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
            default:
                printf("Thanks for using the phonebook. Visit again : )\n");
                exit(0);
        }
        // Wait for user input before clearing screen
        printf("Press any key to continue...\n");
        getchar(); // Clear newline from buffer
        getchar(); // Wait for input
    }
}

// This will print main menu.
void print_menu() {
    system("cls"); // Use "clear" for Unix-based systems
    printf("\t\t****************************************************************\n");
    printf("\t\t*                  Welcome TO My phone book                    *\n");
    printf("\t\t****************************************************************\n\n");
    printf("\t\t\t1) List records\n");
    printf("\t\t\t2) Add person\n");
    printf("\t\t\t3) Search person details\n");
    printf("\t\t\t4) Remove person\n");
    printf("\t\t\t5) Update person\n");
    printf("\t\t\t6) Delete all contacts\n");
    printf("\t\t\t7) Exit phonebook\n\n");
    printf("\t\t\t\tEnter your Choice: ");
}

// This function will add contact into phonebook.
void add_person() {
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL) {
        printf("Error in file opening, Please try again!\n");
        return;
    } else {
        person p;
        take_input(&p);
        fwrite(&p, sizeof(p), 1, fp);
        fclose(fp);
        printf("Record added successfully\n");
    }
}

// By this we take contact information.
void take_input(person *p) {
    system("cls");
    printf("Enter name: ");
    getchar(); // Clear newline from buffer
    scanf("%[^\n]s", p->name);
    printf("Enter country code: ");
    scanf("%s", p->country_code);
    printf("Enter mobile no: ");
    scanf("%ld", &p->mble_no);
    printf("Enter sex: ");
    scanf("%s", p->sex);
    printf("Enter email: ");
    scanf("%s", p->mail);
}

// This function will list contact available in phonebook.
void list_record() {
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL) {
        printf("Error in file opening, Please try again!\n");
        return;
    } else {
        person p;
        printf("\n\t\t\t\t******************************************************************************\n");
        printf("\t\t\t\t*                  Here are all records listed in the phonebook            *\n");
        printf("\t\t\t\t******************************************************************************\n\n");
        printf("  NAME\t\t\t   COUNTRY CODE\t    PHONE NO\t    SEX\t\t             EMAIL\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&p, sizeof(p), 1, fp) == 1) {
            printf("%-30s %-15s %-15ld %-10s %-s\n", p.name, p.country_code, p.mble_no, p.sex, p.mail);
        }
        fclose(fp);
        printf("\nPress any key to continue...\n");
    }
}

// This function will search contact in phonebook.
void search_person() {
    system("cls");
    long int phone;
    printf("Enter Phone number of the person you want to search: ");
    scanf("%ld", &phone);

    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL) {
        printf("Error in file opening, Please try again!\n");
        return;
    } else {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (p.mble_no == phone) {
                printf("  NAME\t\t\t   COUNTRY CODE\t    PHONE NO\t    SEX\t\t             EMAIL\n");
                printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-30s %-15s %-15ld %-10s %-s\n", p.name, p.country_code, p.mble_no, p.sex, p.mail);
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("Person is not in the Phonebook\n");
        }
        fclose(fp);
        printf("\nPress any key to continue...\n");
    }
}

// This function will remove contact from phonebook.
void remove_person() {
    system("cls");
    long int phone;
    printf("Enter Phone number of the person you want to remove from phonebook: ");
    scanf("%ld", &phone);

    FILE *fp, *temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp", "wb+");
    if (fp == NULL) {
        printf("Error in file opening, Please try again!\n");
        return;
    } else {
        person p;
        int flag = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (p.mble_no == phone) {
                printf("Person removed successfully\n");
                flag = 1;
            } else {
                fwrite(&p, sizeof(p), 1, temp);
            }
        }
        if (flag == 0) {
            printf("No record found for %ld number\n", phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp", "phonebook_db");
        printf("Press any key to continue...\n");
    }
}

// This function will update contact information.
void update_person() {
    system("cls");
    long int phone;
    printf("Enter Phone number of the person you want to update details: ");
    scanf("%ld", &phone);

    FILE *fp, *temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp", "wb+");
    if (fp == NULL) {
        printf("Error in file opening, Please try again!\n");
        return;
    } else {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (p.mble_no == phone) {
                take_input(&p);
                fwrite(&p, sizeof(p), 1, temp);
                printf("Data updated successfully\n");
                flag = 1;
            } else {
                fwrite(&p, sizeof(p), 1, temp);
            }
        }
        if (flag == 0) {
            printf("No record found for %ld number\n", phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp", "phonebook_db");
        printf("Press any key to continue...\n");
    }
}

// This function will clear all the data of phonebook.
void remove_all() {
    system("cls");
    remove("phonebook_db");
    printf("All data in the phonebook deleted successfully\n");
    printf("Press any key to continue...\n");
}
