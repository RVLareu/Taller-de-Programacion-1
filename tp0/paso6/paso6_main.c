#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "paso6_wordscounter.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, char* argv[]) {
    FILE* input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        input = stdin;
    }

    if (! input) {
        return ERROR;
    } else {
        wordscounter_t counter;
        wordscounter_create(&counter);
        wordscounter_process(&counter, input);
        size_t words = wordscounter_get_words(&counter);
        printf("%zu\n", words);
        wordscounter_destroy(&counter);
        if (input != stdin)
            fclose(input);
        return SUCCESS;
    }
}

