//-------------------------------------------------------------------------------------elevator
//---------------------------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>
#include "elevator.h"

//Global output string
char os[256];

//---------------------------------------------------------------------------Externally Sourced
//---------------------------------------------------------------------------------------------

/***************************************************************************************
*    Title: Queue | Set 1 (Introduction and Array Implementation)
*    Author: GeeksforGeeks
*    Date: 09 April, 2022
*    Availability: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
*
***************************************************************************************/


// A structure to represent a queue
struct Queue {
	int front, rear, size;
	unsigned capacity;
	int* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue = (struct Queue*)malloc(
		sizeof(struct Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = capacity - 1;
	queue->array = (int*)malloc(
		queue->capacity * sizeof(int));
	return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1)
				% queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	//printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1)
				% queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue
int front(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

// Function to get rear of queue
int rear(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}

//-----------------------------------------------------------------------------------------Main
//---------------------------------------------------------------------------------------------

int main(void){
 
 //Ensure output line is blank on program start
 strcpy(os, " "); 

 //Run system until program is exited
 for(;;){
 	eventHandler(os);
 }

}

//-----------------------------------------------------------------------------Helper Functions
//---------------------------------------------------------------------------------------------

//Takes no parameters
//Scans for and validates input
//Returns output string that may contain: character corresponding to function call,
//integers floors, start, goal, up, and down, and/or error code
//output[-1] contains output code referring to the number of parameters in the output string
//----------6 -> output has function character and f, s, g, u, d
//----------1 -> output has only function character
//----------0 -> output is invalid
char * getInput(){
    
    char input[256];//Original string collected

    char function; //Refers to user function to be called
    char f[256]; //Floor, start, goal, up, down parameters
    char s[256];
    char g[256];
    char u[256];
    char d[256];
    char check[256]; //Checks for extra inputs i.e. :I <f>...<d> <garbage> 
    
    //Allocate output string
    char * output = malloc(256 * sizeof(char));

    //Collect input
		printf("\n: ");
    fgets(input, sizeof(input), stdin);


    //Check that input starts with a single character
    //sscanf(input, " %s %s", check, filename);
    sscanf(input, " %s %s", check, f);
    if((int)strlen(check) > 1){
      strcat(output, "_error_");
      output[-1] = '0';
      return output;
    }

    //Scan input into respective parameters
    sscanf(input, " %c %s %s %s %s %s", &function, f, s, g, u, d);
    
    //Get number of parameters scanned
    int nInput = sscanf(input, " %c %s %s %s %s %s %s", &function, f, s, g, u, d, check);

    //Add proper parameters to output string
    //Set output code at output[-1]
    switch(nInput){
      case 6:
        strncat(output, &function, 1);
        strcat(output, " ");
        strcat(output, f);
        strcat(output, " ");
        strcat(output, s);
        strcat(output, " ");
        strcat(output, g);
        strcat(output, " ");
        strcat(output, u);
        strcat(output, " ");
        strcat(output, d);
        output[-1] = '6';
        break;
      case 1:
        strncat(output, &function, 1);
        output[-1] = '1';
        break;
      default:
        strcat(output, "_error_");
        output[-1] = '0';
    }
  
  return output;
}


//Takes no parameters
//No return value
//Clears output window, prints header, prints command list, prints current output via global output string
void display(){

 system("clear");

 printf("       _                 _\n");
 printf("      | |               | |\n");                 
 printf("   ___| | _____   ____ _| |_ ___  _ __\n");                 
 printf("  / _ \\ |/ _ \\ \\ / / _` | __/ _ \\| `__|\n");                 
 printf(" |  __/ |  __/\\ V / (_| | || (_) | | \n");                 
 printf("  \\___|_|\\___| \\_/ \\__,_|\\__\\___/|_| \n");                 



 printf("\n\nCommands \n");
 printf("I --<f>-<s>-<g>-<u>-<d>-- Input floors, start, goal, up, down.\n");
 printf("X ----------------------- Exit elevator.\n");
  
 //Removes extraneous arrow from end of output
 if(os[strlen(os)-2] == '-'){
   os[strlen(os)-2] = '\0';
 }
 
 printf("\n%s", os);

}

//Takes no parameters
//Further validates input and makes respective function calls
//No return value
void eventHandler(){

  //Update Display
  display(os);

  //Take input
  char * input = getInput();

  int f,s,g,u,d; //Input values

  char function; //Refers to main user functions I or X
  
  //Input code determines which function calls are possible
  //i.e. if a single character is passed, only X is possible
  switch(input[-1]){
    case '6':

      sscanf(input, " %c %d %d %d %d %d", &function, &f, &s, &g, &u, &d);

      //Input validation
      if((f < 1 || f > 100) || (s < 1 || s > f) || (g < 1 || g > f) || (u < 0 || u > 100) || (d < 0 || d > 100)){
        sprintf(os, "Error(6): Input out of valid range.");
        break;
      }

      switch(toupper(function)){
        case 'I':
					user_I(f, s, g, u, d);
        break;

        default:
          sprintf(os, "Error (6): Invalid Input.");
      }

      break;

    case '1':

      sscanf(input, " %c", &function);

      switch(toupper(function)){
			  case 'X':
          user_X();
				  break;

      default:
        sprintf(os, "Error (1): Invalid Input");
        break;
      }

      break;

    case '0':
      sprintf(os, "Error (0): Invalid Input");
      break;

    default:
      sprintf(os, "Error: Default Reached");
      break;
  }
  
}

//Takes integer floors, start, goal, up, down values
//Performs a breadth first search of possible elevator floors
//Returns an output array of integers representing the shortest path from start to goal in order
//----------output[-1] Stair indicator; 1 by default, 0 if goal floor is unreachable
//----------output[-2] Stores number of button presses required to reach goal floor
//----------output[-3] Stores output array length
int * elevator(int f, int s, int g, int u, int d){

  //Initialize output array
  int * output = malloc(1000*sizeof(int));

  output[-1] = 1; //Stair indicator: 1 indicates success, 0 indicates failure
  int index = 0; //To iterate through array

  //Run breadth first search
  struct Queue* q = createQueue(1000);
  int visited[1000] = {0};

  //Keep track of parents to record path
  int prev[1000] = {0};

  visited[s] = 1;
  enqueue(q, s);

  if(s!=g){
    
    while(isEmpty(q) == 0){

      int k = front(q);
      dequeue(q);
      
      if(k == g){
        break;
      }

      if(k+u <= f && visited[k+u] == 0){
        enqueue(q, k+u);
        visited[k+u] = visited[k]+1;
        prev[k+u] = k;
      }

      if(k-d >= 1 && visited[k-d] == 0){
        enqueue(q, k-d);
        visited[k-d] = visited[k]+1;
        prev[k-d] = k;
      }
    } 
  } else {
    visited[g] = 1;
  }

  //Reconstruct path in reverse
  for(int i = g; i != 0; i = prev[i]){
      *(output+index) = i;
      index++;
  }

  //Reverse output to correct order
  int temp;
  for(int i = 0; i<(index+0)/2; i++){
    temp = output[i];
    output[i] = output[(index+0)-i-1];
    output[(index+0)-i-1] = temp;
  }

  //If goal was reached
  if(visited[g] != 0){

      //Store button presses 
      output[-2] = visited[g]-1;
      //Store array length
      output[-3] = index;
  
      return output;

  //If goal can't be reached
  } else {

      //Update stair indicator
      output[-1] = 0; 

      return output;
  }
  
}

//--------------------------------------------------------------------------Main User Functions
//---------------------------------------------------------------------------------------------

//Takes integer floors, start, goal, up, down
//Calculates and displays shotest sequence of button presses to get from start to goal
//or "use the stairs" if goal is unreachable
//No return value
void user_I(int f, int s, int g, int u, int d){

  //Set current floor as starting floor
  int curr = s;

  //Array of visited floors
  int vis[100];
  int visIndex = 0;

  //Allocate output string
  char * output = malloc(256 * sizeof(char));
  char temp[256];

  //Add input display to output
  sprintf(temp, "Floors: %d Start: %d Goal: %d Up: %d Down: %d\n", f, s, g, u, d);
  strcat(output, temp);

  //Get elevator path
  int * path = elevator(f,s,g,u,d);

  //If stair indicator is 0
  if(path[-1] == 0){
    //Goal is unreachable, display use the stairs
    sprintf(os, "Use the stairs!");
    return;
  } 

  //Add number of button presses required to output
  sprintf(temp, "Button Presses: %d\n", path[-2]);
  strcat(output, temp);

  //Add path to output
  for(int i = 0; i < path[-3]; i++){
    sprintf(temp, "%d->", path[i]);
    strcat(output, temp);
  }
  
  //Display output
  sprintf(os, "%s", output);
  
}

//Takes no parameters
//Prints exit message and exits program
//No return value
void user_X(){

  sprintf(os, "Exiting...");
	exit(0);
  
}

//---------------------------------------------------------------------------------------Unused
//---------------------------------------------------------------------------------------------

/*
int visited(int n, int vis[100], int visIndex){
  int visited = 0;

  for(int i = 0; i < visIndex; i++){
    if(vis[i] == n){
      visited = 1;
    }
  }

  return visited;
}


//Takes number of floors, up value, down value
//Returns 2D array of floors rows
//Columns: Floor Number, downward neighbor, upward neighbor
//If there is no neighbor, neighbor value is -1
int ** matrix(int floors, int u, int d){

  int * values = calloc(floors*3, sizeof(int));
  int ** matrix = malloc(floors*sizeof(int*));

  for (int i = 0; i < floors; ++i){
    matrix[i] = values + i*3;
  }

  for(int i = 0; i < floors; i++){
    matrix[i][0] = matrix[i][1] = matrix[i][2] = -1;
  }

  for(int i = 0; i < floors; i++){
    int n = i+1;
    matrix[i][0] = n;


    if(n+u <= floors){
      matrix[i][1] = n+u;
    }

    if(n-d > 0){
      matrix[i][2] = n-d;
    }
  
  }

  return matrix;

}

*/

//-------------------------------------------------------------------------------------elevator
//---------------------------------------------------------------------------------------------







