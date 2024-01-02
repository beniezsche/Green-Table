#include <stdio.h>
#include <stdlib.h>

#define CHUNK 12;

#define ROWS 4
#define COLUMNS 2

struct Cell {
    int content_int;
    char content_string[50];
};

int main() {

    // int* cols[COLUMNS];

    // for(int j = 0; j < COLUMNS; j++) {
    //     int* p = calloc(ROWS, sizeof(int));
    //     *(p+0) = 1 + j;
    //     *(p+1) = 2 + j;
    //     *(p+2) = 3 + j;
    //     *(p+3) = 4 + j;

    //     cols[j] = p;
    // }


    // for(int i = 0; i < COLUMNS; i++) {
    //     for (int j = 0; j < ROWS; j++) {
    //         printf("p[%d] is %d \n", j, (*(cols[i]+j)));
    //     }
        
    // }

    int rows = 5;
    int columns = 2;


    struct Cell cells[rows][columns];

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j].content_int = j + 1;
        }
    }

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf(" %d ", cells[i][j].content_int);
        }
        printf("\n");
    }





    



    return 0;
}

