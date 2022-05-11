//------------------------------------------------------------------------------------hashtable
//---------------------------------------------------------------------------------------------

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>
#include <string.h>
#define hash_size 23

//-----------------------------------------------------------------------------------Structures
//---------------------------------------------------------------------------------------------

typedef struct linked_list
{
    char key[100];
    char value[100];

    //Added friends pointer to implement friends list

    struct linked_list * friends;
    
    //-----------------------------------------------

    struct linked_list * previous;
    struct linked_list * next;
} linked_list;

typedef struct
{
    linked_list * entries[hash_size];
} hash_table;

hash_table new_table();

//-----------------------------------------------------------------------------Provided Headers
//---------------------------------------------------------------------------------------------

int hash0(char s[100]);
int hash1(char s[100]);
int simple_hash(char s[100]);
int get_index(char s[100]);


int get_empty_entries(hash_table * table);
void clean_up_linked_list(linked_list * a);

void clean_up_table(hash_table * table);

void append_head(linked_list * a, linked_list * append);

void append_after(linked_list * a, linked_list * append);

void remove_next(linked_list * a);

void remove_previous(linked_list * a);

void print_hash_table(hash_table table);

void add_entry(hash_table * table, char key[100], char value[100]);

char * find_table(hash_table * table, char key[100]);

void delete_entry(hash_table * table, char key[100]);

//----------------------------------------------------------------------------------New Headers
//---------------------------------------------------------------------------------------------

void print_linked_list(linked_list * a, char s[256]);


void P_createRecord(hash_table * db, char * name, char s[256]);

void F_friend(hash_table * table, char * name1, char * name2, char s[256]);

void U_unfriend(hash_table * table, char * name1, char * name2, char s[256]);

void L_printFriends(hash_table * table, char * name, char s[256]);

void Q_checkFriendship(hash_table * table, char * name1, char * name2, char s[256]);

void X_exit();

int checkFriendship(hash_table * table, char * name1, char * name2);

int checkRecord(hash_table * table, char * name);

void * getRecord(hash_table * table, char key[100]);

void removeNode(linked_list * node, linked_list * node1, char s[256]);

char * getInput();

void display(char s[256]);

void eventHandler(hash_table * db, char s[256]);


#endif

//------------------------------------------------------------------------------------hashtable
//---------------------------------------------------------------------------------------------