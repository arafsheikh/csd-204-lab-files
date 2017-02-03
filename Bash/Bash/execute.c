//
//  execute.c
//  Bash_final
//
//  Created by preetham chandra on 02/02/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//
#define HISTORY_FILE "history.txt"
#define MAX_LINE 80
#include "execute.h"
#include "history.h"
#include <string.h>
#include <stdlib.h>
void executeProgram(char **args, int *should_run, char *temp_string, size_t *historyCount, char **historyBuffer, size_t *hisBufferNextPosition){
    if(temp_string[0] == '\0') /* do nothing for blank input*/
        return ;
    
    (*historyCount)++;
    char temp_string2[MAX_LINE];
    strcpy(temp_string2, temp_string);
    //string tokenise
    stringTokeniser(args, temp_string2);
    if(temp_string[0] == '!'){ /* special ! cases*/
        //write to history
        writeToHistoryFile(historyBuffer, hisBufferNextPosition);
        if(temp_string[1] == '!'){
            temp_string = retriveCommandFromHistory(-1, *historyCount);
        }
        else{
            temp_string++;
            int x = atoi(temp_string);
            if(x>0){
                temp_string = retriveCommandFromHistory(x, *historyCount);
            }
        }
        strcpy(temp_string2, temp_string);
        //string tokenise
        stringTokeniser(args, temp_string2);
    }
    //write to buffer
    writeToHistoryBuffer(temp_string, historyBuffer, hisBufferNextPosition);
    if(!strcmp(args[0], "exit")){
        *should_run = 0;
    }
    else if(!strcmp(args[0], "history")){
        //write to history
        writeToHistoryFile(historyBuffer, hisBufferNextPosition);
        //print lines
        printLast10Lines(*historyCount);
    }
    else{
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            if (execvp(args[0], args) == -1) {
                exit(2);
            }
        }
        else if (pid > 0) {
            // parent process
            int childStatus;
            int detach = 0;
            if (detach) {
                waitpid(pid, &childStatus, WNOHANG);
                usleep(10000); // sleep for 0.1 sec for prompt to show
            } else {
                waitpid(pid, &childStatus, 0);
            }
        }
        else {
            // fork failed
            printf("fork() failed!\n");
            exit(2);
        }    }
}

void stringTokeniser(char*args[], char s[]){ /*splits s[] into words and saves into args[]*/
    char *token = strtok(s, " ");
    size_t i=0;
    char *ptr = s; // points to starting of s[]
    while(*ptr != '\0'){ //removes all spaces, tabs, and new lines
        if(*ptr == ' ' || *ptr == '\t' ||*ptr == '\n')
            *ptr = '\0';
        ptr++;
    }
    while (token) {
        //printf("token: %s\n", token);
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}
