//
// Created by ahmed on 10/30/17.
//

#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include "tokenizer.h"

/*
  Builtin function implementations.
*/

int __cd(Tokens tokens) {
    // cd at background is neglected
    if (tokens.background) return 1;

    // get the home directory path using the user_id
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    char **args = tokens.args;

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        chdir(pw->pw_dir);
    } else if (args[1] != NULL && args[2] != NULL) {
        fprintf(stderr, "hs-shell: too many args for cd\n");
    } else if (chdir(args[1]) != 0) {
        perror("hs-shell");
    }
    return 1;
}

int __exit(Tokens tokens) {
    return 0;
}
