#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_usage(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    return 0;
}

int longest_word(FILE *file) {
    // Check if the file is NULL
    if (file != NULL) {
        // Allocate memory to store words
        int i = 0;
        // String to store largest word (Initially must be null-terminated)
        char * largest = malloc(102 * sizeof(char));
        *largest = '\0';
        // String to store the current word
        char * result = malloc(102 * sizeof(char));

        // Iterate through characters one at a time
        while (!feof(file)) {
            // Copy current character to next spot in buffer
            fread(result + i, 1, 1, file);

            // See if last character was end of word
            if (!feof(file) && (strncmp(result + i, "\n", 1) == 0 ||
                strncmp(result + i, " ", 1) == 0)) {
                // If so, null terminate the string
                *(result + i) = '\0';
                i = 0;

                // Set new largest word if necessary
                if (strlen(result) > strlen(largest)) {
                    strcpy(largest, result);
                }

                // Don't increment i if we are on new word (want i = 0)
                continue;
            }
            i += 1;
        }
        // Check if there were any words
        if (strlen(largest) > 0) {
            printf("%s\n", largest);
        }

        // Free allocated memory
        free(result);
        free(largest);

        // Return successfully
        return 0;
    }

    // Return nonzero value for NULL file pointer
    return -1;
}




int main(int argc, char *argv[]) {
    if (check_usage(argc, argv)) {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    int exit = longest_word(f);
    if (exit != 0) {
        printf("longest: %s: No such file or directory\n", argv[1]);
    }
    else {
        fclose(f);
    }
    return exit;
}
