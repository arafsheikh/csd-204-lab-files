#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *unsorted, *sorted;

/* structure for passing data to threads */
typedef struct {
    int start;
    int end;
} parameters;

void *sort(void* positions);
void *merge(void* positions);

int main(int argc, const char * argv[]) {
    int i;
    
    unsorted = (int*) malloc((argc-1)*sizeof(int));
    sorted = (int*) malloc((argc-1)*sizeof(int));
    for(i=0; i < argc-1; i++) {
        unsorted[i] = atoi(argv[i+1]);
    }
    
    
    printf("Before sorting:\n");
    for(i = 0; i<argc-1; i++){
        printf("%d ", unsorted[i]);
    }

    pthread_t t1, t2, t3;
    parameters p1, p2, p3;
    p1.start = 0;
    p1.end = (argc-1)/2;
    
    pthread_create(&t1, NULL, sort, (void*) &p1);
    p2.start = ((argc-1)/2);
    p2.end = argc-1;
    
    pthread_create(&t2, NULL, sort, (void*) &p2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    p3.start = 0;
    p3.end = argc-1;
    pthread_create(&t3, NULL, merge, (void*) &p3);
    pthread_join(t3, NULL);
    printf("\n\nAfter sorting:\n");
    for(i = 0; i<argc-1; i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");
    
    return 0;
}

void *sort(void *positions){
    int temp = 0;
    parameters* pos = (parameters*) positions;
    int i, j;
    for(i = pos->start; i < pos->end; i++) {
        for(j= i+1; j< pos->end; j++) {
            if(unsorted[i]> unsorted[j]) {
                temp = unsorted[i];
                unsorted[i] = unsorted[j];
                unsorted[j] = temp;
            }
        }
    }
    pthread_exit(0);
}

void *merge(void* positions) {
    parameters* pos = (parameters*) positions;
    int argc = pos->end;
    int i=0, j=(argc/2), k=0;
    while(i < argc/2 && j < argc) {
        if(unsorted[i] < unsorted[j]) {
            sorted[k] = unsorted[i];
            i++;
        }
        else {
            sorted[k] = unsorted[j];
            j++;
        }
        k++;
    }

    while(i < argc/2) {
        sorted[k] = unsorted[i];
        i++;
        k++;
    }

    while(j < argc) {
        sorted[k] = unsorted[j];
        j++;
        k++;
    }
}
