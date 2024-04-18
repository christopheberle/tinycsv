#ifndef TINYCSV_H
#define TINYCSV_H

#include <stdio.h>

typedef struct {
    FILE* fptr; // holds the file pointer
    char* lineptr; // points to the current line
    size_t linesize; // size of the current line
    size_t num_cols; // number of columns in the csv file
    char delimiter; // delimiter used in the csv file
} CSVFILE;

static size_t csv_colcount(char* line, char delim);

CSVFILE* csvopen(const char* filename, char delim);

void csvclose(CSVFILE* file);

char** csvreadl(CSVFILE* file);

#endif // TINYCSV_H
