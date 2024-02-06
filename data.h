
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATA_H__
#define DATA_H__

// Define the Cell data type
typedef struct {
    float value;
    char* label;
    char alignment;
    char* formula;
} Cell;


#endif /* TEST_H__*/