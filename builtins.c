#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "include/shell.h"
#include "include/builtins.h"

int cd_builtin(struct BuiltIn* self, char** args) {
    if (args[1] == NULL) {
        fprintf(stderr, "No arguments passed\n");
        return NARGS_NOT_MET;
    }

    if (strcmp(args[1], "-h") == 0) {
        char msg[1000];
        snprintf(msg, sizeof(msg)*1, "%s: %s\n", self->prog_name, self->doc_string);
        write(STDOUT_FILENO, msg, strlen(msg));
        return EXIT_SUCCESS;
    }
    if (chdir(args[1]) != 0) {
        perror("cd");
    }
    return EXIT_SUCCESS;
}

BuiltIn builtins[] = {
    // How to assign the functions to the struct
    { .prog_name = "cd", .func = cd_builtin, .doc_string = "Used to change directory" },
    { .prog_name = NULL, .func = NULL, .doc_string = NULL }
};

