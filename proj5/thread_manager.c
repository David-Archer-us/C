#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "Node.h"
/***
 * This file will be in charge of managing different threads which will run through a runner
 * and each thread will have a specific action to do
 */

//thread mutex lock for access to the log index
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for critical sections of allocating THREADDATA
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for access to the head node of the Node Linked List
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*); //thread runner
pthread_t tid1, tid2; //the threads that wil be ran
struct THREADDATA_STRUCT {
    pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA; //THREADDATA that will be initialized by one of the threads

THREADDATA* p = NULL;

//variable for indexing of messages by the logging function
int logindex = 1;
int* logip = &logindex;

Node* headNode = NULL;

//A flag to indicate if the reading of input is complete,
//so the other thread knows when to stop
bool is_reading_complete = false;

/*********************************************************
// function main  -------------------------------------------------
 main method which will create the threads and run them through thread runner
*********************************************************/
int main()
{
    //create first thread
    pthread_create(&tid1, NULL, thread_runner, NULL);
    //created the second thread
    pthread_create(&tid2, NULL, thread_runner, NULL);
    //wait for first thread to exit
    pthread_join(tid1, NULL);

    //wait for second thread to exit
    pthread_join(tid2, NULL);
    exit(0);

} //end main

/***
 * function which will print the current time
 */
void printTime()
{
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);

    hours = local->tm_hour; // get hours since midnight (0-23)
    minutes = local->tm_min; // get minutes passed after the hour (0-59)
    seconds = local->tm_sec; // get seconds passed after minute (0-59)

    day = local->tm_mday; // get day of month (1 to 31)
    month = local->tm_mon + 1; // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    // print local time
    if (hours < 12) // before midday
        printf("%02d/%02d/%d %02d:%02d:%02d am : ", day, month, year, hours, minutes, seconds);

    else // after midday
        printf("%02d/%02d/%d %02d:%02d:%02d pm : ", day, month, year, hours - 12, minutes, seconds);
    return;
}

/**********************************************************************
// function thread_runner runs inside each thread --------------------------------------------------
**********************************************************************/
void* thread_runner(void* x)
{
    char buf[50]; //buffer
    pthread_t me;
    me = pthread_self(); //getting the thread number
    pthread_mutex_lock(&tlock2); // critical section starts
    pthread_mutex_lock(&tlock1); //start of critical section
    printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
    printTime();
    printf("Starting the created thread %ld (p=%p)\n", me, p);
    logindex++;
    pthread_mutex_unlock(&tlock1); //end critical section
    if (p == NULL) {
        p = (THREADDATA*)malloc(sizeof(THREADDATA));
        p->creator = me;
        pthread_mutex_lock(&tlock1); // critical section starts
        printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
        printTime();
        printf("created the THREADDATA %p\n", p);
        logindex++;
        pthread_mutex_unlock(&tlock1); //critical section ends
    }
    else {
        pthread_mutex_lock(&tlock1); //critical section starts
        printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
        printTime();
        printf("can access the THREADDATA %p\n", p);
        logindex++;
        pthread_mutex_unlock(&tlock1); //critical section ends
    }
    pthread_mutex_unlock(&tlock2); // critical section ends

    if (p->creator == me) { // if the thread is thread 1, since the pcreator is equal to the thread number of thread 1

        while (fgets(buf, 50, stdin)) {
            if (strchr(buf, '\n') != NULL) { //checks if there is any '\n' characters and removes it

                buf[strlen(buf) - 1] = '\0';
            }
            if (strlen(buf) != 0) { //if the string is not empty

                if (headNode == NULL) {
                    Node* newNode = (Node*)malloc(sizeof(Node)); //creating a new node
                    newNode->data = (char*)malloc(sizeof(char) * 50); //initializing char* of node
                    CreateNewNode(newNode, buf, NULL);
                    pthread_mutex_lock(&tlock3); //critical section starts
                    headNode = newNode;
                    pthread_mutex_lock(&tlock1); // critical section starts
                    printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
                    printTime();
                    printf("Created Linked List and new node at %p\n", newNode);
                    logindex++;
                    pthread_mutex_unlock(&tlock1); //critical section ends
                    pthread_mutex_unlock(&tlock3); //cirtical section ends
                }
                else {
                    if (strcmp(headNode->data, buf) != 0) {
                        Node* newNode = (Node*)malloc(sizeof(Node)); //creating a new node
                        newNode->data = (char*)malloc(sizeof(char) * 50); //initializing char* of node
                        CreateNewNode(newNode, buf, headNode);
                        pthread_mutex_lock(&tlock3); //critical section starts
                        headNode = newNode;
                        pthread_mutex_lock(&tlock1); // critical section starts
                        printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
                        printTime();
                        printf("created new node at %p and inserted  Linked List\n", newNode);
                        logindex++;
                        pthread_mutex_unlock(&tlock1); //critical section ends
                        pthread_mutex_unlock(&tlock3); //critical section ends
                    }
                }
            }
            else {
                break; //breaks if the node is empty
            }
        }
        is_reading_complete = true; //sets is_reading_complete to true since the reading is done
    }
    else { // thread 2
        Node* tempNode = NULL;
        while (!is_reading_complete) {
            pthread_mutex_lock(&tlock3);
            if (headNode != tempNode) { //if the head node has changed
                pthread_mutex_lock(&tlock1);
                printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
                printTime();

                printf("Head of linked list contains data: %s\n", headNode->data);
                logindex++;
                pthread_mutex_unlock(&tlock1);
                tempNode = headNode;
            }
            pthread_mutex_unlock(&tlock3);
        }
    }
    pthread_mutex_lock(&tlock2); //critical section starts
    if (p != NULL && p->creator == me) {
        pthread_mutex_lock(&tlock1); //critical section starts
        printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
        printTime();
        printf("did not touch THREADDATA (p=%p)\n", p);
        logindex++;
        pthread_mutex_unlock(&tlock1); //crtical section ends
    }
    else {
        free(p); //freeing THREADDATA
        p = NULL;
        pthread_mutex_lock(&tlock1); //critical section starts
        printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
        printTime();
        printf("deleted the THREADDATA and set the data to NULL (p=%p)\n", p);
        logindex++;
        pthread_mutex_unlock(&tlock1); //critical section ends
        if (headNode != NULL) {
            pthread_mutex_lock(&tlock3); //critical section start
            Node* temp1;
            Node* temp2;
            temp1 = headNode;
            temp2 = GetNextNode(temp1);
            free(temp1->data);
            free(temp1); //frees the head
            while (temp2 != NULL) { //looping through linked list and freeing
                temp1 = GetNextNode(temp2);
                free(temp2->data);
                free(temp2);
                temp2 = temp1;
            }
            pthread_mutex_lock(&tlock1); //critical section starts
            printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
            printTime();
            printf("deallocated all nodes of the linked List\n");
            logindex++;
            pthread_mutex_unlock(&tlock1); //critical section ends
            pthread_mutex_unlock(&tlock3); //critical sectiond ends
        }
    }
    pthread_mutex_unlock(&tlock2);
    pthread_mutex_lock(&tlock1); //critical section starts
    printf("Logindex %d, thread %ld, PID %ld,", *logip, me, (long)getpid());
    printTime();
    printf("Exiting Thread Runner\n");
    logindex++;
    pthread_mutex_unlock(&tlock1); //critical section ends

    pthread_exit(NULL); //thread exits

} //end thread_runner
