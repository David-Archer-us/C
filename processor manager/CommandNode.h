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
    char command[20][20];
    int index;
    int PID;
    int starttime;
    int finishtime;
    int elapsed;
    int PPID;
    struct command_struct* nextCommandPtr;
} CommandNode;

void CreateCommandNode(CommandNode* thisNode, char cmd[20][20], int ind, CommandNode* nextCmd);
void InsertCommandAfter(CommandNode* thisNode, CommandNode* newNode);
CommandNode* GetNextCommand(CommandNode* thisNode);
CommandNode* FindCommand(CommandNode* cmd, int pid);
CommandNode* FindCommand(CommandNode* cmd, int pid);




#endif //AS3A_COMMANDNODE_H