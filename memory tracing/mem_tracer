// Implement a program mem_tracer.c that reads all lines from an input file,
// Implement tracing of memory consumption.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "CommandNode.h"

// TRACE_NODE_STRUCT is a linked list of
// pointers to function identifiers
// TRACE_TOP is the head of the list is the top of the stack
struct TRACE_NODE_STRUCT {
  char* functionid;                      // ptr to function identifier
  struct TRACE_NODE_STRUCT* next;  // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/* --------------------------------*/
/* function PUSH_TRACE */
void PUSH_TRACE(char* p)          // push p on the stack
{
  TRACE_NODE* tnode;
  static char glob[]="global";

  if (TRACE_TOP==NULL) {

    // initialize the stack with "global" identifier
    TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (TRACE_TOP==NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
    }

    TRACE_TOP->functionid = glob;
    TRACE_TOP->next=NULL;
  }

  // create the node for p
  tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

  // no recovery needed if allocation failed, this is only
  // used in debugging, not in production
  if (tnode==NULL) {
    printf("PUSH_TRACE: memory allocation error\n");
    exit(1);
  }

  tnode->functionid=p;
  tnode->next = TRACE_TOP;  // insert fnode as the first in the list
  TRACE_TOP=tnode;          // point TRACE_TOP to the first node
}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
void POP_TRACE()    // remove the top of the stack
{
  TRACE_NODE* tnode;
  tnode = TRACE_TOP;
  TRACE_TOP = tnode->next;
  free(tnode);
  free(TRACE_TOP);
}/*end POP_TRACE*/



/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: funcA:funcB:funcC.  */
char* PRINT_TRACE()
{
  int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
  int i, length, j;
  TRACE_NODE* tnode;
  static char buf[100];

  if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
    strcpy(buf,"global");   // still in the `global' area
    return buf;
  }

  /* peek at the depth top entries on the stack, but do not
     go over 100 chars and do not go over the bottom of the
     stack */

  sprintf(buf,"%s",TRACE_TOP->functionid);
  length = strlen(buf);                  // length of the string so far
  for(i=1, tnode=TRACE_TOP->next;
                        tnode!=NULL && i < depth;
                                  i++,tnode=tnode->next) {
    j = strlen(tnode->functionid);             // length of what we want to add
    if (length+j+1 < 100) {              // total length is ok
      sprintf(buf+length,":%s",tnode->functionid);
      length += j+1;
    }else                                // it would be too long
      break;
  }
  return buf;
}

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// For instance, example of print out:
// "File tracemem.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
	p = realloc(p,t);

  printf("File \"%s\", line %d, funciton=%s, reallocated the memory segment at address %p to a new size %d\n",
    file, line, PRINT_TRACE(), p, t);
	return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// For instance, example of print out:
// "File tracemem.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
	void* p;
	p = malloc(t);
  printf("File \"%s\", line %d, funciton=%s, allocated new memory segment at address %p to size %d\n",
    file, line, PRINT_TRACE(), p, t);
	return p;
}

// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// For instance, example of print out:
// "File tracemem.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
	free(p);
  printf("File \"%s\", line %d, funciton=%s, deallocated the memory segment at address %p\n",
    file, line, PRINT_TRACE(), p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)


// -----------------------------------------
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
 void add_row(char*** commands,int limit)
 {
   PUSH_TRACE("add_row");
   *commands = (char**)realloc(*commands, sizeof(char*)*limit);
   for(int i = 0; i < limit/2; ++i)
     (*commands)[i] = (char*)realloc((*commands)[i], sizeof(char)*100);
   for (int i = limit/2; i < limit; ++i){
     (*commands)[i] = (char*)malloc(sizeof(char)*100);
     for (int j = 0; j < 100; j++)
       (*commands)[i][j] = '\0';
   }

      //commands = (char**)realloc(commands, sizeof(char*)*limit);
      //for(int i = 0; i < limit/2; ++i)
      //  commands[i] = (char*)realloc(commands[i], sizeof(char)*100);
      //for (int i = limit/2; i < limit; ++i){
      //  commands[i] = (char*)malloc(sizeof(char)*100);
      //  for (int j = 0; j < 100; j++)
      //    commands[i][j] = '\0';
      //}
    
   POP_TRACE();
   return;
 }// end add_row


// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array(char* file)
{
  PUSH_TRACE("make_extend_array");
  CommandNode *headCommand;
  CommandNode *newCommand;
  int limit = 100;
  char **commands;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i, j;
  FILE *fp = fopen(file, "r");
  if(fp == NULL)
  {
    exit(EXIT_FAILURE);
  }

  commands = (char**) malloc(sizeof(char*)*limit);  // 100 rows
  for(i=0; i<limit; i++) {
    commands[i]=(char*) malloc(sizeof(char)*100);  // 100 columns
    for(j=0; j<100; j++)
      commands[i][j]='\0';
  }
  int index = 0;
  while((read = getline(&line, &len, fp)) != -1)
  {
    //make array
    if (index < limit)
    {
      strcpy(commands[index], line);
    }
    else
    {
      limit = limit*2;
      // printf("before add_row, limit: %d\n", limit);
      // fflush(stdout);
      add_row(&commands,limit);
      

      //commands = (char**)realloc(commands, sizeof(char*)*limit);
      //for(int i = 0; i < limit/2; ++i)
      //  commands[i] = (char*)realloc(commands[i], sizeof(char)*100);
      //for (int i = limit/2; i < limit; ++i){
      //  commands[i] = (char*)malloc(sizeof(char)*100);
      //  for (int j = 0; j < 100; j++)
      //    commands[i][j] = '\0';
      //}


      // printf("after add_row, index: %d\n", index);
      // fflush(stdout);
      strcpy(commands[index], line);
    }
    

    if (index == 0)
    {
        headCommand = (CommandNode*)malloc(sizeof(CommandNode));
        CreateCommandNode(headCommand, commands[index], index+1, NULL);
    }
    else
    {
        newCommand = (CommandNode*)malloc(sizeof(CommandNode));
        CreateCommandNode(newCommand, commands[index], index+1, NULL);
        InsertCommandAfter(headCommand, newCommand);
    }

    index++;
  }
  if(line) free(line);
  fclose(fp);
  // for(int i = 0; i < index; ++i)
  // {
  //   printf("index %d: %s\n", i, commands[i]);
  //   fflush(stdout);
  // }

  PrintNodes(headCommand);

  //now deallocate it
  for(i=0; i<limit; i++)
    free((void*)commands[i]);
  free((void*)commands);

  while(headCommand != NULL)
  {
    newCommand = headCommand;
    headCommand = headCommand->nextCommandPtr;
    free(newCommand);
  }

  POP_TRACE();
  return;
}//end make_extend_array



// ----------------------------------------------
// function main
int main(int argc, char *argv[])
// int main()
{
  PUSH_TRACE("main");
  int fout;
  if ((fout = open("memtrace.out", O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0)
  {
    exit(1);
  }
  dup2(fout, 1);
  make_extend_array(argv[1]);
  POP_TRACE();
  return(0);
}// end main

