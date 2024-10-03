// phonebook.h
#ifndef PHONEBOOK_H
#define PHONEBOOK_H

// Define the person structure
struct person {
    char name[30];
    char country_code[4];
    long int mble_no;
    char sex[8];
    char mail[100];
};
#ifdef __cplusplus
extern "C" {
#endif

// Function declarations
void remove_all();
void print_menu(); // Not needed since this will be handled in C++
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(struct person *p);

#ifdef __cplusplus
}
#endif



#endif
