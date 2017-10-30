//
// Created by ahmed on 10/30/17.
//

#ifndef HSH_VALIDATOR_H
#define HSH_VALIDATOR_H

#include "commands.h"

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int (*builtin_func[])(char **) = {
        &__cd,
        &__help,
        &__exit
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


/**
  @brief help function implementation, lists all available build in functions
 */
int __help(char **args) {
    int i;
    printf("Hindawy-Siam Shell - HSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

#endif //HSH_VALIDATOR_H
