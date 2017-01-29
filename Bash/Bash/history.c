//
//  history.c
//  Bash2
//
//  Created by preetham chandra on 29/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#define HISTORY_FILE "history.txt"

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

size_t countHistory(){
    size_t count = 0, len;
    FILE *f = fopen(HISTORY_FILE, "r");
    char *line;
    if(f!=NULL){
        while (getline(&line, &len, f)!= EOF) {
            count++;
        }
    }
    fclose(f);
    return count;
}

void writeToBuffer(char* historyBuffer[], size_t *hisBufferPoint, char temp_string[]){
    historyBuffer[*hisBufferPoint] = (char*)malloc(80);
    strcpy(historyBuffer[*hisBufferPoint], temp_string);
    ++*hisBufferPoint;
    if(*hisBufferPoint == 10){
        writeToHistoryFile(historyBuffer, hisBufferPoint);
    }
    //historyBuffer[hisBufferPoint]
}

int writeToHistoryFile(char* hisBuffer[], size_t *hisBufferPoint){
    size_t i;
    FILE *f = fopen(HISTORY_FILE, "a");
    if(f!=NULL){
        for (i=0; i<*hisBufferPoint; i++) {
            fprintf(f, "%s\n", hisBuffer[i]);
        }
    }
    *hisBufferPoint = 0;
    fclose(f);
    return 1;
}
