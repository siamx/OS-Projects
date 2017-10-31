#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include "mapper.h"

// COLORS
#define _RED     "\x1b[31m"
#define _GREEN   "\x1b[32m"
#define _YELLOW  "\x1b[33m"
#define _BLUE    "\x1b[34m"
#define _MAGENTA "\x1b[35m"
#define _CYAN    "\x1b[36m"
#define _RESET   "\x1b[0m"
//

#define CURRENT_DIR_BUFFER 512

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int launch(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("hs-shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("hs-shell");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int execute(Tokens tokens) {
    char **args = tokens.args;
    int i;
    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(tokens);
        }
    }

    return launch(args);
}

/**
   @brief Loop getting input and executing it.
 */
void loop(void) {
    char *line;
    Tokens tokens;
    int status;

    char *current_dir = malloc(sizeof(char) * CURRENT_DIR_BUFFER);
    if (!current_dir) {
        fprintf(stderr, "hs-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    size_t size = CURRENT_DIR_BUFFER;

    do {
        current_dir = getcwd(current_dir, size);
        fprintf(stdout, _CYAN "%s » " _RESET, current_dir);
        line = read_line();
        tokens = tokenize_line(line);
        status = execute(tokens);

        free(line);
        free(tokens.args);

        __fpurge(stdin);
    } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv) {

    // Always flush the stdout, stderr is unbuffered
    setbuf(stdout, NULL);

    // Run command loop.
    loop();

    return EXIT_SUCCESS;
}
