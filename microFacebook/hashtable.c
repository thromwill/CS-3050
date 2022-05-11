//------------------------------------------------------------------------------------hashtable
//---------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

//------------------------------------------------------------------------------New or Modified
//---------------------------------------------------------------------------------------------

//Takes two linked_list nodes, p1 referring to the head of a list and p2 the node to be removed
//Removes node is found, removes node
void removeNode(linked_list * p1, linked_list * p2, char s[256]){

    linked_list * temp = (linked_list*)malloc(sizeof(linked_list));
    temp = p1->friends;

    if(strcmp(p1->friends->key, p2->key) == 0){
      linked_list * temp1 = p1->friends;
      p1->friends = p1->friends->next;
      free(temp1);
      return;
    }

    while(strcmp(temp->next->key, p2->key) != 0){
      if(temp == NULL){
        sprintf(s, "null reached");
        return;
      }
      temp = temp->next;
    }

    remove_next(temp);
}

//Modified to return linked_list node
void * getRecord(hash_table * db, char key[100])
{
    int index = get_index(key);
    linked_list * a = db->entries[index];
    while (a != NULL)
    {
        if (strcmp(a->key, key) == 0)
        {
            return a;//->value;
        }
        a = a->next;
    }
    return NULL;
}

//Modified to print friends list
void print_linked_list(linked_list * a, char s[256])
{
    char temp[256];
    if (a == NULL)
    {
        //printf("[]\n");
        sprintf(s, "Friends list empty!");
        return;
    }
    linked_list * t = a;

    //printf("[(%s, %s)", t->key, t->value);
    sprintf(temp, "%s\n", t->key);
    strcat(s, temp);
    t = t->next;
    while (t != NULL)
    {
        //printf("-->(%s, %s)", t->key, t->value);
        sprintf(temp, "%s\n", t->key);
    strcat(s, temp);
        t = t->next;
    }
    //printf("]\n");
}


//-------------------------------------------------------------------------------------Provided
//---------------------------------------------------------------------------------------------

/*
 * Create the hash table
 * This creates a new hash table with
 * all empty entries
 * The number of entries is fixed 
 * for this demo
 */
hash_table new_table()
{
    hash_table h;
    for (int i = 0; i < hash_size; ++i)
    {
        h.entries[i] = NULL;
    }
    return h;
}



/*
 * Get the index of an entry
 * this method is used to quickly swap
 * between hashing methods for a string
 */
int get_index(char s[100])
{
    return simple_hash(s);
}

/*
 * Simple hashing method sensitive to
 * the order of the string
 * uses 128 as multiplyer because
 * assuming 128 is the highest value of a char
 */
int hash0(char s[100])
{
    int i = 0;
    int hash = 0;
    while (i < 100 && s[i] != '\0')
    {
        hash = (hash * 128) % hash_size;
        hash = (hash + (s[i] % 128)) % hash_size;
        i++;
    }
    return hash;
}

/*
 * A slight modification of the hash above
 * still sensitive to order
 * tac and cat will hash to different values.
 */
int hash1(char s[100])
{
    int i = 0;
    int hash = 0;
    while (i < 100 && s[i] != '\0')
    {
        hash = (1 + hash * 128) % hash_size;
        hash = (hash + (s[i] % 128)) % hash_size;
        i++;
    }
    return hash;
}

/*
 * A simple hash
 * The order does not affect the hash value
 * strings like tac and cat hash to the same
 * value.
 */
 int simple_hash(char s[100])
{
    int i = 0;
    int hash = 0;
    while (i < 100 && s[i] != '\0')
    {
        hash = (hash + (s[i] % 128)) % hash_size;
        i++;
    }
    return hash;
}

/*
 * Add an entry based on the hash of the key
 * Because the amount of possible keys is more
 * than my hash size, it is going to have a 
 * collision
 */
