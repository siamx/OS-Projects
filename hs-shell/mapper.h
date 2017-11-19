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
char *builtin_name[] = {
        "cd",
        "help",
        "exit"
};

int builtin_cnt() {
    return sizeof(builtin_name) / sizeof(char *);
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

    fprintf(stdout, "Hindawy-Siam Shell - HSS\n");
    fprintf(stdout, "Type program names and arguments, and hit enter.\n");
    fprintf(stdout, "The following are built in:\n");

    int i;
    for (i = 0; i < builtin_cnt(); i++) {
        fprintf(stdout, "  %s\n", builtin_name[i]);
    }

    fprintf(stdout, "Use the man command for information on other programs.\n");
    return 1;
}

#endif //HS_SHELL_MAPPER_H
