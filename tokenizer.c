//
// Created by ahmed on 10/30/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITER " \t\r\n\a"


char *read_line(void) {
    int buffsize = LINE_BUFFER_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "hsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= buffsize) {
            buffsize += LINE_BUFFER_SIZE;
            buffer = realloc(buffer, buffsize);
            if (!buffer) {
                fprintf(stderr, "hsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


char **tokenize_line(char *line) {
    int buffsize = TOKEN_BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "hsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITER);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffsize) {
            buffsize += TOKEN_BUFFER_SIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "hsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITER);
    }
    tokens[position] = NULL;
    return tokens;
}
