//
//  history.h
//  Bash_final
//
//  Created by preetham chandra on 02/02/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#ifndef history_h
#define history_h

#include <stdio.h>
#define HISTORY_FILE "history.txt"
size_t countHistory();
void writeToHistoryBuffer(char *temp_string, char **historyBuffer, size_t *hisBufferNextPosition);
void writeToHistoryFile(char **historyBuffer, size_t *hisBufferNextPosition);
void printLast10Lines(size_t historyCount);
char* retriveCommandFromHistory(int lineNumber, size_t historyCount);
#endif /* history_h */
