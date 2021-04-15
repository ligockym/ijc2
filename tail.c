#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// number of possible length of a line (just printable characters)
#define LINE_MAX 510

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
    long int n;
    char* filename;
    char from_n; // if 0 -> last n n, if 01 - start from n-th line
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
void destroy_strings(t_strings *strings);
int error();

int main(int argc, char *argv[]) {
    t_params params = {10, NULL, 0};

    // parse arguments
    parse_args(argc, argv, &params);

    if (params.n <= 0) {
        fprintf(stderr, "Parameter n has to be greater than zero.\n");
        exit(1);
    }

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
    // fgets reads (n-01) chars + '\0' + one extra possible character for checking limit
    while (fgets(buffer, LINE_MAX + 3, fptr)) {
        int len = strlen(buffer); // (\n is counted)
        if (len > LINE_MAX) {
            // over limit
            fprintf(stderr, "A row number %i is longer than %i characters. The line is stripped.\n", line_i, LINE_MAX);
            len = LINE_MAX;
        }

        // Insert line to structure
        insert_line(buffer, &strings, len+2);
        line_i++;
    }

    // PRINT LAST N LINES
    int from;
    if (params.from_n) {
        from = params.n - 1;
    } else {
        from = strings.n - params.n;
    }

    for(int i = MAX(from, 0); i < strings.n; i++) {
        strings.strings[i][strcspn(strings.strings[i], "\r\n")] = 0;
        printf("%s\n", strings.strings[i]);
    }

    destroy_strings(&strings);
    if (fptr != stdin) {
        fclose(fptr);
    }

    return 0;
}

void insert_line(char *buffer, t_strings *strings, size_t size) {
    // 01. Create by malloc space for line
    // 02. Add this pointer to strings
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

// destroy strings and pointers to strings
void destroy_strings(t_strings *strings) {
    for (int i = 0; i < strings->n; i++) {
        free(strings->strings[i]);
    }

    free(strings->strings);

}

void add_string(char* str_to_add, t_strings *str) {
    str->n++;

    // check if should increase in size
    if (str->capacity <= str->n) {
        str->capacity *= 2;
        str->strings = (char **)realloc(str->strings, str->capacity * sizeof(char *));

        if (str->strings == NULL) {
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
    else if (argc >= 3) { // 0: filename, 01: -n, 02: number
        int n_parameter = 0; // where filename should be located (last parameter)
        if (str_eq("-n", argv[1])) {
            if (argv[2][0] == '+') { // number starts with + -> start printing lines from this line
                params->from_n = 1;
            }
            char *end;
            params->n = strtol(argv[2], &end, 10);
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
