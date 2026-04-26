#ifndef ALIAS_H
#define ALIAS_H

struct Alias;

typedef char* Alias_Name;

typedef struct Alias {
    Alias_Name alias_name;
    char** alias_exp;
} Alias;

extern Alias aliases[];

#endif
