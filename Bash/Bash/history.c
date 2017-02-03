//
//  history.c
//  Bash_final
//
//  Created by preetham chandra on 02/02/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "history.h"
#define HISTORY_FILE "history.txt"
size_t countHistory(){
    size_t count = 0;
    FILE *f = fopen(HISTORY_FILE, "r");
    if(f!=NULL){
        char *line; size_t len;
        while (getline(&line, &len, f) != EOF) {
            count++;
        }
    }
    return count;
}

void writeToHistoryBuffer(char *temp_string, char **historyBuffer, size_t *hisBufferNextPosition){
    historyBuffer[*hisBufferNextPosition] = (char*)malloc(80);
    strcpy(historyBuffer[*hisBufferNextPosition], temp_string);
    ++*hisBufferNextPosition;
    if(*hisBufferNextPosition == 10){
        writeToHistoryFile(historyBuffer, hisBufferNextPosition);
        *hisBufferNextPosition = 0;
    }
}

void writeToHistoryFile(char **historyBuffer, size_t *hisBufferNextPosition){
    FILE *f = fopen(HISTORY_FILE, "a");
    if(f!=NULL){
        size_t i;
        for (i=0; i<*hisBufferNextPosition; i++) {
            fprintf(f, "%s\n", historyBuffer[i]);
        }
    }
    *hisBufferNextPosition = 0;
    fclose(f);
}

void printLast10Lines(size_t historyCount){
    FILE *f = fopen(HISTORY_FILE, "r");
    if(f!=NULL){
        int i=0;
        char *line = NULL; size_t len, num;
        char *temp[10];
        if(historyCount < 10){
            while((getline(&line, &len, f)!= EOF) && i<10){
                temp[i] = (char*)malloc(80);
                strcpy(temp[i++], line);
            }
            for (i--, num = historyCount; i>=0; i--,num--) {
                printf("%zu %s", num, temp[i]);
            }
        }
        else{
            for(i=0; i<historyCount-10; i++){
                getline(&line, &len, f);
            }
            i=0;
            while((getline(&line, &len, f)!= EOF) && i<10){
                temp[i] = (char*)malloc(80);
                strcpy(temp[i++], line);
            }
            size_t num = historyCount;
            for (i=9; i>=0; i--,num--) {
                printf("%zu %s", num, temp[i]);
            }
        }
    }
    fclose(f);
}

char* retriveCommandFromHistory(int lineNumber, size_t historyCount){
    if(lineNumber == -1){
        lineNumber = (int)(historyCount-1);
    }
    else if(lineNumber > historyCount){
        printf("ERROR: invalid line number\n");
        return NULL;
    }
    size_t i, len; char* line = NULL;
    FILE *f = fopen(HISTORY_FILE, "r");
    for (i=0; i<lineNumber; i++) {
        getline(&line, &len, f);
        //printf("%s\n",line);
    }
    strtok(line, "\n");
    return line;
}

