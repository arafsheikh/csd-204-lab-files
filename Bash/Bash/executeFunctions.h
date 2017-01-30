//
//  executeFunctions.h
//  Bash2
//
//  Created by preetham chandra on 29/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#ifndef executeFunctions_h
#define executeFunctions_h

#include <stdio.h>
void executeProgram(char*[], size_t, char *[], size_t*);
void printLast10Lines(char *historyBuffer[], size_t *hisBufferNextPosition, size_t hist_size);
//void printLast10Lines(size_t hist_size, char *historyBuffer[], size_t *hisBufferNextPosition);
#endif /* executeFunctions_h */
