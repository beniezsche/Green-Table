#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



int main() {
    char *input = "@SUM(A1...A3)";

    int p = 0;

    while(p < strlen(input)) {
        printf("%c", input[p]);
        p++;
    }
    

    return 0;
}