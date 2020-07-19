#ifndef CONTACTNODE_H
#define CONTACTNODE_H

// struct ContactNode
typedef struct Contact_struct{
   char contactName[50];
   char contactPhoneNum[50];
   struct Contact_struct* nextNodePtr;
}ContactNode;

// functions for ContactNode
void CreateContactNode(ContactNode* thisNode, char name[59], char phone[20], ContactNode* node);
void InsertContactAfter(ContactNode* thisNode, ContactNode* newNode);
ContactNode* GetNextContact(ContactNode* thisNode);
void PrintContactNode(ContactNode* thisNode);

#endif
