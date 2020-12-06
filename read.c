/**
 * @file: read.c
 * @author: Muhammed Anas s/o Tariq
 * 
 * This file contains the implementation of a C input library to 
 * simplify the reading of a few common types of input from streams/files.
 */

#include "read.h"

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

char* read_word(FILE *file, unsigned int *length) {
    //Read a word from a stream and return a pointer to the string
	gobble_leading_space(file);
	unsigned int buffer = 10, i = 0;
	char *word = malloc(buffer * sizeof(char));
	for (int c = 0; !isspace(c = getc(file)) && c!= EOF;) {
		word[i++] = c;
		if (i == buffer - 1) {
			buffer *= 2;
			char *word_new = realloc(word, buffer * sizeof(char));
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
        if (length) {
            *length = i + 1;
        }
		return word;
	}
	return NULL;
}

char** read_words(FILE *file, const char *delimiters, unsigned int *count) {
    /*Read a line from a stream and return a pointer to the array of words
    * split based on delimiters specified in the array pointed to by delimiters, 
    * or, in the case of a NULL pointer, split based on space and/or punctuation 
    * marks: .,:;-!?'"*/    
    unsigned int buffer = 50, i = 0;
    char *line = read_line(file, NULL), **words = malloc(buffer * sizeof(char*));
    if (!delimiters) {
        delimiters = " ,.:;-!?'\"";
    }
    char *token = strtok(line, delimiters);
    while ((token)) {
        words[i++] = token;
        if (i == buffer - 2) {
            buffer *= 2;
            char **words_new = realloc(words, buffer * sizeof(char*));
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
        if (count) {
            *count = i;
        }
        return words;
    }
    return NULL;
}

char* read_line(FILE *file, unsigned int *length) {
    //Read a line from a stream and return a pointer to the string
	gobble_leading_space(file);
	unsigned int buffer = 50, i = 0;
	char *line = malloc(buffer * sizeof(char));
	for (int c = 0; (c = getc(file)) != '\n' && c != EOF;) {
		line[i++] = c;		
		if (i == buffer - 1) {
			buffer *= 2;
			char *line_new = realloc(line, buffer * sizeof(char));
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
        if (length) {
            *length = i + 1;
        }
		return line;
	}
	return NULL;
}

char** read_lines(const char *filename, unsigned int *length) {
    //Read lines from a text file and return a pointer to the array of strings
	unsigned int buffer = 256, i = 0;
	char *line, **lines = malloc(buffer * sizeof(char*));
	FILE *file = fopen(filename, "r");
	if (file) {
		while ((line = read_line(file, NULL))) {
			lines[i++] = line;
			if (i == buffer - 2) {
				buffer *= 2;
				char **lines_new = realloc(lines, buffer * sizeof(char*));
				if (lines_new) {
					lines = lines_new;
				}
				else {
	    			perror("Error");
	    			break;
	    		}
			}
		}
        fclose(file);
		lines[i] = NULL;
        if (length) {
            *length = i;
        }
        return lines;		
	}
	perror("Error");
	return NULL;    
}

char* read_file(const char *filename, unsigned int *size) {
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
                char *txt_new = realloc(txt, buffer * sizeof(char));
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
        if (size) {
            *size = i + 1;
        }
        return txt;       
    }
    perror("Error");
    return NULL;    
}

char*** read_csv(const char *filename, const char delimiter, unsigned int *rows) {
    /*Read a csv file and return a pointer to the array of arrays of strings
    * split based on delimiter*/
    unsigned int i = 0, buffer = 50;
    char ***csv = malloc(buffer * sizeof(char**)), **values;
    FILE *file = fopen(filename, "r");
    if (file) {
        gobble_leading_space(file);
        // char separator[] = {delimiter, ' ', ' ', '\0'}; //strip trailing space
        char separator[] = {delimiter, '\0'}; //strip trailing space
        while ((values = read_words(file, separator, NULL))) {
            csv[i++] = values;
            if (i == buffer-2) {
                buffer *= 2;
                char ***csv_new = realloc(csv, buffer * sizeof(char**));
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
        if (rows) {
            *rows = i;
        }
        return csv;
    }
    perror("Error");
    return NULL;
}

char* input(const char *prompt) {
    /*Print a prompt to and read a line from standard input and return a pointer 
    * to the string*/
    printf("%s", prompt);
    char *line = read_line(stdin, NULL);
    return line;
}

char* scan_folder(const char *ext) {
    /*Scan current directory for all files with extension .ext and return a 
    pointer to the string returned by shell*/
    char cmd[30];
    sprintf(cmd, CMD, ext);
    system(cmd);
    char *shell_result = read_file("shell_result", NULL);
    remove("shell_result");
    return shell_result;
}