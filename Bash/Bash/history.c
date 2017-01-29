//
//  history.c
//  Bash
//
//  Created by preetham chandra on 27/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "history.h"
#define HIS_FILE "history.txt"
#define MAX_LINE 80
size_t countHistory(){
    //works
    size_t count = 0, len = 0;
    FILE *f = fopen(HIS_FILE, "r");
    char *line = NULL;
    if(f!=NULL){
        while (getline(&line, &len, f) != EOF)
            count++;
    }
    fclose(f);
    return count;
}

void initializeBuffer(char*historyBuffer[10], size_t his_len){
    //working
    size_t lineNum1 = his_len%(10);
    size_t lineNum2 = his_len - lineNum1;
    size_t i=0,j=0,len;
    
    FILE *f = fopen(HIS_FILE, "r");
    //traverse file
    char *line = NULL;
    if(f!=NULL){
        while (i++ < lineNum2){
            getline(&line, &len, f);
        }
        //printf("his len is %zu\nbuff start %zu", his_len, lineNum2);
        for (i=lineNum2, j=0; i<his_len; i++) {
            if(f != NULL){
                getline(&historyBuffer[j++], &len, f);
            }
        }
    }
    fclose(f);
}

void displayHistory(char* hisBuff[], size_t hisNum){
    int i=9, j;
    while (i>=0) {
        if(hisBuff[i]!=NULL)
            printf("%zu %s\n",(hisNum--), hisBuff[i]);
        i--;
    }
}

void writeToHistoryTemp(char* historyBuffer[10], char *s, size_t his_num){
    size_t i = his_num%10;
    if(i==0){
        //write to file
        writeToHistoryFile(historyBuffer);
        //free space
        size_t j;
        //for(j=0; j<10; j++){
            //if(historyBuffer[i] != NULL)
                free(historyBuffer);
        //}
        printf("hi");
    }
    historyBuffer[i] = (char *) malloc(80);
    strcpy(historyBuffer[i], s);
    /*
    if (i != 0) {
        //something
        historyBuffer[i] = (char *) malloc(80);
        strcpy(historyBuffer[i], s);
    }
    else{
        //strcpy(historyBuffer[i], s);
        //writeToHistoryFile(historyBuffer);
    }
     */
    /*
    FILE *f = fopen(HIS_FILE, "a");
    if(f == NULL){
        printf("Error opening history file");
        exit(1);
    }
    fprintf(f, "%s", strcat(s, "\n"));
    fclose(f);
     */
}
void writeToHistoryFile(char* historyBuffer[10]){
    FILE *f = fopen(HIS_FILE, "a");
    if(f == NULL){
        printf("Error opening history file");
        exit(1);
    }
    size_t i;
    for(i=0; i<10 && historyBuffer!=NULL; i++){
        fprintf(f, "%s", historyBuffer[i]);
    }
    fclose(f);
}
