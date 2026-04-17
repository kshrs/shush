#ifndef SHELL_H
#define SHELL_H

#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 1
#endif

#ifndef NO_ARGS_PASSED
    #define NO_ARGS_PASSED 55
#endif

#ifndef NARGS_NOT_MET
    #define NARGS_NOT_MET 56
#endif

/* the mainloop of the shell */
void shush_mainloop();

/* simple readline function */
char* readline();

/* tokenizer to split the line to args */
char** splitargs(char* line);

/* execute function to call decide caller func like builtins or execvp */
int execute(char** args);

/* simple prompt function to present the error code along with the prompt */
void display_prompt(int status);

#endif
