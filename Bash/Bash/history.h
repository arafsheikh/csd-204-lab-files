//
//  history.h
//  Bash
//
//  Created by preetham chandra on 27/01/17.
//  Copyright © 2017 preetham chandra. All rights reserved.
//

#ifndef history_h
#define history_h
void displayHistory(char*[], size_t);
void writeToHistoryTemp(char*[],char*, size_t);
void writeToHistoryFile(char*[]);
int numHistory();
size_t countHistory();
void initializeBuffer(char*[], size_t);
#endif /* history_h */
