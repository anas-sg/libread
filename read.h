#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

char* read_word(FILE *file);
char** read_words(FILE *file, const char *delimiters);
char* read_line(FILE *file);
char** read_lines(const char *filename);
char* read_file(const char *filename);
char*** read_csv(const char *filename, const char delimiter);
char* input(const char *prompt);
char* scan_folder(const char *ext);

#endif  //READ_H