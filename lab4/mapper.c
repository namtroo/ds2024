#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void map(char *input) {
    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        printf("%s\t%d\n", token, 1);
        token = strtok(NULL, " \t\n");
    }
}
