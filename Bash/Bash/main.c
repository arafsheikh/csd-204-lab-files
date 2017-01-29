/* Name: ID: T. Preetham Chandra
 Teammate name(s):
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINE 80 /* The maximum length command */
#define HIS_LINES 10

//my code
#include "history.h"
void stringTokeniser(char*[], char[]);
void executeFunc(char*[], char*[], size_t);

//
int main(){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    //my code
    size_t his_num = 0;
    char temp_string[MAX_LINE]; /* temporarily stores input */
    his_num = countHistory();
    char *histoyBuffer[10];
    initializeBuffer(histoyBuffer, his_num);
    //
    while (should_run) {
        
        printf("osh>");
        //my code
        scanf("%80s",temp_string); /* take input */
        stringTokeniser(args,temp_string); /* parse string and save
                                                into args*/
        
        writeToHistoryTemp(histoyBuffer, temp_string, his_num++);
        
        //displayHistory(histoyBuffer, his_num);
        
        //printf("done");
        //fflush(stdout);
        //return 0;
        //
        //printf("%zu",his_num);
        executeFunc(args, histoyBuffer, his_num);
        //should_run = 0;
        //
        fflush(stdout);
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         * (4) if command is quit, the shell should exit
         *  Explain your steps as comments in the code itself.
         */
    }
    writeToHistoryFile(histoyBuffer); //save history file before closing
    return 0;
}
//my code
void stringTokeniser(char*args[], char s[]){
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

void executeFunc(char*args[], char*hisBuff[], size_t hisNum){
    if(!strcmp(args[0], "history")){
        //write to file
        displayHistory(hisBuff, hisNum);
    }
    /*
    else if(!strcmp(args[0][0], "!")){
        
    }
     */
    
}
//
