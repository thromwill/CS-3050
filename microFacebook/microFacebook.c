//--------------------------------------------------------------------------------microFacebook
//---------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "hashtable.h"


//----------------------------------------------------------------------------------------Main
//--------------------------------------------------------------------------------------------
int main(){
  
  
  //Establish hash table
  hash_table database = new_table();
  hash_table * db = &database;

  //Establish output string
  char s[256];
  strcpy(s, " "); //Make output line blank on program start


  //Functionality
  for(;;){
    eventHandler(db, s);
  }
  
}

//-----------------------------------------------------------------------------Helper Functions
//---------------------------------------------------------------------------------------------

//Takes hash table and name
//Searches for name in hash table
//Returns 0 if record does not exist, 1 if record does exist
int checkRecord(hash_table * db, char * name){

    if(find_table(db, name) == NULL){
      return 0; //record does not exist
    }

    return 1; //record exists
}

//Takes hash table and two names
//Checks if corresponding people are marked as friends
//Returns 1 if true and 0 if false
int checkFriendship(hash_table * db, char * name1, char * name2){

    linked_list * p = getRecord(db, name1);

    linked_list * temp = p->friends;

    //Iterate through friends list
    while(temp != NULL){
      //If corresponding friend is found, return true
      if(strcmp(temp->key, name2) == 0){
          return 1;
      }
      temp = temp->next;
    }

    return 0;
}

//Takes no parameters
//Scans for and validates input
//Returns output string that may include: output code, character parameter, string parameter 1, string parameter 2
//output[-1] contains an output code referring to the number of parameters in the output string
//----------3 -> output has function character and two names
//----------2 -> output has function character and one name
//----------2 -> output has only function character
//----------1 -> output is invalid
char * getInput(){
    
    char input[256];//Original string collected

    char function; //Refers to user function to be called
    char name1[256]; //Name parameter
    char name2[256]; //Second name parameter
    char check[256]; //Checks for extra inputs i.e. P <name> <name> <name>
    
    //Allocate output string
    char * output = malloc(256 * sizeof(char));

    printf("\n\n: ");
    
    //Collect input
    fgets(input, sizeof(input), stdin);

    //Check that input starts with a single character
    sscanf(input, " %s %s %s", check, name1, name2);
    if((int)strlen(check) > 1){
      strcat(output, "_error_");
      output[-1] = '0';
      return output;
    }

    //Scan input into respective parameters
    sscanf(input, " %c %s %s", &function, name1, name2);
    
    //Get number of parameters scanned
    int nInput = sscanf(input, " %c %s %s %s", &function, name1, name2, check);

    //Add proper parameters to output string
    //Set output code at output[-1]
    switch(nInput){
      case 3:
        strncat(output, &function, 1); //Add character
        strcat(output, " "); //Add space
        strcat(output, name1); //Add name1
        strcat(output, " "); //Add space
        strcat(output, name2); //Add name2
        output[-1] = '3'; //Set output code
        break;
      case 2:
        strncat(output, &function, 1);
        strcat(output, " ");
        strcat(output, name1);
        output[-1] = '2';
        break;
      case 1:
        strncat(output, &function, 1);
        output[-1] = '1';
        break;
      case 4:
      default:
        strcat(output, "_error_");
        output[-1] = '0';
    }
    
  return output;
}

//Takes hash table
//Further validates input and makes respective function calls
void eventHandler(hash_table * db, char s[256]){

  //Update Display
  display(s);

  //Gets input
  char * input = getInput();

  //Character referring to main user functions ie P or L
  char function;

  //Will hold name parameters
  char name1[256];
  char name2[256];
  
  //Input code determines which function calls are possible
  //ie if character and one name is passed, P and L are available
  switch(input[-1]){
    case '3':
      //Fill parameters from input string
      sscanf(input, " %c %s %s", &function, name1, name2);

      //Use parameters
      switch(toupper(function)){
        case 'F':
          F_friend(db, name1, name2, s);
          break;

        case 'U':
          U_unfriend(db, name1, name2, s);
          break;

        case 'Q':
        Q_checkFriendship(db, name1, name2, s);
        break;

        default:
          sprintf(s, "Error: case 3");

      }

      break;
    case '2':
      sscanf(input, " %c %s", &function, name1);

      switch(toupper(function)){
        case 'P':
        P_createRecord(db, name1, s);
        break;

        case 'L':
        L_printFriends(db, name1, s);
        break;

        default:
          sprintf(s, "Error: case 2");
      }
      break;
    case '1':
      sscanf(input, " %c", &function);

      switch(toupper(function)){
      case 'X':
        X_exit();
        break;

      default:
        sprintf(s, "Error: case 1");
        break;
      }

      break;
    case '0':
      sprintf(s, "Error: Invalid Input");
      break;
    default:
      sprintf(s, "Error: Default Reached");
      break;
  }
  
}

