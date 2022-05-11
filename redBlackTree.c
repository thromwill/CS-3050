//---------------------------------------------------------------------------------redBlackTree
//---------------------------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "redBlackTree.h"

//Global output string
char s[256];

//---------------------------------------------------------------------------Externally Sourced
//---------------------------------------------------------------------------------------------

/***************************************************************************************
*    Title: Red-Black Tree
*    Author: Programiz
*    Date: n/a
*    Availability: https://www.programiz.com/dsa/red-black-tree
*
***************************************************************************************/

// Implementing Red-Black Tree in C

enum nodeColor {
  RED,
  BLACK
};

struct rbNode {
  int data, color;
  struct rbNode *link[2];
};

struct rbNode *root = NULL; //--------------------------------Global Red-Black Tree Root

// Create a red-black tree
struct rbNode *createNode(int data) {
  struct rbNode *newnode;
  newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
  newnode->data = data;
  newnode->color = RED;
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}

// Insert an node
void insertion(int data) {
  struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Print the inorder traversal of the tree
void inorderTraversal(struct rbNode *node, char output[256]) { //--------Modified to display correctly

  if (node) {
    char temp[256];

    inorderTraversal(node->link[0], output);

    sprintf(temp, "%d", node->data);
		strcat(output, temp);

    if(node->color == RED){
      strcat(output, "R->");
    } else if(node->color == BLACK){
      strcat(output, "B->");
    } else{
      strcat(output, "error: color");
    }


    inorderTraversal(node->link[1], output);
  }
  return;
}

/***************************************************************************************
*    Title: Write a Program to Find the Maximum Depth or Height of a Tree
*    Author: n/a
*    Date: 28 October, 2021
*    Availability: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
*
***************************************************************************************/
int maxDepth(struct rbNode* node)
{
    if (node == NULL)
        return -1;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->link[0]);
        int rDepth = maxDepth(node->link[1]);
 
        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}


//-----------------------------------------------------------------------------------------Main
//---------------------------------------------------------------------------------------------

int main(void){
 
 //Set output line to blank on program start
 strcpy(s, " "); 

 //Ensure red-black tree is null
 root = NULL;

 //Run the eventHandler until program is exited
 for(;;){
 	eventHandler(s);
 }

}

//-----------------------------------------------------------------------------Helper Functions
//---------------------------------------------------------------------------------------------

//Takes no parameters
//Scans for and validates input
//Returns output string that may contain: character corresponding to function call, string filename, and/or error code
//output[-1] contains output code referring to the number of parameters in the output string
//----------2 -> output has function character and filename
//----------1 -> output has only function character
//----------0 -> output is invalid
char * getInput(){
    
    char input[256];//Original string collected

    char function; //Refers to user function to be called
    char filename[256]; //Filename parameter
    char check[256]; //Checks for extra inputs i.e. F <filename> <garbage> 
    
    //Allocate output string
    char * output = malloc(256 * sizeof(char));

    //Collect input
		printf("\n: ");
    fgets(input, sizeof(input), stdin);

    //Check that input starts with a single character
    sscanf(input, " %s %s", check, filename);
    if((int)strlen(check) > 1){
      strcat(output, "_error_");
      output[-1] = '0';
      return output;
    }

    //Scan input into respective parameters
    sscanf(input, " %c %s", &function, filename);
    
    //Get number of parameters scanned
    int nInput = sscanf(input, " %c %s %s", &function, filename, check);

    //Add proper parameters to output string
    //Set output code at output[-1]
    switch(nInput){
      case 2:
        strncat(output, &function, 1);
        strcat(output, " ");
        strcat(output, filename);
        output[-1] = '2';
        break;
      case 1:
        strncat(output, &function, 1);
        output[-1] = '1';
        break;
      case 3:
      default:
        strcat(output, "_error_");
        output[-1] = '0';
    }
  
  return output;
}


//Takes string filename parameter
//Reads text file of integers seperated by commas
//Returns integer array of integers found in file
//Stores array length at output[-1]
int * readFile(char * filename){

		int * output = malloc(256 * sizeof(int)); //Integer output array
		int index = 0; //Integer index value
		char data[511]; //String data read from file. Output taking 256 max integers, 511 characters with commas between entries
		char * ptr; //To parse data by commas

    //Open the file
		FILE * file;
		file = fopen(filename, "r");

    //Check that file opened successfully
		if(!file) {
			output[-1] = -1;
      return output;
		}

    //Read data into input array
		fscanf(file, "%s", data);
		fclose(file);

    //Split data by commas, add integers to output array
		ptr = strtok(data, ",");
		while(ptr){
			int a = atoi(ptr);
			output[index] = a;
			index++;
			ptr = strtok(NULL, ",");
		}
		
    //Store array length
		output[-1] = index;

		return output;
}

