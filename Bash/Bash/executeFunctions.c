//
//  executeFunctions.c
//  Bash2
//
//  Created by preetham chandra on 29/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#include "executeFunctions.h"
#include "history.h"
#define HISTORY_FILE "history.txt"
#include <strings.h>
#include <stdlib.h>
#include  <sys/types.h>

void readLast10Lines(size_t hist_size, char *historyBuffer[], size_t *hisBufferNextPosition);

void executeProgram(char* args[], size_t hist_size, char *historyBuffer[], size_t *hisBufferNextPosition, int* should_run){
    if(!strcmp(args[0], "exit")){
        *should_run = 0;/* closes program by quitting the loop in main*/
    }
    else if(!strcmp(args[0], "history")){
        printLast10Lines(historyBuffer, hisBufferNextPosition, hist_size);
    }
    else if(!strcmp(args[0], "!!")){
        //execute last command
        execLastCommand(historyBuffer, hisBufferNextPosition, hist_size, -1, should_run);
    }
    else if(*args[0] == '!'){
        //execute last command
        //printf("hi");
        *args[0]++;
        //printf("%s", args[0]);
        int x = atoi(args[0]);
        if(x > 0){
            execLastCommand(historyBuffer, hisBufferNextPosition, hist_size, x, should_run);
        }else{
            printf("Error: Invalid Entry, make argument greater than 0\n");
        }
    }
    else{
        int status;
        pid_t pid = fork();
        if (pid < 0) {     /* fork a child process           */
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }
        else if (pid == 0) {          /* for the child process:         */
            if (execvp(args[0], args) < 0) {     /* execute the command  */
                printf("*** ERROR: exec failed\n");
                exit(1);
            }
        }
        else {                                  /* for the parent:      */
           while (wait(&status) != pid)
            ;       /* wait for completion  */
        }
    }
}
void printLast10Lines(char *historyBuffer[], size_t *hisBufferNextPosition, size_t hist_size){
    writeToHistoryFile(historyBuffer, hisBufferNextPosition);
    
    //save to array then print in reverse
    FILE *f = fopen(HISTORY_FILE, "r");
    if(f!=NULL){
        int i=0;
        char *line = NULL; size_t len, num;
        char *temp[10];
        if(hist_size<10){
                while((getline(&line, &len, f)!= EOF) && i<10){
                temp[i] = (char*)malloc(80);
                strcpy(temp[i++], line);
            }
            for (i--, num = hist_size; i>=0; i--,num--) {
                printf("%zu %s", num, temp[i]);
            }
        }
        else{
            for(i=0; i<hist_size-10; i++){
                getline(&line, &len, f);
            }
            i=0;
            while((getline(&line, &len, f)!= EOF) && i<10){
                temp[i] = (char*)malloc(80);
                strcpy(temp[i++], line);
            }
            size_t num = hist_size;
            for (i=9; i>=0; i--,num--) {
                printf("%zu %s", num, temp[i]);
            }
        }
    }
    fclose(f);
}
void execLastCommand(char *historyBuffer[], size_t *hisBufferNextPosition, size_t hist_size, int flag, int* should_run){
    writeToHistoryFile(historyBuffer, hisBufferNextPosition);
    FILE *f = fopen(HISTORY_FILE, "r");
    if(f!=NULL){
        int i=0;
        char *line = NULL; size_t len, num;
        if(flag < 0){
            for(i=0; i<hist_size-1; i++){
                getline(&line, &len, f);
            }
            char *argtemp[41];
            stringTokeniser(argtemp, line);
            executeProgram(argtemp, hist_size, historyBuffer, hisBufferNextPosition,should_run);
        }
        else{
            if(flag > hist_size){
                printf("Error: Invalid Entry, argument is larger than number of lines in history");
            }
            else{
                for(i=0; i<flag; i++){
                    getline(&line, &len, f);
                }
                char *argtemp[41];
                stringTokeniser(argtemp, line);
                executeProgram(argtemp, hist_size, historyBuffer, hisBufferNextPosition,should_run);
            }
    }
    fclose(f);
    }
}
