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
void readLast10Lines(size_t hist_size, char *historyBuffer[], size_t *hisBufferPoint);

void executeProgram(char* args[], size_t hist_size, char *historyBuffer[], size_t *hisBufferPoint){
    if(!strcmp(args[0], "history")){
        printLast10Lines(historyBuffer, hisBufferPoint, hist_size);
    }
}
void printLast10Lines(char *historyBuffer[], size_t *hisBufferPoint, size_t hist_size){
    writeToHistoryFile(historyBuffer, hisBufferPoint);
    
    //save to array then print in reverse
    FILE *f = fopen(HISTORY_FILE, "r");
    if(f!=NULL){
        int i;
        char *line = NULL; size_t len;
        for(i=0; i<hist_size-10; i++){
            getline(&line, &len, f);
        }
        char *temp[10]; i=0;
        while((getline(&line, &len, f)!= EOF) && i<10){
            temp[i] = (char*)malloc(80);
            strcpy(temp[i++], line);
        }
        size_t num = hist_size;
        for (i=9; i>=0; i--,num--) {
            printf("%zu %s", num, temp[i]);
        }
    }
    fclose(f);
}