//Takes no parameters
//Takes user input when manual data entry is selected
//Reads non-zero integer values one at a time until terminating character 'X' is input
//Returns integer output array containing these values
int * getValues(){

  char input[256]; //Stores input
  int * output = malloc(256 * sizeof(int)); //Integer output array
  int index = 0; //Integer index

  //Print header
  sprintf(s, "Enter non-zero integer values one at a time, then 'X' to submit\n");

  do {
    //Update GUI
    display();

    //Take input
    printf("\n: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; //removes excess newline
    
    //Check that input is an integer---------------------------*(causes 0 to be ommitted from usable data entries)
    //Add integer to output array
    //Update GUI with previous input values
    if(atoi(input) != 0){
      output[index] = atoi(input);
      index++;
      strcat(s, input);
      strcat(s, " ");
    }
    
    //Repeat until 'X' is entered
  } while ((int)strlen(input) != 1 || toupper(input[0]) != 'X');

  //Store array length 
  output[-1] = index;

  return output;
}

//Takes integer array and integer array length value
//Iterates through array and inserts each integer into a red-black tree
//No return value
void buildTree(int arr[256], int arrLen){
 
    //Loops tree insertion
    for (int i = 0; i < arrLen; i++) {
 
      insertion(arr[i]);
    }

}

//inorder helper function
//Takes no parameters
//Allocates string to return inorder traversal values
char * inorderOutput(){

	char * output = malloc(256 * sizeof(char));
	inorderTraversal(root, output);
	return output;

}

//Takes no paramters
//No return value
void printTree(){
	
	char output[256] = ""; //Output string
  char temp[256] = ""; //Temporary string
	char * traversal = inorderOutput(); //Input array containing tree nodes

  //Print header
	strcat(output, "In-order Traversal: ");
  //Remove excess arrow at end of string
  traversal[strlen(traversal)-2] = '\0';
  //Add traversal to output string
	strcat(output, traversal);

  //Print header
	strcat(output, "\nHeight: ");
  //Scan integer value into temp
  sprintf(temp, "%d", maxDepth(root)+1); // +1 Accounts for black leaf nodes
  //Add temp to output string
  strcat(output, temp);

	strcat(output, "\nBlack Height: ");
  sprintf(temp, "%d", blackHeight(root));
  strcat(output, temp);

	strcat(output, "\nSecond Largest Element: ");
  sprintf(temp, "%d", secondMax(root));
  strcat(output, temp);

  strcat(output,"\n");
	sprintf(s, "%s", output);
  
}

//Takes red-black tree root node
//Returns second highest value found in tree
int secondMax(struct rbNode * root){

  struct rbNode * temp = root; //Placeholder node

  //Follows the right-most path down the tree until the second highest value is reached
  while(temp->link[1]->link[1] != NULL){
    temp = temp->link[1];
  }

  return temp->data;

}

//Takes red-black tree root node
//Returns blackheight of the tree
int blackHeight(struct rbNode * root){
  
  int count = 0; //Number of black nodes found

  //Every path from root to leaf in a red-black tree contains the same number of black nodes
  //Follow the rightmost path from root to leaf
  //Increment count each time a black node is passed
  //Includes black root node
  struct rbNode * temp = root;

  while(temp!= NULL){
    if(temp->color == BLACK){
      count++;
    }
    temp = temp->link[1];
  }

  return count;

}

//Takes no parameters
//No return value
//Clears output window, prints header, prints command list, prints current output via global output string
void display(){

 system("clear");

 printf("              _   _     _            _      _   \n");              
 printf("             | | | |   | |          | |    | |    \n");            
 printf(" _ __ ___  __| | | |__ | | __ _  ___| | __ | |_ _ __ ___  ___ \n");
 printf("| '__/ _ \\/ _` | | '_ \\| |/ _` |/ __| |/ / | __| '__/ _ \\/ _ \\\n");
 printf("| | |  __/ (_| | | |_) | | (_| | (__|   <  | |_| | |  __/  __/\n");
 printf("|_|  \\___|\\__,_| |_.__/|_|\\__,_|\\___|_|\\_\\  \\__|_|  \\___|\\___|\n");

 printf("\n\nCommands \n");
 printf("F - <filename.txt> - Read values from a file to create a red black tree.\n");
 printf("E ------------------ Enter values to create a red black tree.\n");
 printf("X ------------------ Exit red black tree generator.\n");


  printf("\n%s", s);

}

//Takes no parameters
//Further validates input and makes respective function calls
//No return value
void eventHandler(){

  //Update Display
  display(s);

  //Take input
  char * input = getInput();

  char function; //Regers to main user functions F, E, or X

  char filename[256]; //Will hold filename
  
  //Input code determines which function calls are possible
  //i.e. if a single character is passed, E and X are possible
  switch(input[-1]){
    case '2':
      sscanf(input, " %c %s", &function, filename);

      switch(toupper(function)){
        case 'F':
					user_F(filename);
        break;

        default:
          sprintf(s, "Error (2): Invalid Input.");
      }
      break;
    case '1':
      sscanf(input, " %c", &function);

      switch(toupper(function)){
      case 'E':
        user_E();
				
        break;
			
			case 'X':
				sprintf(s, "Exiting...");
				exit(0);
				break;

      default:
        sprintf(s, "Error (1): Invalid Input");
        break;
      }

      break;
    case '0':
      sprintf(s, "Error (0): Invalid Input");
      break;
    default:
      sprintf(s, "Error: Default Reached");
      break;
  }
  
}

//--------------------------------------------------------------------------Main User Functions
//---------------------------------------------------------------------------------------------

//Takes string filename
//Reads data from file, builds red-black tree from data, displays tree data
//No return value
void user_F(char * filename){

  //Read integer data into array
  int * data = readFile(filename);

  //Check that the file exists and/or opened correctly
	if(data[-1] == -1){
		sprintf(s, "Error (-1): filename error.");
		return;
	}

  //Create and display the tree
	buildTree(data, data[-1]);
	printTree();

  //Reset global red-black tree for next function call
  root = NULL;

}

//Takes no parameters
//Takes user input for red-black tree values
//Builds and displays tree from input data
//No return value
void user_E(){

  //Read user input into array
  int * data = getValues();

  //Create and display the tree
	buildTree(data, data[-1]);
	printTree();

  //Reset global red-black tree for next function call
  root = NULL;
  
}

//---------------------------------------------------------------------------------redBlackTree
//---------------------------------------------------------------------------------------------



