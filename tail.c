#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// number of possible length of a line (just printable characters)
#define LINE_MAX 510

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
    long int rows;
    char* filename;
} t_params;

typedef struct {
    int n;
    int capacity;
    char **strings;
} t_strings;

int str_eq(char *str1, char *str2);
void parse_args(int argc, char *argv[], t_params *params);
void init_strings(t_strings *strings);
void insert_line(char *buffer, t_strings *strings, size_t size);
void add_string(char* str_to_add, t_strings *str);
int error();

int main(int argc, char *argv[]) {
    t_params params = {10, NULL};

    // parse arguments
    parse_args(argc, argv, &params);

    FILE *fptr = stdin;

    if (params.filename) {
        fptr = fopen(params.filename, "r");
        if (fptr == NULL) {
            error();
        }
    }

    t_strings strings;
    init_strings(&strings);

    // READING LINES
    int line_i = 1;
    char buffer[LINE_MAX + 3]; // including \0, \n and one extra for checking if not larger than limit
    // fgets reads (n-1) chars + '\0' + one extra possible character for checking limit
    while (fgets(buffer, LINE_MAX + 3, fptr)) {
        int len = strlen(buffer); // (\n is counted)
        if (len > LINE_MAX) {
            // over limit
            fprintf(stderr, "A row number %i is longer than %i characters. The line is stripped.\n", line_i, LINE_MAX);
            len = LINE_MAX;
        }

        // Insert line to structure
        insert_line(buffer, &strings, len);
        line_i++;
    }

    // PRINT LAST LINES
    int from = strings.n - params.rows;
    for(int i = MAX(from, 0); i < strings.n; i++) {
        strings.strings[i][strcspn(strings.strings[i], "\r\n")] = 0;
        printf("%s\n", strings.strings[i]);
    }

    return 0;
}

void insert_line(char *buffer, t_strings *strings, size_t size) {
    // 1. Create by malloc space for line
    // 2. Add this pointer to strings
    char *line = malloc(size);
    if (line == NULL) {
        error();
    }
    // copy from buffer to line
    strncpy(line, buffer, size);

    add_string(line, strings);
}

void init_strings(t_strings *strings) {
    strings->n = 0;
    strings->capacity = 1;
    strings->strings = (char **)malloc(strings->capacity * strings->capacity * sizeof(char *)); // init array of pointers to lines
}

void add_string(char* str_to_add, t_strings *str) {
    str->n++;

    // check if should increase in size
    if (str->capacity <= str->n) {
        str->capacity *= 2;
        str->strings = (char **)realloc(str->strings, str->capacity * sizeof(char *));

        if (str->strings == NULL) {
            // TODO: Destroy strings (?)
            error();
        }
    }

    str->strings[str->n - 1] = str_to_add;
}

void parse_args(int argc, char *argv[], t_params *params) {
    // Load -n parameter
    if (argc == 2) { // only file name
        params->filename = argv[1];
    }
    else if (argc >= 3) { // 0: filename, 1: -n, 2: number
        int n_parameter = 0; // where filename should be located (last parameter)
        if (str_eq("-n", argv[1])) {
            char *end;
            params->rows = strtol(argv[2], &end, 10);
            n_parameter = 1;
            if (end == NULL) {
                error();
            }
        }
        if (n_parameter && argc >= 4) {
            params->filename = argv[argc-1];
        }
    }
}

/**
 * Wrapper function which returns true if two characters are equal
 */
int str_eq(char *str1, char *str2) {
    // strcmp returns 0 when strings are equal
    return !strcmp(str1, str2);
}

int error() {
    fprintf(stderr, "An error has occured.\n");
    exit(1);
}
