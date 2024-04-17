# tinycsv

tinycsv is a minimal library for reading .csv / .tsv files in C.

**Disclaimer**: This library is not production ready and just a personal project of mine. 

## Usage

To get started open up a CSV file using `CsvParser* csv_open_file(const char* filename, char delimiter)` as follows

```C
#include "tinycsv.h"

int main() {
    CsvParser* parser = csv_open_file("some_file.csv", ';');
    ...
```

The function returns a pointer to a `CsvParser` struct defined below

```C
typedef struct {
    FILE* fptr; // holds the file pointer
    char* lineptr; // points to the current line
    size_t linesize; // size of the current line
    size_t num_cols; // number of columns in the csv file
    char delimiter; // delimiter used in the csv file
} CsvParser;
```

Note that `csv_open_file` initialises this struct for you so there is no need to set any of these fields. If initialisation fails a `NULL` pointer is returned and `errno` is set accordingly.

Next, to actually read a CSV file, tinycsv exposes a `char** csv_read_line(CsvParser* parser)` function which reads the current line in the file, returning a `char` double pointer which can be indexed from `0` to `parser->num_cols` yielding the `n`-th column value of the current row.

For example, to print the first two lines of the CSV file we opened above we can do

```C
...
size_t nrows = 2;

for (size_t i = 0; i < nrows; i++) {
    char** line_contents = csv_read_line(parser);
    for (size_t j = 0; j < parser->num_cols; j++) {
        printf("%s\t", line_contents[j]);
    }
    printf("\n");
}
...
```

Finally, in order to close the file and free the parser, tinycsv exposes a convenience function `void csv_free_parser(CsvParser* parser)`.

```C
...
csv_free_parser(parser);
return EXIT_SUCCESS;
}
```