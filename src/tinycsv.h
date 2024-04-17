#ifndef TINYCSV_H
#define TINYCSV_H

#include <stdio.h>

typedef struct {
    FILE* fptr; // holds the file pointer
    char* lineptr; // points to the current line
    size_t linesize; // size of the current line
    size_t num_cols; // number of columns in the csv file
    char delimiter; // delimiter used in the csv file
} CsvParser;

static size_t csv_colcount(char* line, char delim);

CsvParser* csv_open_file(const char* filename, char delim);

void csv_free_parser(CsvParser* parser);

char** csv_read_line(CsvParser* parser);

#endif // TINYCSV_H
