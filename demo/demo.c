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
    CsvParser* parser = csv_open_file(filename, ';');
    if (parser == NULL) { perror("Error"); return EXIT_FAILURE; } // csv_open_file() failed

    printf("Found %zu columns\n", parser->num_cols);
    size_t nrows = 2; // number of rows to read
    for (size_t i = 0; i < nrows; i++) {
        char **line = csv_read_line(parser);
        if (errno != 0) { perror("Error"); exit(EXIT_FAILURE); } // csv_read_line() failed
        for (size_t j = 0; j < parser->num_cols; j++) {
            printf("%s ", line[j]);
            free(line[j]);
        }
        printf("\n");
        free(line);
    }
    csv_free_parser(parser);
    return EXIT_SUCCESS;
}
