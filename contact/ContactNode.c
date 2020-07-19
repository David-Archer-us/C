#include <stdio.h>
#include <string.h>

#include "ContactNode.h"

// for creating new ContactNode
void CreateContactNode(ContactNode* thisNode, char name[59], char phone[20], ContactNode* node)
{
   strcpy((*thisNode).contactName, name);
   strcpy((*thisNode).contactPhoneNum, phone);
   thisNode->nextNodePtr = node;
}

// for inserting a new ContactNode
void InsertContactAfter(ContactNode* thisNode, ContactNode* newNode)
{
   ContactNode* tmp = thisNode->nextNodePtr;
   thisNode->nextNodePtr = newNode;
   newNode->nextNodePtr = tmp;
}

// for returnting the next ContactNode of a certain ContactNode
ContactNode* GetNextContact(ContactNode* thisNode)
{
   return thisNode->nextNodePtr;
}

// for printing a ContactNode
void PrintContactNode(ContactNode* thisNode)
{ 
   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n", thisNode->contactPhoneNum);
}
   
