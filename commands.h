//
// Created by ahmed on 10/30/17.
//

#ifndef HS_SHELL_COMMANDS_H
#define HS_SHELL_COMMANDS_H

#include "tokenizer.h"

/*
  Function Declarations for builtin shell commands:
 */

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int __cd(Tokens tokens);

/**
   @brief Builtin command: print help.
   @param args List of args.
   @return Always returns 1, to continue executing.
 */
int __help(Tokens tokens);

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int __exit(Tokens tokens);

#endif //HS_SHELL_COMMANDS_H
