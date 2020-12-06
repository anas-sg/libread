//Example program to test functions from read.h
#include "read.h"

void read_word_test(void) {
    printf("Enter a word: ");
    char *word = read_word(stdin, NULL);
    printf("Word entered: %s\nEnter to continue...\n", word);
    getchar();
}

void read_words_test(void) {
    printf("Enter some words: ");
    unsigned int count;
    char **words = read_words(stdin, NULL, &count);
    printf("%u Words entered:\n", count);
    for (unsigned int i = 0; (words[i]); printf("%s\n", words[i++]));
    puts("Enter to continue...");
    getchar();
}

void read_line_test(void) {
    puts("Reading a line from crime.csv:");
    FILE *file = fopen("test/crime.csv", "r");
    char *line = read_line(file, NULL);
    printf("%s\n", line);
    puts("Enter to continue...");
    getchar();
}

void read_lines_test(void) {
    puts("Reading lines from test.txt:");
    unsigned int length, i = 0;
    char **lines = read_lines("test/test.txt", &length);
    printf("Done reading %u lines. Printing:\n", length);
    for (char **plines = lines; (*plines); plines++) {
        printf("%u: ", i++);
        printf("%s\n\n", *plines);
    }
    puts("Enter to continue...");
    getchar();
}

void read_file_test(void) {
    puts("Reading test.txt:");
    char *file = read_file("test/test.txt", NULL);
    printf("%s\n", file);
    puts("Enter to continue...");
    getchar();
}

void read_csv_test(void) {
    puts("Reading crime.csv...");
    char ***csv = read_csv("test/crime.csv", ',', NULL);
    puts("Printing some sample cells (based on Excel numbering):");
    printf("B130: %s\n", csv[130 - 1]['B' - 'A']);
    printf("C249: %s\n", csv[249 - 1]['C' - 'A']);
    printf("F4993: %s\n\n", csv[4993 - 1]['F' - 'A']);
}

void input_test(void) {
    char *user_input = input("Enter some text: ");
    printf("You entered:\n%s\n\n", user_input);
}

void scan_folder_test(void) {
    char *ext = input("Enter a file extension, eg. c, h, exe, txt: ");
    printf("Found the following files with extension %s:\n%s", ext, scan_folder(ext));
}

int main(void) {
    read_word_test();
    read_words_test();
    read_line_test();
    read_lines_test();
    read_file_test();
    read_csv_test();
    input_test();
    scan_folder_test();
}