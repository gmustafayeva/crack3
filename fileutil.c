#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileutil.h"


char **loadFileAA(char *filename, int *size) {
    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Can't open file");
        exit(1);
    }

    int capacity = 10;
    char **arr = (char **)malloc(capacity * sizeof(char *));
    *size = 0;
    char line[256];

    while (fgets(line, sizeof(line), in)) {
        line[strcspn(line, "\n")] = '\0';

        if (*size >= capacity) {
            capacity *= 2;
            arr = (char **)realloc(arr, capacity * sizeof(char *));
        }

        arr[*size] = (char *)malloc(strlen(line) + 1);
        strcpy(arr[*size], line);
        (*size)++;
    }

    fclose(in);
    return arr;
}


char *substringSearchAA(char *target, char **arr, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], target) == 0) {
            return arr[i];
        }
    }
    return NULL;
}

void freeAA(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
