#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "src/tinycsv.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        errno = EINVAL;
        perror("Error");
        errno = 0;
        printf("Please provide a file path.");
        return EXIT_FAILURE;
    }
    char* filename = argv[1];
    printf("Attempting to read file %s\n", filename);
    CsvParser* reader = csv_open_file(filename, ';');
    if (reader == NULL) {
        perror("Error");
        errno = 0;
        return EXIT_FAILURE;
    }
    printf("Found %zu columns\n", reader->num_cols);
    for (size_t i = 0; i < 3; i++) {
        char **line = csv_read_line(reader);
        if (errno != 0) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        for (size_t j = 0; j < 4; j++) {
            printf("%s ", line[j]);
            free(line[j]);
        }
        printf("\n");
        free(line);
    }
    csv_free_parser(reader);
    return EXIT_SUCCESS;
}
