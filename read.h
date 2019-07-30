#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

void gobble_leading_space(FILE* file);
void gobble_trailing_space(char* string, int* i);
char* read_word(FILE* file);
char** read_words(FILE* file, const char* delimiters);
char* read_line(FILE* file);
char** read_lines(const char* filename);
char* input(const char* prompt);
char* read_file(const char* filename);

#endif  //READ_H