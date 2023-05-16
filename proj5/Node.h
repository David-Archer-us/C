/*
 * Filename: Node.h
 * Specification of the function of the linked list
*/

/****
 * NODE_STRUCT struct which creates a linked list of nodes containing different data
 */
typedef struct node_struct {
    char* data;
    int index;
    struct node_struct* nextNodePtr;
} Node;


/* function prototypes */

/***
 * method which will create and intialize a new node
 * @param thisNode - the node that will be initalized
 * @param data - the text data in the method
 * @param nextNode - the nextNode that the current node will point to
 */
void CreateNewNode(Node* thisNode, char* data, Node* nextNode);

/***
 * insert a node after another node
 * @param thisNode - the node that the new node will be inserted after
 * @param newNode  - the new node that will be inserted after
 */
void InsertNodeAfter(Node* thisNode, Node* newNode);

/***
 * gets the next node in the list
 * @param thisNode - the node in which the method will get the next node
 * @return - the next node in the list
 */
Node* GetNextNode(Node* thisNode);

/***
 * recursive method which will print the nodes of the linked list
 * @param head - the head of the linked list
 */
void printNodes(Node* head);