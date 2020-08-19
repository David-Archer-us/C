//
// Created by cs149 on 7/6/20.
//

#ifndef AS3A_COMMANDNODE_H
#define AS3A_COMMANDNODE_H


/**
 * *CommandNode.h
 * *Author: Bill Andreopoulos
 * *The struct for a Command Node and function prototypes
 * for a linked list of commands *CS149 assignment 3 usage only
 **/
typedef struct command_struct {
    char *command;
    int index;
    struct command_struct* nextCommandPtr;
} CommandNode;

void CreateCommandNode(CommandNode* thisNode, char *line, int index, CommandNode* nextCmd);
void InsertCommandAfter(CommandNode* thisNode, CommandNode* newNode);
CommandNode* GetNextCommand(CommandNode* thisNode);
CommandNode* FindCommand(CommandNode* thisNode, int index);
void PrintNodes(CommandNode* headNode);


#endif //AS3A_COMMANDNODE_H