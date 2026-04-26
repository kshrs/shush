#ifndef EXEC_H
#define EXEC_H

#include "builtins.h"
#include "alias.h"

/* function to launch programs using execvp */
int exec_prog(char** args);

/* function to launch builtin programs */
int exec_builtin(char** args);

/* function to execute alias */
char** exec_alias(char** args);

#endif
