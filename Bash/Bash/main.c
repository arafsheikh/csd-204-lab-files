//
//  main.c
//  Bash2
//
//  Created by preetham chandra on 29/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

/* Name: ID: Preetham Chandra
 Teammate name(s):
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "history.h"
#include "executeFunctions.h"
#define MAX_LINE 80 /* The maximum length command */

//my code

void stringTokeniser(char*[], char[]);
//

int main(void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    
    //my variables
    
    char temp_string[MAX_LINE]; /* temporarily stores input */
    size_t histSize = countHistory();/* stores number of lines in history */
    char *historyBuffer[10]; /* holds 10 values before writing them to file*/
    size_t hisBufferPoint = 0; /* point at next location(for new input)*/
    
    //
    while (should_run) {
        printf("osh>");
        //my code
        
        scanf("%80s",temp_string); /* take input */
        stringTokeniser(args,temp_string); /* parse string and save
                                            into args*/
        writeToBuffer(historyBuffer, &hisBufferPoint, temp_string); /* stores string at hisBuff[BuffPt] and increments BuffPt*/
        histSize++; /* increment history size*/
        executeProgram(args, histSize, historyBuffer, &hisBufferPoint);
        //
        
        fflush(stdout);
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         *  Explain your steps as comments in the code itself.
         */
    }
    //writeToHistoryFile(historyBuffer, hisBufferPoint);
    printf("closing main");
    return 0;
}
