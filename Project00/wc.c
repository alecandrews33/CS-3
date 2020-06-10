#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int check_usage(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    return 0;
}

int line_count(FILE *file) {
    int num_lines = 0;
    if (file != NULL) {
        // Allocate memory to store current character
        char * result = malloc(1 * sizeof(char));
        assert(result != NULL);

        while (!feof(file)) {
            // Read current character into buffer
            fread(result, 1, 1, file);
            // Check if at newline character
            if (!feof(file) && strncmp(result, "\n", 1) == 0) {
                // If so, increment counter
                num_lines += 1;
            }
        }

        // Free allocated memory and close the file
        free(result);
        fclose(file);
        return num_lines;
    }
    else {
        // Return impossible value for null file pointer
        return -1;
    }
}




int main(int argc, char *argv[]) {
    if (check_usage(argc, argv)) {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    int count = line_count(f);

    if (count != -1) {
        printf("%d %s\n", count, argv[1]);
        return 0;
    }
    printf("wc: %s: No such file or directory\n", argv[1]);

    return 1;
}
