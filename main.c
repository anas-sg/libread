//Example program to test functions from read.h
#include <stdio.h>
#include "read.h"

void read_words_test(void) {
    puts("Enter some words:");
    char **words = read_words(stdin, NULL);
    puts("Words entered:");
    for (int i = 0; (words[i]); printf("%s\n", words[i++]));
}

void input_test(void) {
    char *line = input("Enter a line of text:\n");
    printf("Line entered:\n%s\n", line);
}


int main(void) {
    read_words_test();
    input_test();    
}