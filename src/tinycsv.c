#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tinycsv.h"

static size_t csv_colcount(char* line, char delim) {
    size_t colcount = 0;
    while (*line != '\0') {
        if (*line == delim || *line == '\n') {
            colcount++;
        }
        line++;
    }
    return colcount;
}

CSVFILE* csvopen(const char* filename, char delim) {
    CSVFILE* reader = malloc(sizeof(CSVFILE));
    if (!reader) { free(reader); errno = ENOMEM; return NULL; } // malloc() failed

    FILE* fptr = fopen(filename, "r");
    if (!fptr) { free(reader); return NULL; } // fopen() failed

    // read the first line -> infer number of fields -> rewind fptr to beginning of file
    char* lineptr = NULL;
    size_t linesize = 0;
    ssize_t read = getline(&lineptr, &linesize, fptr);
    if (read == -1) { errno = EIO; return NULL; } // getline() failed

    size_t num_cols = csv_colcount(lineptr, delim);
    free(lineptr);
    linesize = 0;
    rewind(fptr); // reset to file pointer to beginning of file
    
    reader->fptr = fptr;
    reader->lineptr = NULL;
    reader->linesize = linesize;
    reader->num_cols = num_cols;
    reader->delimiter = delim;
    return reader;
}

void csvclose(CSVFILE* file) {
    fclose(file->fptr);
    free(file->lineptr);
    free(file);
}

char** csvreadl(CSVFILE* file) {
    if (feof(file->fptr)) { errno = EOF; return NULL; } // reached end of document

    ssize_t read = getline(&(file->lineptr), &(file->linesize), file->fptr);
    if (read == -1) { errno = EIO; return NULL; }

    char** line_contents = malloc((file->num_cols) * sizeof(char*)); // malloc() failed
    if (!line_contents) { errno = ENOMEM; return NULL; } // getline() failed

    size_t fidx = 0;
    char* p = file->lineptr;
    char* q = file->lineptr;
    
    while (*q != '\0') {
        if (*q == file->delimiter || *q == '\n') {
            char* content = malloc((q - p + 1) * sizeof(char)); // +1 for '\0' terminator
            if (!content) {
                errno = ENOMEM;
                // cleanup
                for (size_t i = 0; i < fidx; i++) {
                    free(line_contents[i]);
                }
                free(content);
                free(line_contents);
                return NULL;
            }
            strncpy(content, p, q-p); // copy from p to q into contents
            line_contents[fidx] = content;
            fidx++; 
            q++; // advance past ';'
            p = q;
        }
        q++;
    }
    return line_contents;
}