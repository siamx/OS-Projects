//
// Created by ahmed on 10/30/17.
//

#ifndef HS_SHELL_TOKENIZER_H
#define HS_SHELL_TOKENIZER_H

typedef struct {
    char **args;
    int background;
} Tokens;

/**
   @brief Read a line of input from std-in.
   @return The line from std-in.
 */
char *read_line(void);

/**
   @brief Split a line into tokens.
   @param line The line.
   @return Null-terminated array of tokens.
 */
Tokens tokenize_line(char *line);

#endif //HS_SHELL_TOKENIZER_H
