//
// Created by ahmed on 10/30/17.
//

#ifndef HSH_TOKENIZER_H
#define HSH_TOKENIZER_H

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *read_line(void);

/**
   @brief Split a line into tokens.
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **tokenize_line(char *line);

#endif //HSH_TOKENIZER_H
