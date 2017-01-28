//
//  history.h
//  Bash
//
//  Created by preetham chandra on 27/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#ifndef history_h
#define history_h

#include <stdio.h>
void displayHistory();
void writeToHistory(char [], size_t);
int numHistory();
size_t countHistory();
void initializeBuffer(char*[], size_t);
#endif /* history_h */