//Clears output window, prints header, prints command list, prints latest output
void display(char s[256]){

  system("clear");

  printf("  __           _             _                       _\n");    
  printf(" / _|   __ _  | | __   ___  | |__     ___     ___   | | __\n");
  printf("| |_   / _` | | |/ /  / _ \\ | '_ \\   / _ \\   / _ \\  | |/ /\n");
  printf("|  _| | (_| | |   <  |  __/ | |_) | | (_) | | (_) | |   < \n");
  printf("|_|    \\__,_| |_|\\_\\  \\___| |_.__/   \\___/   \\___/  |_|\\_\\\n");

  printf("\nCommands List: \n");
  printf("P - <name> ---------- Create a person record of the specified first name.\n");
  printf("F - <name1> <name2> - Record that the two specified people are friends.\n");
  printf("U - <name1> <name2> - Record that the two specified people are no longer friends.\n");
  printf("L - <name> ---------- Print out the friends of the specified person.\n");
  printf("Q - <name1> <name2> - Check whether the two people are friends.\n");
  printf("X ------------------- Terminate the program.\n");

  printf("\n%s", s);

}

//---------------------------------------------------------------------------Main Functionality
//---------------------------------------------------------------------------------------------

//Takes hash table and name
//Adds element to hash table using the given name
void P_createRecord(hash_table * db, char * name, char s[256]){

    //Check if corresponding person is in hash table
    if(checkRecord(db, name) == 1){
      sprintf(s, "Record already exists!");
      return;
    }

    //Add person to hash table
    add_entry(db, name, name);

    sprintf(s, "Entry for %s added!", name);
    
    
}

//Takes hash table and two names
//Gets nodes under given names from table and adds them to the respective friends list
void F_friend(hash_table * db, char * name1, char * name2, char s[256]){

    //Check that corresponding people are in the hash table
    if(checkRecord(db, name1) == 0){
      sprintf(s, "No record found for %s!", name1);
      return;
    }

    if(checkRecord(db, name2) == 0){
      sprintf(s, "No record found for %s!", name2);
      return;
    }

    //Check if corresponding people are already friends
    if(checkFriendship(db, name1, name2) == 1){
      sprintf(s, "%s and %s are already friends!", name1, name2);
      return;
    }
    
    //Get nodes using given names
    linked_list * p1 = getRecord(db, name1);
    linked_list * p2 = getRecord(db, name2);

    linked_list * node1 = (linked_list*)malloc(sizeof(linked_list));
    strcpy(node1->key, name1);
    strcpy(node1->value, name1);

    linked_list * node2 = (linked_list*)malloc(sizeof(linked_list));
    strcpy(node2->key, name2);
    strcpy(node2->value, name2);

    //Add friends to each friends list
    node2->next = p1->friends;
    p1->friends = node2;

    node1->next = p2->friends;
    p2->friends = node1;    

    sprintf(s, "Friends Added!");
}


//Takes hash table and two names
//Gets respective nodes and removes them from each friends list
void U_unfriend(hash_table * db, char * name1, char * name2, char s[256]){

    //Check that corresponding people are in the hash table
    if(checkRecord(db, name1) == 0){
      sprintf(s, "No record found for %s!", name1);
      return;
    }

    if(checkRecord(db, name2) == 0){
      sprintf(s, "No record found for %s!", name2);
      return;
    }

    //Check if corresponding people are already friends
    if(checkFriendship(db, name1, name2) == 0){
      sprintf(s, "%s and %s are not friends!", name1, name2);
      return;
    }

    linked_list * p1 = getRecord(db, name1);
    linked_list * p2 = getRecord(db, name2);

    //Remove friends from list
    removeNode(p1, p2, s);
    removeNode(p2, p1, s);

    sprintf(s, "Friends removed!");
  
}

//Takes hash table and name
//Gets respective node and prints each element under it's friends list
void L_printFriends(hash_table * db, char * name, char s[256]){
    
    //Check that corresponding person is in hash table
    if(checkRecord(db, name) == 0){
      sprintf(s, "No record found for %s!", name);
      return;
    }

    //Print friends list
    sprintf(s, "%s's friends: \n", name);
    linked_list * person = getRecord(db, name);
    print_linked_list(person->friends, s);
}

//Takes two names
//Gets respective nodes and checks if names are in friends lists
//Prints result
void Q_checkFriendship(hash_table * db, char * name1, char * name2, char s[256]){
    
    //Check that corresponding people are in hash table
    if(checkRecord(db, name1) == 0){
      sprintf(s, "No record found for %s!", name1);
      return;
    }

    if(checkRecord(db, name2) == 0){
      sprintf(s, "No record found for %s!", name2);
      return;
    }

    //Check if corresponding people are friends and print result
    if(checkFriendship(db, name1, name2) == 1){
      sprintf(s, "%s and %s are friends!", name1, name2);
      return;
    } 
    sprintf(s, "%s and %s are not friends!", name1, name2);

}

//Takes no parameters
//Exits program
void X_exit(){

  exit(0);

}

//--------------------------------------------------------------------------------microFacebook
//---------------------------------------------------------------------------------------------

