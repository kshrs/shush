#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MINBUFFER 3

void shush_loop();
char* shush_readline();
char** shush_splitargs(char* line);
int shush_execute(char** args);


int main(int argc, char** argv) {
    // 1. Load some configuration if present
    
    // 2. Load Eval loop
    shush_loop();
    
    // 3. Free up memory at the end
    printf("Exiting shell\n\n\n");
    return EXIT_SUCCESS;
}

void shush_loop() {
    char* line;
    char** args;
    int status;

    do {
        printf(">>> ");
        line = shush_readline();
        if (!line) {
            printf("Error reading line from stdin\n");
        }
        args = shush_splitargs(line);
        status = shush_execute(args);
    } while(status);

    free(line);
    free(args);
}

char* shush_readline() {
    size_t current_size = MINBUFFER;
    void* realloc_status = NULL;
    char* line = malloc(current_size);
    int c;
    int len = 0;

    while( ((c = getchar()) != EOF) && c != '\n' ) {
        if (len == current_size-1) {
            current_size *= 2;
            realloc_status = realloc(line, current_size);
            if (!realloc_status) {
                return NULL;
            }
        }
        *(line + len) = c;
        len++;
    }
    *(line + len) = '\0';
    return line;
}

char** shush_splitargs(char* line) {
    char* delim = " ";
    char* token = strtok(line, delim);
    char** tokens = NULL;
    int count = 0;

    while(token != NULL) {
        if (tokens == NULL) {
            tokens = malloc(sizeof(char*));
        } else {
            realloc(tokens, sizeof(char*) * (count + 1));
        }

        tokens[count] = strdup(token);
        count++;

        token = strtok(NULL, delim);
    }

    char* temp = *tokens;
    // for(int i=1; i<=count; ++i) {
    //     printf("Token: %s\n", temp);
    //     temp = *(tokens + i);
    // }

    return tokens;
}

int shush_execute(char** args) {
    if (args[0] == NULL) {
        return 0;
    }
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }
    return 1;

}

