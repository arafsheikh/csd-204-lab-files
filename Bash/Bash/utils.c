#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

#define HISTORY_FILE ".osh_history"

/*
 * Remove the trailing new line character from the given string
 * and insert a NULL character in the end
 */
int cleanArgs(char *string) {
    string = strtok(string, "\n");
    char* temp[2];
    temp[0] = string;
    temp[1] = NULL;
    if (string[strlen(string)-1] == '&') {
        string = strtok(string, "&");
        string = *temp;
        return 1;
    } else {
        string = *temp;
        return 0;
    }
    
}

/*
 * Save the given string to the HISTORY_FILE
 */
void saveToHistory(char *string) {
    FILE *f = fopen(HISTORY_FILE, "a");
    if (f == NULL) {
        printf("Error saving to history\n");
        exit(1);
    }
    fputs(string, f);
    fputs("\n", f);
    fclose(f);
}

/*
 * Print the last `lines` from the HISTORY_FILE
 * 
 * lines: number of lines to print
 */
void readFromHistory(int lines) {
    // base case
    if (lines <= 0)
       return;

    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    int count = 0; // line count in file
    char *line; size_t len;
    while (getline(&line, &len, f) != EOF)
        count++;
    rewind(f); // return cursor to initial position in file
    int i=count;
    for (i -= lines+1; getline(&line, &len, f) != EOF; i--) {
        if (i < 0) {
            printf("%d\t%s", count-i, line);
        }
    }
    fclose(f);
}

/*
 * Fetch the string on the given line number from the history file
 */
char* getLine(int number) {
    // base case
    if (number <= 0)
       return NULL;

    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    char *line; size_t len;
    while (number--) {
        getline(&line, &len, f);
    }
    return line;
}

/*
 * Get the total number of lines in the history file
 */
int getTotalLines() {
    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    int count = 0; // line count in file
    char *line; size_t len;
    while (getline(&line, &len, f) != EOF)
        count++;
    return count;
}

/*
 * Execute the given string as a command
 */
void mexec (char* str, int detach) {
    pid_t pid = fork();
        if (pid == 0) {
            // child process
            if (execvp(&str[0], &str) == -1) {
                exit(2);
            }
        }
        else if (pid > 0) {
            // parent process
            int childStatus;
            if (detach) {
                waitpid(pid, &childStatus, WNOHANG);
                usleep(10000); // sleep for 0.1 sec for prompt to show
            } else {
                waitpid(pid, &childStatus, 0);
            }
        }
        else {
            // fork failed
            printf("fork() failed!\n");
            exit(2);
        }
}

/*
 * Function responsible to run any command from the shell
 */
void execCommand(char* str, int detach) {
    if (!strcmp(str, "history")) {
        readFromHistory(10);
    }
    else if (str[0] == '!' && str[1] == '!') {
        printf("%s", getLine(getTotalLines() - 1));
        mexec(getLine(getTotalLines() - 1), 0);
    }
    else if (str[0] == '!') {
        char* temp = str;
        temp++;
        printf("%s", getLine(atoi(temp)));
        mexec(getLine(atoi(temp)), 0);
    }
    else {
        mexec(str, detach);
    }
}
