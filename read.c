#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "read.h"

void gobble_leading_space(FILE* file) {
    //Remove all leading whitespace from a stream
	for (int c = 0; (c = getc(file)) != EOF;) {
		if (!isspace(c)) {
			ungetc(c, file);
			break;
		}
	}
}

void gobble_trailing_space(char* string, int* i) {
    //Remove all trailing whitespace from a string
	int j = *i;
	while (isspace(string[j-1])) {
		j--;
	}
	*i = j;
}

char* read_word(FILE* file) {
    //Read a word from a stream and return a pointer to the string
	gobble_leading_space(file);
	int buffer = 10, i = 0;
	char *word = malloc(buffer * sizeof(char));
	for (int c = 0; !isspace(c = getc(file)) && c!= EOF;) {
		word[i++] = c;
		if (i == buffer - 1) {
			buffer *= 2;
			char *word_new = realloc(word, buffer);
			if (word_new) {
				word = word_new;
			}
			else {
    			perror("Error");
    			break;
    		}
		}
	}
	if (i) {
		word[i] = '\0';
		return word;
	}
	return NULL;
}

char** read_words(FILE* file, const char* delimiters) {
    /*Read a line from a stream and return a pointer to the array of words
    * split based on delimiters specified in the array pointed to by delimiters, 
    * or, in the case of a NULL pointer, split based on punctuation marks*/    
    int buffer = 50, i = 0;
    char *line = read_line(file), **words = malloc(buffer * sizeof(char*));
    if (!delimiters) {
        delimiters = " ,.:;-!?'\"";
    }
    char *token = strtok(line, delimiters);
    while ((token)) {
        words[i++] = token;
        if (i == buffer - 2) {
            buffer *= 2;
            char **words_new = realloc(words, buffer);
            if (words_new) {
                words = words_new;
            }
            else {
                perror("Error");
                break;
            }
        }
        token = strtok(NULL, delimiters);
    }
    words[i] = NULL;
    return words;
}

char* read_line(FILE* file) {
    //Read a line from a stream and return a pointer to the string
	gobble_leading_space(file);
	int buffer = 50, i = 0;
	char *line = malloc(buffer * sizeof(char));
	for (int c = 0; (c = getc(file)) != '\n' && c != EOF;) {
		if (c != '\r') {
			line[i++] = c;
		}
		if (i == buffer - 1) {
			buffer *= 2;
			char *line_new = realloc(line, buffer);
			if (line_new) {
				line = line_new;
			}
			else {
    			perror("Error");
    			break;
    		}
		}
	}
	if (i) {
		gobble_trailing_space(line, &i);
		line[i] = '\0';
		return line;
	}
	return NULL;
}

char** read_lines(const char *filename) {
    //Read lines from a text file and return a pointer to the array of strings
	int buffer = 50, i = 0;
	char *line, **txt = malloc(buffer * sizeof(char*));
	FILE *file = fopen(filename, "r");
	if (file) {
		while ((line = read_line(file))) {
			txt[i++] = line;
			if (i == buffer - 2) {
				buffer *= 2;
				char **txt_new = realloc(txt, buffer);
				if (txt_new) {
					txt = txt_new;
				}
				else {
	    			perror("Error");
	    			break;
	    		}
			}
		}
		txt[i] = NULL;		
	}
    else {
    	perror("Error");
		return NULL;
    }
    fclose(file);
	return txt;
}

char* input(const char* prompt) {
    //Print a prompt to and read a line from standard input and return a pointer to the string 
    printf("%s", prompt);
    char *line = read_line(stdin);
    return line;
}

char* read_file(const char *filename) {
	int c, i = 0, buffer = 1024;
	char *txt = malloc(buffer * sizeof(char));
	FILE *file = fopen(filename, "r");
	if (file) {
		gobble_leading_space(file);
	    while ((c = getc(file)) != EOF) {
	    	txt[i] = c;
	    	if (++i == buffer-2) {
	    		buffer *= 2;
	    		char *txt_new = realloc(txt, buffer);
	    		if (txt_new) {
	    			txt = txt_new;
	    		}
	    		else {
	    			perror("Error");
	    			break;
	    		}
	    	}
	    }	    	
	    fclose(file);
	    txt[i] = '\0';
	}
    else {
		return NULL;
    }
	return txt;
}