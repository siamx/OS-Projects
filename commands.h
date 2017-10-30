//
// Created by ahmed on 10/30/17.
//

#ifndef HSH_COMMANDS_H
#define HSH_COMMANDS_H

/*
  Function Declarations for builtin shell commands:
 */

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int __cd(char **args);

/**
   @brief Builtin command: print help.
   @param args List of args.
   @return Always returns 1, to continue executing.
 */
int __help(char **args);

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int __exit(char **args);


#endif //HSH_COMMANDS_H
