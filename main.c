// all neccessary includes
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80// The maximum length command

// struct for storing command and it's PID
typedef struct {

    pid_t PID;
    char* command;

} History;

History his[MAX_LINE]; // intializing history
int historyIndex = 0;  // index of history

// this function execute all commands
void executeCommand(char* command) {
    int waitStatus = 0;
    int execvpStatus=0;
    pid_t pid;
    char* args[] = {"ls",NULL}; 

    pid = fork(); // fork the child process
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        execvpStatus=execvp(command, args);
        if (strcmp(command, args[0]) == 0 && execvpStatus==-1){
            exit(1);
        } else {
            printf("Invalid command!\n");
            exit(1);
        }
    } else {
        wait(&waitStatus); // waiting for execution
        // store history
        his[historyIndex].command = strdup(command);
        his[historyIndex].PID = pid;
        historyIndex++;
    }
}


// this execute history command
void displayAllHistory() {
    printf("ID  PID  Command\n");
    for (int i = 0; i < historyIndex; i++) {
        printf("%d  %d  %s\n", i, his[i].PID, his[i].command);
    }
}

int main() {
    bool should_run = true;
    char command[MAX_LINE];
    
    while (should_run) {
        printf("CSCI3120> ");
        fgets(command, MAX_LINE, stdin);
        command[strlen(command) - 1] = '\0'; // remove the newline character
        if (strcmp(command, "history") == 0) {
            displayAllHistory();// displaying all commands
            
        }else if(strcmp(command, "!!") == 0){
            if(historyIndex>0){
                executeCommand(his[historyIndex-1].command); // execute most recent command
            }else{
                printf("No command in history!\n");
            }
        }else if(command[0] == '!' && isdigit(command[1])){
            int n = atoi(&command[1]); // convert from string to number
            if (n >= 0 && n < historyIndex) {
                executeCommand(his[n].command);
            }else{
                printf("Such a command is NOT in history!\n");
            }
        }else if(strcmp(command,"exit")==0){
            should_run=false;
        }else{
            executeCommand(command);
        }
    }
    return 0;
}

