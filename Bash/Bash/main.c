/* Name:
ID: sa421 (Sheikh Araf)
Teammate name(s): pt915 (Preetham Chandra)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#define MAX_LINE 80 /* The maximum length command */

int main(void){
    char args[MAX_LINE]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {
        printf("osh> ");

        // get command from user
        fgets(args, MAX_LINE, stdin);

        // if nothing is entered by the user continue
        if (strlen(args) == 1) {
            continue;
        }

        // check if non blocking command is entered
        int detach = cleanArgs(args);

        // check if quit command is given
        if (!strcmp(args, "quit")) {
            should_run = 0;
            continue;
        }

        // save command to history and run
        saveToHistory(args);
        execCommand(args, detach);

        fflush(stdout);
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) if command included &, parent will invoke wait()
        * (4) if command is quit, the shell should exit
        *  Explain your steps as comments in the code itself.
        */
        }
    return 0;
}
