#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include "include/exec.h"

int exec_prog(char** args) {
    pid_t pid, wpid;
    int status;
    (void) wpid; // To Supress Unused Variable Warning

    pid = fork();

    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        // Child Process
        if (execvp(args[0], args) == -1) {
            char err_msg[256];
            snprintf(err_msg, 256, "shush: Command not found: %s", args[0]);
            perror(err_msg);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error Forking
        perror("Error forking process at func (int launch_prog(char** args))");
        return EXIT_FAILURE;
    } else {
        // Parent Process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return WEXITSTATUS(status);
}

int exec_builtin(char** args) {
    for (int i = 0; builtins[i].prog_name != NULL; ++i) {
        if (strcmp(builtins[i].prog_name, args[0]) == 0) {
            return builtins[i].func(&builtins[i], args);
        }
    }
    return EXIT_FAILURE;
}
