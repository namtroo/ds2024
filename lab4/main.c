#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void map(char *input);
void reduce();

int main() {
    char line[1024];

  
    while (fgets(line, sizeof(line), stdin) != NULL) {
        map(line);
    }

   
    reduce();

    return 0;
}
