//
// Created by ahmed on 10/30/17.
//

#include <stdio.h>
#include <zconf.h>
#include "tokenizer.h"

/*
  Builtin function implementations.
*/

int __cd(Tokens tokens) {

    // cd at background is neglected
    if (tokens.background) return 1;

    char **args = tokens.args;

    if (args[1] == NULL) {
        fprintf(stderr, "hs-shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("hs-shell");
        }
    }
    return 1;
}

int __exit(Tokens tokens) {
    return 0;
}
