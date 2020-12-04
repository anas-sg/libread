//Example program to test functions from read.h
#include "read.h"

void read_words_test1(void) {
    //Read words from stdin
    puts("Enter some words:");
    char **words = read_words(stdin, NULL);
    puts("Words entered:");
    for (int i = 0; (words[i]); printf("%s\n", words[i++]));
    printf("\n\n");
}

void read_words_test2(void) {
    //Read words from a text file
    puts("Reading crime2.csv...");
    FILE *file = fopen("test/crime2.csv", "r");
    char **words;    
    while ((words = read_words(file, ","))) {
        for (int i = 0; (words[i]); printf("%s ", words[i++]));
        printf("\n");
    }
    fclose(file);  
}

void input_test(void) {
    char *line = input("Enter a line of text:\n");
    printf("\nLine entered:\n%s\n", line);
}

void read_csv_test(void) {
    //Read csv file
    puts("Reading crime2.csv...");
    char ***csv = read_csv("test/crime2.csv", ',');
    for (int i = 0; (csv[i]); ++i) {
        for (int j = 0; csv[i][j]; ++j) {
            printf("%s ", csv[i][j]);
        }
        printf("\n");
    }
}


int main(void) {
    // read_words_test1();
    // read_words_test2();
    // read_csv_test();
    // input_test();
    // printf("%s\n", scan_folder("c"));
    // unsigned long length = 0;
    char **lines = read_lines("input.txt");
    // char **lines = read_lines("test.txt");
    puts("Done");
    printf("%s\n", lines[0]);
    printf("%s\n", lines[1]);
    printf("%s\n", lines[2]);   
}