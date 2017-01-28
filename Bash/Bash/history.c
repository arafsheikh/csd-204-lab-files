//
//  history.c
//  Bash
//
//  Created by preetham chandra on 27/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "history.h"
#define HIS_FILE "history.txt"
#define MAX_LINE 80
size_t countHistory(){
    size_t count = 0;
    FILE *file = fopen(HIS_FILE, "r");
    char line[MAX_LINE];
    if (file != NULL){
        while (fgets(line, sizeof(line), file) != NULL)
        {
                count++;
        }
        fclose(file);
    }
    return count;
}

void initializeBuffer(char*historyBuffer[], size_t his_len){
    size_t lineNum1 = his_len%(10);
    size_t lineNum2 = his_len - lineNum1;
    size_t i=0,j;
    
    FILE *f = fopen(HIS_FILE, "r");
    //traverse file
    if(f!=NULL){
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), f) != NULL) {
            if(i == lineNum2)
                break;
        }
    }
    for (i=lineNum2, j=0; i<his_len && j<10; i++, j++) {
        if(f != NULL){
            
        }
    }
    /*
     lineNumber = x;
     
     static const char filename[] = "file.txt";
     FILE *file = fopen(filename, "r");
     int count = 0;
     if ( file != NULL )
     {
     char line[256]; /* or other suitable maximum line size
    while (fgets(line, sizeof line, file) != NULL) /* read a line
    {
        if (count == lineNumber)
        {
            //use line or in a function return it
            //in case of a return first close the file with "fclose(file);"
        }
        else
        {
            count++;
        }
    }
    fclose(file);
}
else
{
    //file doesn't exist
}
     */
}

void displayHistory(){
    FILE *f = fopen("history.txt", "r");
    if(f == NULL){
        printf("Error reading history file");
        exit(1);
    }
    size_t numberOfLen = 0;
    char *line = NULL;
    /*
     while (i--) {
     getline(&line, &len, f);
     printf("%s", line);
     }
     */
    fclose(f);
}

void writeToHistory(char s[], size_t his_num){
    char *historyBuffer[20];
    if (his_num%10 != 0) {
        <#statements#>
    }
    else{
        
    }
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

int numHistory(){
    int numberOfLen = 0;
    FILE *f = fopen("history.txt", "r");
    if(f == NULL){
        printf("Error reading history file");
        exit(1);
    }
    size_t len=0;
    char *line = NULL;
    while (getline(&line, &len, f)) {
        numberOfLen++;
    }
    return numberOfLen;
}
