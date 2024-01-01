#include <stdio.h>
#include <stdlib.h>

#define CHUNK 12;

#define ROWS 4
#define COLUMNS 2

int main() {

    int* cols[COLUMNS];

    for(int j = 0; j < COLUMNS; j++) {
        int* p = calloc(ROWS, sizeof(int));
        *(p+0) = 1 + j;
        *(p+1) = 2 + j;
        *(p+2) = 3 + j;
        *(p+3) = 4 + j;

        cols[j] = p;
    }


    for(int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("p[%d] is %d \n", j, (*(cols[i]+j)));
        }
        
    }

    



    return 0;
}