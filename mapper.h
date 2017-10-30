//
// Created by ahmed on 10/30/17.
//

#ifndef HS_SHELL_MAPPER_H
#define HS_SHELL_MAPPER_H

#include "commands.h"
#include "tokenizer.h"

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/**
  @param tokens
  @return state return value of executed command
 */
int (*builtin_func[])(Tokens tokens) = {
        &__cd,
        &__help,
        &__exit
};

/**
  @brief help function implementation, lists all available build in functions
 */
int __help(Tokens tokens) {

    // help at background run is neglected
    if (tokens.background) return 1;

    int i;
    printf("Hindawy-Siam Shell - HSS\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

#endif //HS_SHELL_MAPPER_H