void add_entry(hash_table * table, char key[100], char value[100])
{
    int index = get_index(key);
    if (table->entries[index] != NULL)
    {
        /*
        We had a collision
         */
        linked_list * a = table->entries[index];
        while (a != NULL)
        {
            /*
            We found the key
             */
            if (strcmp(a->key, key) == 0)
            {
                strcpy(a->value, value);
                break;
            }
            else
            {
                a = a->next;
            }
        }
        if (a == NULL)
        {
            a = (linked_list*)malloc(sizeof(linked_list));
            strcpy(a->key, key);
            strcpy(a->value, value);
            append_head(table->entries[index], a);
            table->entries[index] = a;
        }
    }
    else
    {
        /*
         There was no collision
         */

        table->entries[index] = (linked_list*)malloc(sizeof(linked_list));
        strcpy(table->entries[index]->key, key);
        strcpy(table->entries[index]->value, value);
        if (table->entries[index] == NULL)
        {
            printf("oh\n");
        }
    }
}

char * find_table(hash_table * table, char key[100])
{
    int index = get_index(key);
    linked_list * a = table->entries[index];
    while (a != NULL)
    {
        if (strcmp(a->key, key) == 0)
        {
            return a->value;
        }
        a = a->next;
    }
    return NULL;
}


int get_empty_entries(hash_table * table)
{
    int count = 0;
    for (int i = 0; i < hash_size; ++i)
    {
        if (table->entries[i] == NULL)
        {
            count++;
        }
    }
    return count;
}

void clean_up_linked_list(linked_list * a)
{
    linked_list * todel = a;
    while (todel != NULL)
    {
        linked_list * next = todel->next;
        free(todel);
        todel = next;
    }
}

void clean_up_table(hash_table * table)
{
    for (int i = 0; i < hash_size; ++i)
    {
        if (table->entries[i] != NULL)
        {
            clean_up_linked_list(table->entries[i]);
            table->entries[i] = NULL;
        }
    }
}

void append_head(linked_list * a, linked_list * append)
{
    if (append->next == NULL)
    {
        append->previous = a->previous;
        a->previous = append;
        append->next = a;

    }
}

void append_tail(linked_list * a, linked_list * append){

    if (a == NULL){
        a = append;
        return;
    } 

    linked_list * temp = a;
    while(temp->next != NULL){
        temp = temp->next;    
    }
    
    temp->next = append;    
    return;

}

void append_after(linked_list * a, linked_list * append)
{
    if (append->previous == NULL)
    {
        append->next = a->next;
        a->next = append;
        append->previous = a;
    }
}

void remove_next(linked_list * a)
{
    if (a->next != NULL)
    {
        linked_list * tmp = a->next;
        a->next = a->next->next;
        free(tmp);
    }
    else
    {
        printf("nothing to remove!\n");
    }
}

void remove_previous(linked_list * a)
{
    if (a->previous != NULL)
    {
        printf("removing key: %s \n", a->previous->key);
        linked_list * tmp = a->previous;
        printf("a->key: %s\n", a->key);

        a->previous = a->previous->previous;
        if (a->previous != NULL)
        {
            a->previous->next = a;
        }
        free(tmp);
        if (a->next == NULL)
        {
            printf("this key has no next\n");
        }
    }
    else
    {
        printf("nothing to remove!\n");
    }
}

/*
void print_hash_table(hash_table table)
{
    for (int i = 0; i < hash_size; ++i)
    {
        print_linked_list(table.entries[i]);
    }
    return;
}
*/

void delete_entry(hash_table * table, char key[100])
{
    int index = get_index(key);
    linked_list * a = table->entries[index];
    while (a != NULL)
    {
        if (strcmp(a->key, key) == 0)
        {
            // delete
            a = a->previous;
            if (a == NULL)
            {
                a = table->entries[index];
                a = a->next;
                if (a == NULL)
                {
                    clean_up_linked_list(table->entries[index]);
                }
                remove_previous(a);
                
                table->entries[index] = a;
            }
            else {
                remove_next(a);
            }

        }
        a = a->next;
    }

}

//------------------------------------------------------------------------------------hashtable
//---------------------------------------------------------------------------------------------

