#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "read.h"

#if defined(_WIN32) || defined(_WIN64)
#define CMD "dir /b *.%s > shell_result" //25
#endif

#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix__)
#define CMD "ls *.%s > shell_result"
#endif

static void gobble_leading_space(FILE *file) {
    //Remove all leading whitespace from a stream
	for (int c = 0; (c = getc(file)) != EOF;) {
		if (!isspace(c)) {
			ungetc(c, file);
			break;
		}
	}
}

static void gobble_trailing_space(char *string, unsigned int *i) {
    //Remove all trailing whitespace from a string
	unsigned int j = *i;
	while (isspace(string[j-1])) {
		j--;
	}
	*i = j;
}

char* read_word(FILE *file) {
    //Read a word from a stream and return a pointer to the string
	gobble_leading_space(file);
	unsigned int buffer = 10, i = 0;
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

char** read_words(FILE *file, const char *delimiters) {
    /*Read a line from a stream and return a pointer to the array of words
    * split based on delimiters specified in the array pointed to by delimiters, 
    * or, in the case of a NULL pointer, split based on space and/or punctuation 
    * marks: .,:;-!?'"*/    
    unsigned int buffer = 50, i = 0;
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
    if (i) {
        words[i] = NULL;
        return words;
    }
    return NULL;
}

char* read_line(FILE *file) {
    //Read a line from a stream and return a pointer to the string
	gobble_leading_space(file);
	unsigned int buffer = 50, i = 0;
	char *line = malloc(buffer * sizeof(char));
	for (int c = 0; (c = getc(file)) != '\n' && c != EOF;) {
		line[i++] = c;		
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
	unsigned int buffer = 256, i = 0;
	char *line, **lines = malloc(buffer * sizeof(char*));
	FILE *file = fopen(filename, "r");
	if (file) {
		while ((line = read_line(file))) {
            printf("Reading line ");
			lines[i++] = line;
            printf("%d\n", i);
			if (i == buffer - 2) {
				buffer *= 2;
				char **lines_new = realloc(lines, buffer);
				if (lines_new) {
					lines = lines_new;
                    puts("realloc passed");
				}
				else {
	    			perror("Error");
	    			break;
	    		}
			}
		}
		lines[i] = NULL;
        fclose(file);
        return lines;		
	}
	perror("Error");
	return NULL;    
}

char* read_file(const char *filename) {
    //Read a text file into a string and return a pointer to the string
    unsigned int c, i = 0, buffer = 1024;
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
        txt[i] = '\0';           
        fclose(file);
        return txt;       
    }
    perror("Error");
    return NULL;    
}

char*** read_csv(const char *filename, const char delimiter) {
    /*Read a csv file and return a pointer to the array of arrays of strings
    * split based on delimiter*/
    unsigned int i = 0, buffer = 50;
    char ***csv = malloc(buffer * sizeof(char**)), **values;
    FILE *file = fopen(filename, "r");
    if (file) {
        gobble_leading_space(file);
        char separator[] = {delimiter, ' ', ' ', '\0'}; //strip trailing space
        while ((values = read_words(file, separator))) {
            csv[i++] = values;
            if (i == buffer-2) {
                buffer *= 2;
                char ***csv_new = realloc(csv, buffer);
                if (csv_new) {
                    csv = csv_new;
                }
                else {
                    perror("Error");
                    break;
                }
            }
        }
        csv[i] = NULL;
        fclose(file);
        return csv;
    }
    perror("Error");
    return NULL;
}

char* input(const char *prompt) {
    /*Print a prompt to and read a line from standard input and return a pointer 
    * to the string*/
    printf("%s", prompt);
    char *line = read_line(stdin);
    return line;
}

char* scan_folder(const char *ext) {
    /*Scan current directory for all files with ext via shell and
    return a pointer to the string returned by shell*/
    char cmd[30];
    sprintf(cmd, CMD, ext);
    system(cmd);
    char *shell_result = read_file("shell_result");
    remove("shell_result");
    return shell_result;
}