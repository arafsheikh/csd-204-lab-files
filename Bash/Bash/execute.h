//
//  execute.h
//  Bash_final
//
//  Created by preetham chandra on 02/02/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#ifndef execute_h
#define execute_h

#include <stdio.h>
void executeProgram(char **args, int *should_run, char *temp_string, size_t *historyCount, char **historyBuffer, size_t *hisBufferNextPosition);
void stringTokeniser(char*args[], char s[]);
#endif /* execute_h */
