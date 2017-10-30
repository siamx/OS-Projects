//
// Created by ahmed on 10/30/17.
//

#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <zconf.h>
#include <strings.h>
#include "tokenizer.h"


/*
  Builtin function implementations.
*/

int __cd(Tokens tokens) {
    // get the home directory path using the user_id
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    // cd at background is neglected
    if (tokens.background) return 1;

    char **args = tokens.args;

    if (args[1] == NULL || strcmp(args[1],"~") == 0) {
        chdir(pw->pw_dir);
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
