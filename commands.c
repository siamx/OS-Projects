//
// Created by ahmed on 10/30/17.
//

#include <stdio.h>
#include <zconf.h>

/*
  Builtin function implementations.
*/

int __cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "hsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("hsh");
        }
    }
    return 1;
}


int __exit(char **args) {
    return 0;
}
