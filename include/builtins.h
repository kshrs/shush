#ifndef BUILTINS_H
#define BUILTINS_H

struct BuiltIn;


// BuiltIn Struct
typedef struct BuiltIn {
    char* prog_name;
    int (*func)(struct BuiltIn* self, char** args);
    char* doc_string;
} BuiltIn;


extern BuiltIn builtins[];

#endif
