#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "src/tinycsv.h"

int main(int argc, char* argv[]) {
    // handle command line arguments
    if (argc < 2) {
        errno = EINVAL;
        perror("Error");
        printf("Please provide a file path.");
        return EXIT_FAILURE;
    }
    char* filename = argv[1];

    printf("Attempting to read file %s\n", filename);
    CSVFILE* file = csvopen(filename, ';');
    if (file == NULL) { perror("Error"); return EXIT_FAILURE; } // csvopen() failed

    printf("Found %zu columns\n", file->num_cols);
    size_t nrows = 2; // number of rows to read
    for (size_t i = 0; i < nrows; i++) {
        char **line = csvreadl(file);
        if (errno != 0) { perror("Error"); exit(EXIT_FAILURE); } // csvreadl() failed
        for (size_t j = 0; j < file->num_cols; j++) {
            printf("%s ", line[j]);
            free(line[j]);
        }
        free(line);
        printf("\n");
    }
    csvclose(file);
    return EXIT_SUCCESS;
}
