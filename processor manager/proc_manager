// You will develop a proc_manager program that reads in the commands to execute from an input file one-by-one. 
// You will read one command and its parameters per each line. Then the proc_manager program will start up the process and "babysit" it.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "CommandNode.h"


int main(int argc, char *argv[])
{
    // set up the linked list head and some variables
    CommandNode *headCommand;
    CommandNode *newCommand;
    struct timespec start, finish;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char command[20][20];
    int i,j,ctr;
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int index = 1;
    // read the command file
    while ((read = getline(&line, &len, fp)) != -1)
    {
        for (int i=0; i<20; i++)
            for (int j=0; j<20; j++)
                command[i][j]='\0';
        j=0; ctr=0;
        for(i=0;i<=(strlen(line));i++)
        {
            // if space or NULL found,
            // assign NULL into newString[ctr]
            if(line[i]==' '||line[i]=='\0'||line[i]=='\n')
            {
                command[ctr][j]='\0';
                ctr++;  //for next word
                j=0;  //for next word, init index to 0
            }
            else
            {
                command[ctr][j]=line[i];
                j++;
            }
        }
        // write in the linked list
        if (index == 1)
        {
            headCommand = (CommandNode*)malloc(sizeof(CommandNode));
            CreateCommandNode(headCommand, command, index, NULL);
        }
        else
        {
            newCommand = (CommandNode*)malloc(sizeof(CommandNode));
            CreateCommandNode(newCommand, command, index, NULL);
            InsertCommandAfter(headCommand, newCommand);
        }
        index++;
    }
    fclose(fp);

    // Execute the commands in the linked list
    pid_t pid;
    int status;
    CommandNode *tmpNode;
    tmpNode = headCommand;
    while (tmpNode != NULL) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        tmpNode->starttime = start.tv_sec;
        // make a copy of the command in a node
        char *buf2[23];
        for (int i = 0; i < 20; ++i){
            // buf2[i] = tmpNode->command[i];
            if (tmpNode->command[i][0] != '\0')
                buf2[i] = (char *)&tmpNode->command[i][0];
            else buf2[i] = (char *)0;
        }
        buf2[20] = (char *)0;
        buf2[21] = (char *)0;
        buf2[22] = (char *)0;

        if ((pid = fork()) < 0)
        {
            printf("fork error");
        }
        else if (pid == 0)
        {
            /* child */
            execvp(buf2[0], buf2);
            printf("couldn't execute: %s", buf2[0]);
        }
        else if (pid > 0)
        {
            tmpNode->PID = pid;
        }
        tmpNode = tmpNode->nextCommandPtr;
    } /*end of while loop*/


    // check the elapsed time and write the files
    while((pid = wait(&status)) >= 0) {

        clock_gettime(CLOCK_MONOTONIC, &finish);
        CommandNode *node = FindCommand(headCommand, pid);
        char fileOut[20];
        sprintf(fileOut, "%d.out", node->index);
        FILE *out = fopen(fileOut, "a");
        char fileerr[20];
        sprintf(fileerr, "%d.err", node->index);
        FILE *err = fopen(fileerr, "a");
        int finishtime = finish.tv_sec;
        int elapsed = finishtime-node->starttime;
        fprintf(out, "Starting command %d: child %d pid of parent %d.\n", node->index, pid, getpid());
        fprintf(out, "Finished at %d, runtime duration %d\n", finishtime, elapsed);
        if (WIFEXITED(status)) {
            fprintf(err, "Exit with exitcode = %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            fprintf(err, "Killed with signal: %d\n", WTERMSIG(status));
            // exit(0);
        }
        // check the elapsed time 
        if (elapsed > 2 && WIFEXITED(status))
        {
            // re-fork some commands
            clock_gettime(CLOCK_MONOTONIC, &start);
            node->starttime = start.tv_sec;
            char *buf2[23];
            for (int i = 0; i < 20; ++i){
                // buf2[i] = tmpNode->command[i];
            if (node->command[i][0] != '\0')
                buf2[i] = (char *)&node->command[i][0];
            else buf2[i] = (char *)0;
            }
            buf2[20] = (char *)0;
            buf2[21] = (char *)0;
            buf2[22] = (char *)0;

            if ((pid = fork()) < 0)
            {
                printf("fork error");
            }
            else if (pid == 0)
            {
                /* child */
                execvp(buf2[0], buf2);
                printf("couldn't execute: %s", buf2[0]);
            }
            else if (pid > 0)
            {
                node->PID = pid;
            }
        }
        else
        {
            // write the .err file for closing a command
            fprintf(err, "spawning too fast\n");
        }
        fclose(out);
        fclose(err);
    }
    return 0;
}
