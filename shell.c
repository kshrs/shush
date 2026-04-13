#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 1
#endif

#ifndef NO_ARGS_PASSED
 #define NO_ARGS_PASSED 55
#endif

void shush_mainloop();
char* readline();
char** splitargs(char* line);
int execute(char** args);
void display_prompt(int status);

void exit_handler(int signal);

int main(int argc, char** argv) {
    signal(SIGINT, exit_handler);

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
    char* line = (char*) malloc(sizeof(char*) * capacity);

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
    *(tokens + count) = token;
    return (char**) tokens;
}

void exit_handler(int sig) {
    exit(0);
}

int execute(char** args) {
    if (!args) {
        return NO_ARGS_PASSED;
    }

    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting shush....\n");
        exit(0);
    }

    return 0;
}

void display_prompt(int status) {
    const char* prompt = "> ";
    char nil_flag[6] = "nil";

    switch(status) {
        case NO_ARGS_PASSED:
            strcat(nil_flag, prompt);
            write(STDOUT_FILENO, nil_flag, strlen(nil_flag));
            break;
            
        default:
            write(STDOUT_FILENO, prompt, strlen(prompt));
    }
}
