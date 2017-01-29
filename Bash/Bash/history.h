//
//  history.h
//  Bash2
//
//  Created by preetham chandra on 29/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#define history_h

#include <stdio.h>
void stringTokeniser(char*[], char[]);
size_t  countHistory();
void writeToBuffer(char*[], size_t*, char[]);
int writeToHistoryFile(char*[], size_t*);
