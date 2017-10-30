//
// Created by ahmed on 10/30/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

#define LINE_BUFFER_SIZE 512
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITER " \t\r\n\a"

/**
   @brief Read a line of input from std-in.
   @return The line from std-in.
 */
char *read_line(void) {
    int buffer_size = LINE_BUFFER_SIZE, position = 0;
    char *buffer = malloc(sizeof(char) * buffer_size);
    int c;

    if (!buffer) {
        fprintf(stderr, "hs-shell: allocation error\n");
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
            buffer[position] = (char) c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= buffer_size) {
            buffer_size += LINE_BUFFER_SIZE;
            buffer = realloc(buffer, (size_t) buffer_size);
            if (!buffer) {
                fprintf(stderr, "hs-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
   @brief Split a line into tokens.
   @param line The line.
   @return Null-terminated array of tokens.
 */
Tokens tokenize_line(char *line) {
    Tokens tokens;
    int buffer_size = TOKEN_BUFFER_SIZE, position = 0;
    tokens.args = malloc(buffer_size * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens.args) {
        fprintf(stderr, "hs-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITER);
    while (token != NULL) {
        tokens.args[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += TOKEN_BUFFER_SIZE;
            tokens_backup = tokens.args;
            tokens.args = realloc(tokens.args, buffer_size * sizeof(char *));
            if (!tokens.args) {
                free(tokens_backup);
                fprintf(stderr, "hs-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITER);
    }
    tokens.args[position] = NULL;

    // check for `&`, background command
    tokens.background = (position > 1 && strcmp(tokens.args[position - 1], "&") == 0) ? 1 : 0;
    return tokens;
}
