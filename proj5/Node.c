/*
 * Filename: Node.h
 * Implmentation of the function of the linked list
 
 * This file allows one to create a linked list
 * using nodes which holds text data
*/

#include "Node.h"
#include <string.h>
#include <stdio.h>

/***
 * method which will create and intialize a new node
 * @param thisNode - the node that will be initalized
 * @param data - the text data in the method
 * @param nextNode - the nextNode that the current node will point to
 */
void CreateNewNode(Node* thisNode, char* data, Node* nextNode) {
    strcpy(thisNode->data, data);
    thisNode->nextNodePtr = nextNode;
    return;
}

/***
 * insert a node after another node
 * @param thisNode - the node that the new node will be inserted after
 * @param newNode  - the new node that will be inserted after
 */
void InsertNodeAfter(Node* thisNode, Node* newNode) {
    Node* tmpNext = NULL;
    tmpNext = thisNode->nextNodePtr;
    thisNode->nextNodePtr = newNode;
    newNode->nextNodePtr = tmpNext;
    return;
}

/***
 * gets the next node in the list
 * @param thisNode - the node in which the method will get the next node
 * @return - the next node in the list
 */
Node* GetNextNode(Node* thisNode) {
    return thisNode->nextNodePtr;
}

/***
 * recursive method which will print the nodes of the linked list
 * @param head - the head of the linked list
 */
void printNodes(Node* head){
    Node* temp;
    printf("Node Index: %d, Data: %s\n",head->index, head->data);
    temp = GetNextNode(head);
    if(temp != NULL){
        printNodes(temp); //recursive calling
    }
    return;
}