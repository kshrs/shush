#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "include/shell.h"
#include "include/exec.h"

int main() {
    /* the main shell process should not be interrupted and can only be killed or terminated */
    signal(SIGINT, SIG_IGN);

    // 1. config
    
    // 2. mainloop
    shush_mainloop();

    // 3. clear mem
    
    return EXIT_SUCCESS;
}


void shush_mainloop() {
    char* line;
    char** args;
    int status = 0;
    
    while(1) {
        // 0. display prompt
        display_prompt(status);

        // 1. readline
        line = readline();

        // 2. splitargs
        args = splitargs(line);
        
        // 3. execute
        status = execute(args);
    } 
    
    free(line);
    free(args);
}

#define INIT_READLINE_BUFSIZE 50;
char* readline() {
    int capacity = INIT_READLINE_BUFSIZE;
    char* line = (char*) malloc(sizeof(char) * capacity);

    if (!line) {
        fprintf(stderr, "Failed to allocate memory to (char* line)\n");
        exit(-1);
    }

    int c;
    int len = 0;

    while((c=getchar()) != EOF && c != '\n') {
        if (len == (capacity-1)) {
            capacity = 2 * capacity;
            line = (char*) realloc(line, sizeof(char*) * capacity);

            if (!line) {
                fprintf(stderr, "Failed to reallocate memory to (char* line)\n");
                exit(-1);
            }
        }

        line[len++] = c;
    }
    line[len++] = '\0';

    return (char *) line;
}

char** splitargs(char* line) {
    int count = 0;

    char** tokens = malloc(sizeof(char*) * (count + 1));
    const char* delim = " ;";

    if (!*line) {
        return NULL;
    }

    char* token = strtok(line, delim);
    while(token != NULL) {
        *(tokens + count) = token;
        count++;
        tokens = (char**) realloc(tokens, sizeof(char*) * (count + 1));
        token = strtok(NULL, delim);
    }
    *(tokens + count) = token; // append the args with NULL Terminator
    return (char**) tokens;
}

int execute(char** args) {
    int status;
    if (!args) {
        return NO_ARGS_PASSED;
    }

    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting shush....\n");
        exit(0);
    }

    char** exp_args = exec_alias(args);
    args = (exp_args == NULL) ? args : exp_args;

    status = exec_builtin(args);

    if (status == EXIT_SUCCESS) {
        return status;
    }
    if (status == NARGS_NOT_MET) {
        return status;
    }
    status = exec_prog(args);
    return status;
}


void display_prompt(int status) {
    const char* prompt = "> ";
    char nil_flag[6] = "nil";
    char err_flag[6] = "err";
    char arg_err_flag[10] = "arg_err";

    switch(status) {
        case NO_ARGS_PASSED:
            strcat(nil_flag, prompt);
            write(STDOUT_FILENO, nil_flag, strlen(nil_flag));
            break;

        case NARGS_NOT_MET:
            strcat(arg_err_flag, prompt);
            write(STDOUT_FILENO, arg_err_flag, strlen(arg_err_flag));
            break;
            
        case EXIT_FAILURE:
            strcat(err_flag, prompt);
            write(STDOUT_FILENO, err_flag, strlen(err_flag));
            break;

        case EXIT_SUCCESS:
            write(STDOUT_FILENO, prompt, strlen(prompt));
            break;
            
        default:
            char code_flag[7];
            sprintf(code_flag, "%d%s", status, prompt);
            write(STDOUT_FILENO, code_flag, strlen(code_flag));
    }
}
