#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/shell.h"
#include "include/color.h"
#include "include/prompt.h"

char* prompt = NULL;
size_t prompt_size = 100;
char* default_prompt = COLOR_F_GREEN "> " COLOR_RESET;

void init_prompt() {
    prompt = (char*) malloc(prompt_size * sizeof(char));
    if (!prompt) {
        perror("shush: Failed to init prompt; MEM_ALLOC_ERR");
        exit(1);
    }
    snprintf(prompt, prompt_size, "%s", default_prompt);
}

void reset_default_prompt() {
    snprintf(prompt, prompt_size, "%s", default_prompt);
}

void add_flag_to_prompt(char* flag) {

start:
    int needed = snprintf(prompt, prompt_size, "%s%s", flag, default_prompt);
    
    if (needed < 0) {
        perror("shush: Formatting Error with prompt");
        exit(1);
    }
    if ((size_t) needed >= prompt_size) {
        prompt_size = needed + 1;
        prompt = (char*) realloc(prompt, prompt_size * sizeof(char));
        if (!prompt) {
            perror("shush: Failed to modify prompt; MEM_REALLOC_ERR");
            exit(1);
        }
        goto start;
    }
}

void display_prompt(int status) {

    char* nil_flag = COLOR_F_RED "nil" COLOR_RESET;
    char* err_flag = COLOR_F_RED "err" COLOR_RESET;
    char* arg_err_flag = COLOR_F_RED "arg_err" COLOR_RESET;

    switch(status) {
        case NO_ARGS_PASSED:
            add_flag_to_prompt(nil_flag);
            write(STDOUT_FILENO, prompt, strlen(prompt));
            break;

        case NARGS_NOT_MET:
            add_flag_to_prompt(arg_err_flag);
            write(STDOUT_FILENO, prompt, strlen(prompt));
            break;
            
        case EXIT_FAILURE:
            add_flag_to_prompt(err_flag);
            write(STDOUT_FILENO, prompt, strlen(prompt));
            break;

        case EXIT_SUCCESS:
            write(STDOUT_FILENO, prompt, strlen(prompt));
            break;
            
        default:
            
            char code_flag[100];
            sprintf(code_flag, "%d%s", status, prompt);
            write(STDOUT_FILENO, code_flag, strlen(code_flag));
    }
    reset_default_prompt();
}
