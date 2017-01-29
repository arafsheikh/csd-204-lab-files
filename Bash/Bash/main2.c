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
    size_t his_num = 0;
    his_num = countHistory();
    printf("%zu\n",his_num);
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
