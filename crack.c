#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"
#include "fileutil.h"

#define PASS_LEN 50
#define HASH_LEN 33


int compareHashes(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <hash_file> <dictionary_file>\n", argv[0]);
        exit(1);
    }

    
    int size;
    char **hashes = loadFileAA(argv[1], &size);

    
    qsort(hashes, size, sizeof(char *), compareHashes);

    
    FILE *dict_file = fopen(argv[2], "r");
    if (!dict_file) {
        perror("Failed to open dictionary file");
        exit(1);
    }

    int cracked_count = 0;
    char password[PASS_LEN];

    
    while (fgets(password, sizeof(password), dict_file)) {
        password[strcspn(password, "\n")] = '\0'; 
        
        
        char *hashed_password = md5(password, strlen(password));

        
        if (bsearch(&hashed_password, hashes, size, sizeof(char *), compareHashes)) {
            printf("Cracked: %s -> %s\n", password, hashed_password);
            cracked_count++;
        }

        free(hashed_password); 
    }

    fclose(dict_file);
    freeAA(hashes, size); 

    printf("Total hashes cracked: %d\n", cracked_count);

    return 0;
}
