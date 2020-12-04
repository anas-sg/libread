//Example program to test functions from read.h
#include "read.h"

int main(void) {
    char **lines = read_lines("test/input.txt");
    // char **lines = read_lines("test/test.txt");
    puts("Done");
    printf("%s\n", lines[0]);
    printf("%s\n", lines[1]);
    printf("%s\n", lines[2]);   
}