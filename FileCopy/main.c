/* Name: ID:
 Teammate name(s):
 Explain your steps as comments in the code itself.
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: ./filecopy inputFile outputFile\n");
        exit(1);
    }
    char* SRC_FILE = argv[1];
    char* DES_FILE = argv[2];

    int fd[2];
    pid_t pid;
    pipe(fd); /* create pipe */

    if((pid = fork()) == -1){
        perror("Fork error");
        exit(1);
    }
    else if(pid == 0){
        /* child only reads. Close the write end */
        close(fd[WRITE_END]);
        /* Open the destination file and read from pipe */
        /* Create the destination file if it does not exist */
        FILE *f = fopen(DES_FILE, "wb");
        if (f == NULL) {
            printf("Error opening destination file\n");
            exit(1);
        }
        char ch;
        while(read(fd[READ_END], &ch, sizeof(ch))){
            fprintf(f, "%c", ch);
        }
        
        fclose(f);
        close(fd[READ_END]);
    }
    else{
        /* parent only writes. Close the read end */
        close(fd[READ_END]);
        /* Open the source file and write to pipe */
        /* Print error message if the source file does not exist */
        FILE *f = fopen(SRC_FILE, "rb");
        if (f == NULL) {
            printf("Source file does not exist\n");
            exit(1);
        }
        char ch;
        while ((ch = getc(f)) != EOF) {
            write(fd[WRITE_END], &ch, sizeof(ch));
        }
        fclose(f);
        close(fd[WRITE_END]);
    }
    return 0;
}
