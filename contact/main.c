#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "ContactNode.h"

int main(void) {
   // set up the size and tracing both head node and nail node of the linked list
   int SIZE = 3;
   ContactNode* headNode = (ContactNode*)malloc(sizeof(ContactNode));
   ContactNode* nailNode = (ContactNode*)malloc(sizeof(ContactNode));
   headNode = nailNode;
   
   // for loop for getting user input
   for (int i = 0; i < SIZE; ++i)
   {
      char name[59];
      char phoneNumber[20];
      ContactNode* newNode = (ContactNode*)malloc(sizeof(ContactNode));
      printf("Person %d\n", i+1);
      printf("Enter name:\n");
      fgets(name, 59, stdin);
      name[strlen(name)-1] = '\0';
      printf("Enter phone number:\n");
      fgets(phoneNumber, 20, stdin);
      printf("You entered: %s, %s\n", name, phoneNumber);
      
      // set up the Linked list
      CreateContactNode(newNode, name, phoneNumber, NULL);
      InsertContactAfter(nailNode, newNode);
      nailNode = nailNode->nextNodePtr;
   }
   headNode = headNode->nextNodePtr;
   
   // print out the linked list
   ContactNode* traversingNode = headNode;
   printf("\nCONTACT LIST\n");
   while(traversingNode != NULL)
   {
      PrintContactNode(traversingNode);
      traversingNode = traversingNode->nextNodePtr;
   }
   printf("\n");
   free(headNode);
   return 0;
}

