#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reduce() {
    char current_word[1024];
    char word[1024];
    int count = 0;

    while (scanf("%s\t%d\n", word, &count) == 2) {
        if (strcmp(word, current_word) != 0) {
            if (count > 0) {
                printf("%s\t%d\n", current_word, count);
            }
            strcpy(current_word, word);
            count = 0;
        }
        count += 1;
    }
    if (count > 0) {
        printf("%s\t%d\n", current_word, count);
    }
}
